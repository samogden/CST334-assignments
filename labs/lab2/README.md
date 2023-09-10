# CST334 Lab 2

## Background

In this lab we'll be trying to debug some runtime issues in C to get a sense of how to approach fixing problems in our homework code.
Runtime issues in C are different than in many other languages, such as python, because by default C doesn't give us any hints as to what is wrong.
This allows it to run much faster, but is also much harder to understand.

In this lab we'll be talking about compilation flags and we'll be trying out two tools, `gdb` and `valgrind` to help is isolate memory issues and figure out what's going wrong.

## Getting Started

First things first, create a google document called "Lab2".
You will be saving screenshots and other responses in this document and submit it on canvas after we're done!


### Updates to Docker

For this lab, we'll be using our docker container.
I have made some changes, both to better clarify that docker is running and to include the debug tools that we're using so make sure to pull the latest version.

```shell
$ docker pull samogden/csumb:cst334
```

As a quick aside, notice how the above command has a `$` at the beginning of it.
This is not to be included in the command itself and is just there to indicate that this is text to be entered into a command line.
You may occasionally see a variation of it that starts with a `# ` that is often used to denote things run in a "root shell", where you have elevated privileges.
This looks similar to when we have comments so understanding the context is key!

After you have pulled the latest docker container, navigate to your working directory and start docker like you did for the last lab.

```shell
/Users/ssogden/repos/classes/CST334-assignments/
$ docker run -it -v ${PWD}:/tmp/lab samogden/csumb:cst334
[DOCKER] /tmp/ $ 
```

One thing to notice is that our prompt has now changed to more clearly differentiate that we're running within docker.
If you don't see that the line starts with `[DOCKER]` then something went awry so don't hesitate to reach out.

Don't forget to change to the mounted directory so we have access to our working files!


### Updates to git

This lab wasn't in your git repo during the last lab so to get it and the associated files you'll have to update your git repo.
To do this we run instructions similar to our [PA1](../../programming-assignments/PA1) to update our local code.
This code is the below:

```shell
git stash     # Save our changes to local files to the side
git pull      # Pull updates from github
git stash pop # Put our changes to local files back into place
```

After running these you should be told that you have a number of updates and lab2 should appear locally.

### Lab files

This lab is designed to be a very miniature version of the homework.
It has a [`src`](src) folder and a [`tests`](tests) folder, contianing source code and testing files respectively.
It also has a [`Makefile`](Makefile) that will build executables for you.
Itt has two other files, one of which we've seen in PA1 and the other which is new.

Let's dig into a few of these files now.

#### `unit_tests.c`

The first file we'll be looking at is [`unit_tests.c`](unit_tests.c), the source code of which we can see below

```shell
[DOCKER] /tmp/lab/labs/lab2/ $ cat -n unit_tests.c
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
[DOCKER] /tmp/lab/labs/lab2/ $ cat -n debug.c
     1	#include "src/student_code.h"
     2
     3	int main() {
     4	    return 0;
     5	}
```

Somehow I managed to make it even more boring than `unit_tests.c`.
We can see a similar structure here, where it includes our student code functions and then just exits.

This is intentional.  We want to keep this file fairly empty in order to move what we're currently debugging into there.
Essentially, it's a scratchpad where we're going to be looking at bugs more closely.

#### `src/student_code.c`

Now that we've looked a little bit at our general setup, let's look at the specifics of what our code does.
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

***TODO:*** Go check out the documentation for [strcpy](https://pubs.opengroup.org/onlinepubs/009696799/functions/strcpy.html).
Does anything jump out at you?

Overall, this looks pretty okay and basic.
`strcpy` is a standard function that so long as our strings are well-formatted should probably work.
Nothing setting off red flags yet, right?

## Lab Steps

### Step 1: Let's watch things break

Okay, so now that we've check out our various files, let's run our program and see how our tests are doing!
We run it by using the `make` command, which parses our Makefile.
Running it we get the below:

```shell
[DOCKER] /tmp/lab/labs/lab2/ $ make
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

***TODO:*** Take a screenshot of the `make` command failing and paste it into your google document.

#### Step 1a: Digging into what we're seeing

Let's try to parse out what happened.
To break this down a bit I'm going to pipe the output of make into `cat -n` to add line numbers, and then add in some artificial spacing for clarity.
The command has two parts.
`make 2>&1` means to run `make` and make stderr write to stdout (i.e. "combine file 2 to file 1").
`| cat -n` says "take the output of the previous command and pass it into `cat -n`", and `cat -n` just repeats back what is input with line numbers added in.

```shell
[DOCKER] /tmp/lab/labs/lab2/ $ make 2>&1 | cat -n
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

### Step 2: Checking out our unit tests.

The first thing we should do is go and find out where our tests are failing.
Let's check out our unit test file.

```c
 1	#include <criterion/criterion.h>
 2	#include "../src/student_code.h"
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

Because it's doing the same thing but failing more epically, let's just disable this test for now.
Set the `.disabled` to be `true` (and remember to turn it on again before submitting your homework!).

***TODO:*** Take a screenshot with the test disabled and paste it into your google doc.

#### Step 2a: let's see what happens when we've disabled that test
