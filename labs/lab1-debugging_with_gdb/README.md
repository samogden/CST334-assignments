# CST334 Lab 1

## Background

In this lab we'll be trying to debug some runtime issues in C to get a sense of how to approach fixing problems in our homework code.
Runtime issues in C are different than in many other languages, such as python, because by default C doesn't give us any hints as to what is wrong.
This allows it to run much faster, but is also much harder to understand.

In this lab we'll be talking about compilation flags and we'll be trying out a tool, `gdb` to help is isolate memory issues and figure out what's going wrong.

---
> <b>Common Issues</b>
> 
> A common issue is not being able to find the correct files or directory.  If this is happening to you, then you are not alone!
> 
> The cause of this is usually that you started docker in a slight different way or wound up in a different path than usual.
> 
> There are two commands that will help you solve your issue!
> 
> 1. `pwd` : Tells you the directory you are currently in
> 2. `ls` : lists the contents of the current directory
>    - Has some useful flags:
>      - `-l` (for "long") lists more information (details to come in lectures) 
>      - `-a` (for "all") lists _all_ files, including normally hidden files
>    - Can also be called on a directory by passing this in as an _argument_
>      - e.g. `ls dir` will return the contents of the directory.
> 
> These can be used to figure out _where_ you are in a file system and where you can move to in it!
> 
> p.s. don't forget that you can use `..` to reference the parent directory.  For example, `ls /tmp/hw/..` will tell you the contents of the `/tmp` directory.
> 
---


### Lab files

This lab is designed to be a miniature version of the homework.
It has a [`src`](src) folder, a [`include`](include) folder, and a [`tests`](tests) folder, contianing source code, headers, and testing files respectively.
It also has a [`Makefile`](Makefile) that will build executables for you.
Itt has two other files, one of which we've seen in PA1 and the other which is new.

Let's dig into a few of these files now.

#### `unit_tests.c`

The first file we'll be looking at is [`unit_tests.c`](unit_tests.c), the source code of which we can see below

```shell
[DOCKER] /tmp/hw/labs/lab1-debugging_with_gdb/ $ cat -n unit_tests.c
     1	#include <criterion/criterion.h>
     2
     3	#include "tests/tests-person.c"
```

It's... a bit boring.
It has two lines that do something.

First, one line 1 we have `#include <criterion/criterion.h>`.
This is an include preprocessor directive.
Include directives basically say "copy the contents of this mentioned file here", so it's saying to copy the contents of `<criterion/criterion.h>` to the current source code.
This is us including a header of the unit testing framework we'll be using so we can start using tests.
If you want to dig into it a bit more that's beyond the scope of what you really need to worry about, but it's a nifty project and can be found [here](https://github.com/Snaipe/Criterion).

The second is line 3, where we say `#include "tests/tests-person.c"`.
Similar to line 1, this is us pulling in the contents of another file, in this case our actual unit tests.
We'll be looking at these later, but I wanted to point out how it flows.

So, basically our unit tests file includes our framework and then includes our tests.
In PA1, this is done [exactly the same way](../../programming-assignments/PA1/unit_tests.c).


#### `debug.c`

The second file is called `debug.c` and is meant to help us isolate problems in our code.
Below we can see what it currently consists of.

```shell
[DOCKER] /tmp/hw/labs/lab1-debugging_with_gdb/ $ cat -n debug.c
     1	#include "student_code.h"
     2
     3	int main() {
     4	    return 0;
     5	}
```

Somehow I managed to make it even more boring than `unit_tests.c`.
We can see a similar structure here, where it includes our student code functions and then just exits.

This is intentional.  We want to keep this file fairly empty in order to move what we're currently debugging into there.
Essentially, it's a scratchpad where we're going to be looking at bugs more closely.

#### `include/student_code.h`

When looking at a new project it's often helpful to look at the header files.
Header files define how you can interact with code, so it essentially defines the API that the library presents.

Inside a header file is any definitions that are used in a program and any functions that the library is presenting.
Let's check out what we're presenting in this project.

```c
 1	#ifndef PROJECTS_STUDENT_CODE_H
 2	#define PROJECTS_STUDENT_CODE_H
 3
 4	typedef struct Person {
 5	    int age;
 6	    char name[8];
 7	    int favorite_number;
 8	} Person;
 9
10	/**
11	 * This function takes in an age, a name, and a favorite number and returns a person
12	 * @param age integer representing age
13	 * @param name character string representing name (at most 7 chars long!)
14	 * @param favorite_number integer representing favorite number
15	 * @return
16	 */
17	Person make_new_person(int age, char* name, int favorite_number);
18
19	#endif //PROJECTS_STUDENT_CODE_H
```

The first thing we notice is that on lines 1, 2, and 19 we are using some preprocessor commands.
Preprocessor commands let us do things, in this case making it check to see if a variable is set.
This prevent us from re-including the same header file twice, which would cause the compiler confusion.

Next, from lines 4-8 we define a Person struct and typedef it to make it so we can just say `Person` instead of `struct Person`.

Finally, lines 10-17 define a function called `make_new_person`.
This function's declaration is line 17, but the lines 11-15 describe what the function is going to do.
The unit tests _should_ be written to match this description so if you are wondering what a test should do this is a good place to check.  


#### `src/student_code.c`

Now that we've looked a little bit at our general setup and headers, let's look at the specifics of what our code does.
Unlike the homework, I'm providing a bit of code, so let's check it out!

```c
 1	#include <string.h>
 2	#include "student_code.h"
 3
 4
 5	/***********
 6	 * Persons *
 7	 ***********/
 8
 9	Person make_new_person(int age, char* name, int favorite_number) {
10	    Person p;
11	    p.age = age;
12	    strcpy(p.name, name);
13	    p.favorite_number = favorite_number;
14	    return p;
15	}
```

Okay, so this code should hopefully look familiar, since the general layout is similar to homework.
At the very top, on lines 1 and 2 we have our includes, which bring in libraries an function declarations.
Next, we have some fanciness and then the actual function itself.

This function is fairly straight forward -- we're just making a new instance of a `Person` struct, setting some parts of it and then returning the memory object.
The only time we don't do this directly ourselves is when we use the library function `strcpy` which copies null terminated strings from one memory location to another.

***TODO:*** Go check out the documentation for [strcpy](https://linux.die.net/man/3/strcpy).
Does anything jump out at you?

Overall, this looks pretty okay and basic.
`strcpy` is a standard function that so long as our strings are well-formatted should probably work.
Nothing setting off red flags yet, right?

## Lab Steps


## Step 0: Preparation

Make sure that you've gone through the steps to install docker and get it running as per the slides/video on canvas.

Additionally, create a google document (or microsoft word, or apple pages, if you prefer) titled "Lab 1"

### Step 1: Start Docker

First, navigate to your working directory in your terminal of choice (e.g. PowerShell on Windows or Terminal on macOS) and type in the following command:
```bash
docker run -it -v ${PWD}:/tmp/lab samogden/csumb:cst334
```

This will start docker and mount the current folder inside of it, giving us access to our shared files.

Next, run the below command to change directory.

```bash
cd /tmp/lab
```

Because this folder was mounted with the `-v ${PWD}:/tmp/lab` flag when we started the docker image it is shared with our host operating system allowing us to edit files locally and have the changes automatically appear in the docker image.


## Step 2: Downloading the starter code

Type the following into your terminal:
```bash
git clone https://github.com/samogden/CST334-assignments
```

This will download the a git repository containing the lab data files.
To change to the directory containing the files for this lab (including a copy of this file) run the below commands.

```bash
cd CST334-assignments
cd labs
cd lab1-debugging_with_gdb
```

Note that you can run all of these commands on a single line as `cd CST334-assignments/labs/lab1-debugging_with_gdb`.

## Step 3: Open the starter code

To open the starter code you should navigate in your host operating system (e.g. windows or OSX) to the same directory as your terminal instance is.
That is, in the directory you started docker in click folders until you are in the `lab1-debugging_with_gdb` directory.



## Step 4: Let's watch things break

Okay, so now that we've check out our various files, let's run our program and see how our tests are doing!
We run it by using the `make` command, which parses our Makefile.
Running it we get the below:

```shell
[DOCKER] /tmp/hw/labs/lab1-debugging_with_gdb/ $ make
rm -rf bin unit_tests debug
mkdir -p bin
gcc -Wall -lcriterion -I/opt/homebrew/Cellar/criterion/2.4.1_2/include/ -c src/student_code.c -o bin/student_code.o
gcc -Wall -lcriterion -I/opt/homebrew/Cellar/criterion/2.4.1_2/include/ unit_tests.c -o unit_tests bin/student_code.o
./unit_tests
[----] tests/tests-person.c:25: Assertion Failed
[----]
[----]   The expression strcmp(p2.name, "Douglas A") == 0 is false.
[----]
[FAIL] Person::make_new_person: (0.00s)
*** stack smashing detected ***: terminated
[----] tests/tests-person.c:30: Unexpected signal caught below this line!
[FAIL] Person::make_new_person_badly: CRASH!
[====] Synthesis: Tested: 2 | Passing: 0 | Failing: 2 | Crashing: 1
make: *** [Makefile:13: all] Error 1
```

Shoot.
That's not good.
Something went wrong.

***Note:*** if running on an intel processor you may not see a stack smashing warning.
If this happens to you  then a few of the below steps will be affected -- specifically when you run gdb your execution will not stop and running `backtrace` will say there is no stack -- this is because the execution of the program completed.
If this happens then please read through the next few sections until you get to when we [recompile for GDB](#step-3b-compiling-for-gdb) where instructions will be more similar.

***TODO:*** Take a screenshot of the `make` command failing and paste it into your google document.

### Step 4a: Digging into what we're seeing

Let's try to parse out what happened.
To break this down a bit I'm going to pipe the output of make into `cat -n` to add line numbers, and then add in some artificial spacing for clarity.
The command has two parts.
`make 2>&1` means to run `make` and make stderr write to stdout (i.e. "combine file 2 to file 1").
`| cat -n` says "take the output of the previous command and pass it into `cat -n`", and `cat -n` just repeats back what is input with line numbers added in.

```shell
[DOCKER] /tmp/hw/labs/lab1-debugging_with_gdb/ $ make 2>&1 | cat -n
     1	rm -rf bin unit_tests debug
     
     2	mkdir -p bin
     
     3	gcc -Wall -lcriterion -I/opt/homebrew/Cellar/criterion/2.4.1_2/include/ -c src/student_code.c -o bin/student_code.o
     4	gcc -Wall -lcriterion -I/opt/homebrew/Cellar/criterion/2.4.1_2/include/ unit_tests.c -o unit_tests bin/student_code.o
     
     5	./unit_tests
     6	[----] tests/tests-person.c:20: Assertion Failed
     7	[----]
     8	[----]   The expression strcmp(p2.name, "Douglas A") == 0 is false.
     9	[----]
    10	[FAIL] Person::make_new_person: (0.00s)
    
    11	*** stack smashing detected ***: terminated
    12	[----] tests/tests-person.c:25: Unexpected signal caught below this line!
    13	[FAIL] Person::make_new_person_badly: CRASH!
    14	[====] Synthesis: Tested: 2 | Passing: 0 | Failing: 2 | Crashing: 1
    
    15	make: *** [Makefile:13: all] Error 1
```

Line 1 is running the `clean` command within the make file.
(If you didn't ask ChatGPT about Makefiles, now might be a good time).

Line 2 is running another make command to create the `bin` directory, since we just deleted it.

Lines 3 and 4 are compiling our code, and we see that goes fine.

Line 5 is where we start running our code.
We see that it calls the executable (`./unit_tests`) and then it starts running our code.

On line 6 we see our first error reported -- specifically some assertion on line 20 failed.
A failed assertion means that something didn't happen like we expected it to -- it is our unit test failing, indicating that something needs to be fixed in our implementation.
Line 8 tells us what this specific fail was, and then line 10 notifies us (again) that we failed our unit test (d'oh!).

Line 11 is scary.
"*** stack smashing detected ***: terminated" sounds pretty serious.
It's so serious, in fact, that it actually crashes out next test, which is told to us on line 13.
All we know about it is that the last known-good line is reported on line 12 as "tests/tests-person.c:25".

Line 14 is a summary of the tests, telling us that it tested 2 things, 2 of them failed and one of the ultra-failed (i.e. it crashed).

Finally, line 15 is just our make file telling us that something went wrong.

Well shoot.
Time to get debugging!

## Step 5: Checking out our unit tests.

The first thing we should do is go and find out where our tests are failing.
Let's check out our unit test file in `tests/tests-person.c`.

```c
 1	#include <criterion/criterion.h>
 2	#include "student_code.h"
 3
 4	TestSuite(Person, .disabled=false);
 5
 6	Test(Person, make_new_person, .disabled=false) {
 7	    // First we make a person that fits expectations
 8	    Person p1 = make_new_person(27, "Doug", 42);
 9
10	    //Next, we test to make sure it worked correctly
11	    cr_assert(p1.age == 27); // Test age
12	    cr_assert(strcmp(p1.name, "Doug") == 0); // Note that we use the strcmp function
13	    cr_assert(p1.favorite_number == 42); // Test favorite number
14
15	    // Next we poke around at our expectations a bit
16	    Person p2 = make_new_person(27, "Douglas A", 42);
17
18	    //Next, we test to make sure it worked correctly
19	    cr_assert(p2.age == 27); // Test age
20	    cr_assert(strcmp(p2.name, "Douglas A") == 0); // Note that we use the strcmp function
21	    cr_assert(p2.favorite_number == 42); // Test favorite number
22	}
23
24
25	Test(Person, make_new_person_badly, .disabled=false) {
26	    // Next we poke around at our expectations a bit
27	    Person p2 = make_new_person(27, "Douglas Adams", 42);
28
29	    //Next, we test to make sure it worked correctly
30	    cr_assert(p2.age == 27); // Test age
31	    cr_assert(strcmp(p2.name, "Douglas Adams") == 0); // Note that we use the strcmp function
32	    cr_assert(p2.favorite_number == 42); // Test favorite number
33	}
```

Looking at our unit tests file, we have a "TestSuite" and two "Test"s.
The TestSuite is how we group together tests hierarchically and is helpful in larger assignments -- our PA1 has four test suites.
The Test is how we actually declare an individual tests.
One thing to notice is that each of these, both TestSuites and Test, have a field called `.disabled` that we can use to toggle the test on and off.
If we disable a test it isn't run -- so if you do temporarily toggle one off don't forget to turn it back on!

We can see now the culprits of our errors that were reported [above](#step-1a-digging-into-what-were-seeing).
Let's look a bit more at these.

For the first one, we see the following few lines.

```c
15	    // Next we poke around at our expectations a bit
16	    Person p2 = make_new_person(27, "Douglas A", 42);
17
18	    //Next, we test to make sure it worked correctly
19	    cr_assert(p2.age == 27); // Test age
20	    cr_assert(strcmp(p2.name, "Douglas A") == 0); // Note that we use the strcmp function
21	    cr_assert(p2.favorite_number == 42); // Test favorite number
```

Essentially we're creating an object and then checking to see whether it has the right name.
That looks fine.
In fact, on lines 8 through 13 we do the same thing and it works!
That's weird.
Let's move on for now.

For the crash, we just got told that the last good line was line 25 so let's look at that function.
```c
25	Test(Person, make_new_person_badly, .disabled=false) {
26	    // Next we poke around at our expectations a bit
27	    Person p2 = make_new_person(27, "Douglas Adams", 42);
28
29	    //Next, we test to make sure it worked correctly
30	    cr_assert(p2.age == 27); // Test age
31	    cr_assert(strcmp(p2.name, "Douglas Adams") == 0); // Note that we use the strcmp function
32	    cr_assert(p2.favorite_number == 42); // Test favorite number
33	}
```

This looks to be doing exactly the same thing!
The only difference is that the string is longer.
Huh.  Curiouser and curiouser.

Because it's doing the same thing but failing more epically, let's just isolate just this test for now.
Set the `.disabled` on the first test to be`true` (and remember to turn it on again before submitting your homework!).

***TODO:*** Take a screenshot with the test disabled and paste it into your google doc.

### Step 5a: let's see what happens when we've disabled that test

```shell
[DOCKER] /tmp/hw/labs/lab1-debugging_with_gdb/ $ make 2>&1 | cat -n
     1	rm -rf bin unit_tests debug
     2	mkdir -p bin
     3	gcc -Wall -lcriterion -I/opt/homebrew/Cellar/criterion/2.4.1_2/include/ -c src/student_code.c -o bin/student_code.o
     4	gcc -Wall -lcriterion -I/opt/homebrew/Cellar/criterion/2.4.1_2/include/ unit_tests.c -o unit_tests bin/student_code.o
     5	./unit_tests
     6	*** stack smashing detected ***: terminated
     7	[----] tests/tests-person.c:25: Unexpected signal caught below this line!
     8	[FAIL] Person::make_new_person_badly: CRASH!
     9	[====] Synthesis: Tested: 1 | Passing: 0 | Failing: 1 | Crashing: 1
    10	make: *** [Makefile:13: all] Error 1
```

Okay, so now we're having this really bad fail.
If we can fix it then it can probably help us figure out what's going on a bit better.
Let's get going and dig into it a bit more!


## Step 6: Isolating the problem

Before we start digging into debugging tools I have to say that I'm willing to bet some of you can already guess what's going on.
For a problem like this a full debug is potentially overkill but it's good to go through the steps and practice.

Okay!
So let's grab this snippet of code and make use of our `debug.c`.
The idea is that we can move the problematic piece of code over there and poke at it a bit more to see what's going wrong.
Let's copy lines 15-21 over into our main function as such:

```c
 1	#include "src/student_code.h"
 2
 3	int main() {
 4	    // Next we poke around at our expectations a bit
 5	    Person p2 = make_new_person(27, "Douglas Adamssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss", 42);
 6
 7	    //Next, we test to make sure it worked correctly
 8	    cr_assert(p2.age == 27); // Test age
 9	    cr_assert(strcmp(p2.name, "Douglas Adamssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss") == 0); // Note that we use the strcmp function
10	    cr_assert(p2.favorite_number == 42); // Test favorite number
11
12	    return 0;
13	}
```

After we've done this let's run a `make debug`, which calls a special make rule I've added that builds a debug executable.

```shell
[DOCKER] /tmp/hw/labs/lab1-debugging_with_gdb/ $ make debug
gcc -Wall -lcriterion -I/opt/homebrew/Cellar/criterion/2.4.1_2/include/ debug.c -o debug bin/student_code.o
debug.c: In function 'main':
debug.c:8:5: warning: implicit declaration of function 'cr_assert' [-Wimplicit-function-declaration]
    8 |     cr_assert(p2.age == 27); // Test age
      |     ^~~~~~~~~
debug.c:9:15: warning: implicit declaration of function 'strcmp' [-Wimplicit-function-declaration]
    9 |     cr_assert(strcmp(p2.name, "Douglas Adams") == 0); // Note that we use the strcmp function
      |               ^~~~~~
debug.c:2:1: note: include '<string.h>' or provide a declaration of 'strcmp'
    1 | #include "src/student_code.h"
  +++ |+#include <string.h>
    2 |
/usr/bin/ld: /tmp/cc2m428F.o: in function `main':
debug.c:(.text+0x44): undefined reference to `cr_assert'
/usr/bin/ld: debug.c:(.text+0x6c): undefined reference to `cr_assert'
/usr/bin/ld: debug.c:(.text+0x80): undefined reference to `cr_assert'
collect2: error: ld returned 1 exit status
make: *** [Makefile:21: debug] Error 1
```

Oh.
Something went wrong.
It's always good to start at the beginning and start working down because often the first bug cascades into causing other ones.

The first warning we see is `debug.c:8:5: warning: implicit declaration of function 'cr_assert'`.
This is saying that our testing code isn't included.
This `cr_assert` is how we actually make the assertions in our unit tests.
Since this is us trying to isolate a problem, let's assume our testing framework is good and not use `cr_assert`.
Let's go through and instead change all of our `cr_assert` statements to `printf` to print out their results.
This makes our tests look like the below:

```c
printf("%d\n", (p2.age == 27)); // Test age
printf("%d\n", (strcmp(p2.name, "Douglas Adams") == 0)); // Note that we use the strcmp function
printf("%d\n", (p2.favorite_number == 42)); // Test favorite number
```

Don't forget to include `stdio.h`.
Also, note that we are printing out decimals instead of booleans because booleans don't properly exist in C.

Running this again we see we've still got an issue, but GCC has suggestions for how to fix it.
```shell
[DOCKER] /tmp/hw/labs/lab1-debugging_with_gdb/ $ make debug
mkdir -p bin
gcc -Wall -lcriterion -I/opt/homebrew/Cellar/criterion/2.4.1_2/include/ -c src/student_code.c -o bin/student_code.o
gcc -Wall -lcriterion -I/opt/homebrew/Cellar/criterion/2.4.1_2/include/ debug.c -o debug bin/student_code.o
debug.c: In function 'main':
debug.c:10:21: warning: implicit declaration of function 'strcmp' [-Wimplicit-function-declaration]
   10 |     printf("%d\n", (strcmp(p2.name, "Douglas Adams") == 0)); // Note that we use the strcmp function
      |                     ^~~~~~
debug.c:3:1: note: include '<string.h>' or provide a declaration of 'strcmp'
    2 | #include "src/student_code.h"
  +++ |+#include <string.h>
    3 |
```

We can just follow it's suggestions and add in the `string.h` library and we should be good to go:

```shell
[DOCKER] /tmp/hw/labs/lab1-debugging_with_gdb/ $ make debug
gcc -Wall -lcriterion -I/opt/homebrew/Cellar/criterion/2.4.1_2/include/ debug.c -o debug bin/student_code.o
[DOCKER] /tmp/hw/labs/lab1-debugging_with_gdb/ $ ./debug
*** stack smashing detected ***: terminated
Aborted
```

We can now cleanly compile but we're still failing.
Time to move onto figuring out what's going on!

***Note:*** 
It might not fail here, especially if you have an intel based machine, but keep reading!

***TODO:*** Take a screenshot of your debug.c and paste it into your google document.

## Step 7: GDB

The first tool we'll be using is [GDB](https://www.sourceware.org/gdb/), aka the GNU Project Debugger.
To start up GDB we simply type `gdb [program name]` and it launches the debugger with that program as it's input.

```shell
[DOCKER] /tmp/hw/labs/lab1-debugging_with_gdb/ $ gdb debug
GNU gdb (Ubuntu 12.1-0ubuntu1~22.04) 12.1
Copyright (C) 2022 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "aarch64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from debug...
(No debugging symbols found in debug)
(gdb)
```

This show us an output explaining a little bit about GDB and then drops us as a `(gdb)` prompt where we can enter commands.

The idea behind GDB is that it allows us to set breakpoints and see memory variables.
It also, critically, allows us to see a backtrace of what went wrong.
This backtrace is usually a good first step to figuring out what's happening and gives us an idea of where we can set breakpoints to isolate problems.

To see this we first need to run our program, so at this prompt type in either `run` or just `r` (if you're in a rush).
You should see something like the below:

```shell
(gdb) run
Starting program: /tmp/hw/labs/lab1-debugging_with_gdb/debug
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/aarch64-linux-gnu/libthread_db.so.1".
*** stack smashing detected ***: terminated

Program received signal SIGABRT, Aborted.
__pthread_kill_implementation (threadid=281474842214432, signo=signo@entry=6, no_tid=no_tid@entry=0) at ./nptl/pthread_kill.c:44
44	./nptl/pthread_kill.c: No such file or directory.
```

***Note:***
It seems that sometimes the stack smashing fails right here and instead your program completes normally.
If that happens to you then I'm sorry I didn't succeed in causing an error on your computer, and I'd love to try to figure out why so stop by office hours sometime.
In the meantime, just read along for the next section until we get to [Section 3b where we recompile and set a breakpoint](#step-3b-compiling-for-gdb).

What we see is that the program still crashes (sometimes it doesn't because gdb makes a few tweaks to memory layout to simply debugging), and is killed.
To see a bit of information about _why_ let's call `backtrace` (or `bt`) to ask what sequence of calls was made.
(You can also specify a number of functions to report back, but for now let's just use it without this).

```shell
(gdb) backtrace
#0  __pthread_kill_implementation (threadid=281474842214432, signo=signo@entry=6, no_tid=no_tid@entry=0) at ./nptl/pthread_kill.c:44
#1  0x0000fffff7e4f254 in __pthread_kill_internal (signo=6, threadid=<optimized out>) at ./nptl/pthread_kill.c:78
#2  0x0000fffff7e0a67c in __GI_raise (sig=sig@entry=6) at ../sysdeps/posix/raise.c:26
#3  0x0000fffff7df7130 in __GI_abort () at ./stdlib/abort.c:79
#4  0x0000fffff7e43308 in __libc_message (action=action@entry=do_abort, fmt=fmt@entry=0xfffff7f237a8 "*** %s ***: terminated\n")
    at ../sysdeps/posix/libc_fatal.c:155
#5  0x0000fffff7ec5898 in __GI___fortify_fail (msg=msg@entry=0xfffff7f23790 "stack smashing detected") at ./debug/fortify_fail.c:26
#6  0x0000fffff7ec5864 in __stack_chk_fail () at ./debug/stack_chk_fail.c:24
#7  0x0000aaaaaaaa0a64 in make_new_person ()
#8  0x0000aaaaaaaa0944 in main ()
```

To read this we start from the bottom and read upwards (or at least I do), to dig into the execution of the program.
This let's us see which of our functions caused a problem, and which are caused by other libraries.
I see that we are in `main ()` and then `make_new_person ()`, and then above that is something called `__stack_chk_fail ()`.
That, paired with the error saying "stack smashing detected" seems to be saying that something is messing around with the stack and causing some check to fail.
That's weird.

Let's look at this program a bit more by checking out the memory at that `make_new_person ()` call:

```shell
(gdb) x/5i 0x0000aaaaaaaa0a64
   0xaaaaaaaa0a64 <make_new_person+116>:	mov	x0, x2
   0xaaaaaaaa0a68 <make_new_person+120>:	mov	x1, x3
   0xaaaaaaaa0a6c <make_new_person+124>:	ldp	x29, x30, [sp], #64
   0xaaaaaaaa0a70 <make_new_person+128>:	ret
   0xaaaaaaaa0a74 <_fini>:	nop
```

In this command we're saying to show us the memory (`x`) and to show the next 5 instructions (`/5i`) after our particular memory location.
Note that we can also add in offsets to our memory location (e.g. `0x0000aaaaaaaa0a64-5`) to show the instructions leading up to it, but it doesn't automatically do math for us leading to possible garbage results.

So I broke my promise again because we're now looking at assembly language.
And it's not even particularly useful because I don't know exactly what that means, and can't tell what it corresponds to in our program and what line needs to be fixed.
To remedy this we want to turn on debugging.

Quit gdb by running `quit`.

### Step 7b: Compiling for GDB

Let's do a slightly modification to our Makefile to have it compile with some extra information for gdb.
This is already turned on in the projects but I wanted to have an excuse to talk about it.
In your Makefile goto line 2 and after `-Wall` add in a `-g` flag so it reads:
```makefile
CFLAGS=-Wall -g -lcriterion -I/opt/homebrew/Cellar/criterion/2.4.1_2/include/ -I../common/ -I$(INCLUDE_DIR)
```

This flag will add in some extra information that gdb uses.

***TODO:*** What does this flag do?  Use the man pages or the `--help` flag to help you figure it out!

Recompiling with this flag by rerunning `make debug`, restart GDB as before, and re-run your program.
You should get the same error as before.
However, this time run the `backtrace` command and you'll see more information.

```shell
(gdb) backtrace
#0  __pthread_kill_implementation (threadid=281474842214432, signo=signo@entry=6, no_tid=no_tid@entry=0) at ./nptl/pthread_kill.c:44
#1  0x0000fffff7e4f254 in __pthread_kill_internal (signo=6, threadid=<optimized out>) at ./nptl/pthread_kill.c:78
#2  0x0000fffff7e0a67c in __GI_raise (sig=sig@entry=6) at ../sysdeps/posix/raise.c:26
#3  0x0000fffff7df7130 in __GI_abort () at ./stdlib/abort.c:79
#4  0x0000fffff7e43308 in __libc_message (action=action@entry=do_abort, fmt=fmt@entry=0xfffff7f237a8 "*** %s ***: terminated\n")
    at ../sysdeps/posix/libc_fatal.c:155
#5  0x0000fffff7ec5898 in __GI___fortify_fail (msg=msg@entry=0xfffff7f23790 "stack smashing detected") at ./debug/fortify_fail.c:26
#6  0x0000fffff7ec5864 in __stack_chk_fail () at ./debug/stack_chk_fail.c:24
#7  0x0000aaaaaaaa0a64 in make_new_person (age=27, name=0xaaaaaaaa0a90 "Douglas Adams", favorite_number=42) at src/student_code.c:15
#8  0x0000aaaaaaaa0944 in main () at debug.c:7
```

Whoa, that's a lot more information!
Now GDB is not only showing us what line is failing, but also the arguments being passed in!
That's much more useful.

### Step 7c: Stepping through code in GDB

Okay!  Now that we have actual information, let's try stepping through some code.
To do this run `break make_new_person` to set a breakpoint at the beginning of our make_new_person function, and then call `run`.

```shell
(gdb) break make_new_person
Breakpoint 1 at 0xa04: file src/student_code.c, line 9.
(gdb) run
Starting program: /tmp/hw/labs/lab1-debugging_with_gdb/debug
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/aarch64-linux-gnu/libthread_db.so.1".

Breakpoint 1, make_new_person (age=27, name=0xaaaaaaaa0a90 "Douglas Adams", favorite_number=42) at src/student_code.c:9
9	Person make_new_person(int age, char* name, int favorite_number) {
```

Now our program is stopped at the beginning of this function and we want to step through it looking at local variables.
To do this we use `step` and we use `info locals` to print out information on the local variables.

```shell
(gdb) info locals
p = {age = -134397524, name = "\377\377\000\000\270\366\377\377", favorite_number = 65535}

(gdb) step
11	    p.age = age;

(gdb) info locals
p = {age = -134397524, name = "\377\377\000\000\270\366\377\377", favorite_number = 65535}

(gdb) step
12	    strcpy(p.name, name);

(gdb) info locals
p = {age = 27, name = "\377\377\000\000\270\366\377\377", favorite_number = 65535}

(gdb) step
strcpy () at ../sysdeps/aarch64/strcpy.S:75
75	../sysdeps/aarch64/strcpy.S: No such file or directory.
```

We see that at first our locals are randomly initialized, as we would expect.
Wehn we step through line 11 (`p.age = age;`) we see that this was actually telling us the _next_ instruction, and so we don't see any change for a little bit, but eventually we see that `age = 27` shows up in the local variable.
Finally, the last bit is warning us that we've called another function and entered that.
Since we're trusting `strcpy` for now we want to skip through this function.
To do this we enter `finish` to skip over all of its steps.

```shell
(gdb) finish
Run till exit from #0  strcpy () at ../sysdeps/aarch64/strcpy.S:79
make_new_person (age=27, name=0xaaaaaaaa0a90 "Douglas Adams", favorite_number=42) at src/student_code.c:13
13	    p.favorite_number = favorite_number;
(gdb) info locals
p = {age = 27, name = "Douglas ", favorite_number = 1835099201}
```

We see that we've finished copying over the string, but it's not the full string for some weird reason.
Instead, it's "Douglas " and then we've lost the "Adams".
It's also weird that our `favorite_number` field has now changed, but that number was junk anyway, right?

If we keep stepping through our program we see that it sets our `favorite_number` correctly and we eventually start getting warnings that "stack smashing" has occurred.

```shell
(gdb) step
14	    return p;
(gdb) info locals
p = {age = 27, name = "Douglas ", favorite_number = 42}
(gdb) step
15	}
(gdb) info locals
p = {age = 27, name = "Douglas ", favorite_number = 42}
(gdb) step
__stack_chk_fail () at ./debug/stack_chk_fail.c:24
24	./debug/stack_chk_fail.c: No such file or directory.
(gdb) info locals
No locals.
(gdb) step
__GI___fortify_fail (msg=msg@entry=0xfffff7f23790 "stack smashing detected") at ./debug/fortify_fail.c:23
23	./debug/fortify_fail.c: No such file or directory.
```
It looks like something's probably wrong with that `strcpy`, but that's a library function so it must be something we're doing to call it.
Hmmmm.

***TODO:*** Take a screenshot of you walking through gdb like the above and paste it into your google document.


## Step 8: Looking at our code

Based on what we've seen until now we know that something is wrong with how we're using the `strcpy` function.
Even though it's a library function it's somehow messing something up.
The biggest hint we have is that it's somehow dropping the "Adams" part of "Douglas Adams" when using `strcpy`, and changing whatever is after that in memory.

This hint points us to something to do with buffer sizes.
Usually when we see that:
1. Something is cutoff mysteriously, and
2. Something directly around it in memory is changed, and

Then it means that something has overflowed a buffer.

So let's look at our buffers by looking at our `student_code.h` file.
This is in the `include/` directory instead of our `src/` directory.
We already looked at this file before, but let's look at it again.

```c
1	#ifndef PROJECTS_STUDENT_CODE_H
2	#define PROJECTS_STUDENT_CODE_H
3
4	typedef struct Person {
5	    int age;
6	    char name[8];
7	    int favorite_number;
8	} Person;
9
10	/**
11	 * This function takes in an age, a name, and a favorite number and returns a person
12	 * @param age integer representing age
13	 * @param name character string representing name (at most 7 chars long!)
14	 * @param favorite_number integer representing favorite number
15	 * @return
16	 */
17	Person make_new_person(int age, char* name, int favorite_number);
18
19	#endif //PROJECTS_STUDENT_CODE_H
```

Okay, so we see we have a struct defined here, and then some docstring stuff, and then a function definition.
Looking at our struct we're particularly interested in line 10, because that's the buffer we're having trouble with.
We see that it's defined as a character array of length 8!
The name we're testing with is much longer than that!

Is that how many characters we're printing out?
```c
[DOCKER] /tmp/hw/labs/lab1-debugging_with_gdb/ $ echo "Douglas " | awk -F '' -v 'OFS=\n' '{$1=$1}1'  | cat -n
 1	D
 2	o
 3	u
 4	g
 5	l
 6	a
 7	s
 8
```

Hmm, we're getting 8 characters including our space, right?
So it looks like it's doing okay.
But what do we know about C strings?
We know that they should be null-terminated (i.e. end with a `\0`), so a string that's fit into an array of size 8 should only have 7 characters.
...but ours has a space in the 8th character.

So it seems like what might be happening is that we're copying a string that's too long into too small a location.
Let's try changing the size of this array to something bigger, say 1024, to allow for much longer names.

Making this change and re-running we see that our debug now runs successfully!

```shell
[DOCKER] /tmp/hw/labs/lab1-debugging_with_gdb/ $ make debug
gcc -Wall -g -lcriterion -I/opt/homebrew/Cellar/criterion/2.4.1_2/include/ debug.c -o debug bin/student_code.o
[DOCKER] /tmp/hw/labs/lab1-debugging_with_gdb/ $ ./debug
1
1
1
```

Let's try out our unit tests!
```shell
[DOCKER] /tmp/hw/labs/lab1-debugging_with_gdb/ $ make
rm -rf bin unit_tests debug
mkdir -p bin
gcc -Wall -g -lcriterion -I/opt/homebrew/Cellar/criterion/2.4.1_2/include/ -c src/student_code.c -o bin/student_code.o
gcc -Wall -g -lcriterion -I/opt/homebrew/Cellar/criterion/2.4.1_2/include/ unit_tests.c -o unit_tests bin/student_code.o
./unit_tests
[====] Synthesis: Tested: 1 | Passing: 1 | Failing: 0 | Crashing: 0
```

Hey that's great!
Our unit test is no longer crashing!
Success!

***TODO:*** Take a screenshot of running the passing unit test.


## Step 9: Commit our changes

After working on our code and fixing a bug, or getting another unit test to pass, it is always good practice to commit our code to our git repository.
This allows us to make sure that if we run into any problems when developing for the next test, or with our repo in general, we can simply roll back the changes.
You can search for more details on your own (hint: `git restore ...`), but for now we want to run a commit:

```shell
[DOCKER] /tmp/hw/labs/lab2/ $ git commit . -m "Commit after lab1"
[main 4dacf3c] Commit after lab1
 1 file changed, 1 insertion(+)
```

The command we are using is of the form `git commit [file or directory to commit] -m [message to include with the commit]`.
You should change your message to include useful information that you can look back on.

Every time you get a new test passing or finish an assignment or lab it is good practice to commit your code.
This also means if I push updates you won't run into as many issues.





### Conclusion

We've now walked through how to use GDB, at least in a basic way.
We've fixed a buffer overflow problem, and looked at how memory is represented in the computer.
This is how we can start debugging problems without `printf` statements, and even when our `printf` statements are failing!
GDB is incredibly powerful and can help us solve most runtime problems we run into in C, so long as we know what it's trying to tell us.
GDB has a ton of other features that I encourage you to explore.
Additionally, ChatGPT is a fairly good resource at GDB, although it might take a bit of wrangling to get a really good answer.


Finally, I have two followup questions!

***TODO:*** What step did we forget to do?  There was something I mentioned as important and then totally neglected to follow up on.  What is it?


***TODO:*** Is our solution a "safe" solution to the problem?  Does it prevent it from happening again?  What would be a better solution?  (Hint: it's mentioned in one of the linked pages here)


#### Last step: Submission of your google doc

Please submit your google doc where you've been collecting todos!


