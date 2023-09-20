# CST334 Project 1

## Background

In this project we're going to be mostly playing around with C to get a sense of how it works.
This means we'll not only be trying out building our own structs, but also will be making system calls, using libraries, and trying to find some erroneous calls.

## Overview

There are four parts to this homework, each worth a different amount of the overall grade.
These four are [strings](#strings), [system calls](#system-calls), [structs](#structs), and [processes](#processes).

Note that each of these sections has a few questions at the beginning of them that you should answer for the Programming Assignment #1 Checkpoint on Canvas.

## Getting started

### Setting up your environment

To get started move to the same directory where you did your lab work.
We will be running similar, but slightly different, commands to get started on this assignment.

Before we get started, let's check for updates to the docker image by running:
```shell
docker pull samogden/csumb:cst334
```

Then, navigate using your terminal on your local machine to your working directory (i.e. the github repo `CST334-assignments`) and run the below command to start docker:
```shell
docker run -it -v ${PWD}:/tmp/programming samogden/csumb:cst334
```

***Question:*** What are the differences between these commands and the ones for lab1?  What do they mean?


Once the docker shell starts change to the appropriate directory (e.g. run `cd programming`) and update your github files:
```shell
git stash
git pull
git stash pop
```

Note: these git instructions might give you an error talking about different users.
This is a side effect of the new docker image I recently pushed (and you pulled).
Take the steps advised in them in this case, but in future cases you might not want to ignore such warnings.

And then change to the appropriate directory:
```shell
cd /tmp/programming/programming-assignments/PA1
```

Now you're ready to get started coding!


### Testing Code

To test your code you will run two commands; one of them will compile your code and the other will run the unit tests.

#### Building code

```shell
make clean unit_tests
```
The above command invokes the Makefile to do two things.
First, it cleans the local code, removing old compilations (by including the `clean` directive).
Second, it tells the system to build the unit_tests target.
If your system is taking a long time running this command (e.g. more than ~10 seconds) you simply run `make unit_tests` which will only rebuild when necessary.
We will be learning more about `make` in class in later weeks.

This command will show warnings when you first get it.
These warnings are there because I did some hacky things to make sure the code compiled with the `todo` hooks active -- looking at fixing them is a good way to get started on the assignment!

#### Running code

```shell
./unit_tests
```

This command runs the unit tests.
You will see that initially that there are a lot of failing tests -- in fact all of them fail.
There are also a few crashing tests -- these should be due to things that are necessary to fix later one.

The above lines will have `FAIL` and point you to the assertions that are failing.
Exploring the code to figure out _why_ these are failing will be helpful.

Note that if it helps you can also call `./unit_tests --help` to get more information on calling the unit tests.

Also, note that the tests do not yet have point values associated with them.
You will have to consult the below point values to calculate your score.

## Assignment components


### Strings 
***(21 points)***

Remember from class that Strings in C are null-terminated character arrays.
In this section you should practice using string functions and mimic them on your own.
Note that some of these functions (e.g. `copy_str` and `length_of_str`) are available in the c string library, but you should implement your own version of them.
I will reiterate this in the code itself, and use of these standard functions will result in a 0 for these problems.

***Question:*** How do we know that we've gotten to the end of a c-string?

#### Specific todos and point values

```c
int get_str_length(char* str);                      // 4 points
char* copy_str(char* str);                          // 4 points
void truncate_string(char* str, int new_length);    // 3 points
void to_uppercase(char* str);                       // 3 points
void to_lowercase(char* str);                       // 3 points
void find_first_index(char* str, char target);      // 2 points
void find_last_index(char* str, char target);       // 2 points
```

### Structs 
***(19 points)***

Structs in C are contiguous memory objects, where we group together more primative object types to make more complex types.
They are similar to objects in object-oriented languages, but consist of only the data instead of the associated functions as well.
With that said, we can also have functions associated with them, albeit with a more verbose usage (i.e. a longer and more explicit set of input parameters).
In this section we'll practice both designing new structs, but also see how to use them and how to make functions for them.

***Question:*** When thinking about fields in object-oriented programming and fields in c-structs what are the key differences?

#### Specific todos and point values

```c
struct Group;                                                       // 3 points
Person person_make_new(char* first_name, char* last_name, int age); // 3 points
char* person_to_string(Person person);                              // 2 points
Group group_make_new(char* group_name);                             // 3 points
int num_people_in_group(Group* group);                              // 2 points
int free_spaces_in_group(Group* group);                             // 2 points
int add_person(Group* group, Person* person_to_add);                // 3 points
int remove_person(Group* group, Person* person_to_remove);          // 1 point
```

***NOTE:***
You will need to change the `struct Group` definition in `student_code.h` to pass the unit tests.
The `void*` types are placeholders for you to change.

### Processes 
***(30 points)***

In class we will be learning about process management, where we start and stop processes.
The core of this will be handled by the OS but when using C there are two main functions that are essential for us to learn how to use well: `fork()` and `exec()`.

`fork()` starts a new process that is, at it's core, exactly the same as our process.
They have an identical memory layout and the same program state with two differences.
1. The PID of the child process is different.
2. The return code of `fork()` in the child is 0, while in the parent process it is the PID of the child process.

`exec()` will replace the existing process with a new one -- it completely erases the memory of the process and resets the PC back to start at the beginning of the process.
Calling it without `fork`'ing off a new process will lead to the original process being lost, so we need to start a new child process first.
Using it properly relies on checking error codes, and then getting the response of the child function.

***Question:*** What makes a process distinct from the program code?

#### Specific todos and point values

```c
int fork_and_return_child();    // 10 points
int fork_and_return_parent();   // 10 points
int make_exec_call(int* errno); // 10 points
```


### System Calls 
***(10 points)***

Below the standard library provided by `stdli.h` is a set of [system calls](https://man7.org/linux/man-pages/man2/syscalls.2.html) that allow direct interfacing with the operating system below.
This is how programs actually interface with the operating systems -- they make system calls and the operating system takes over to actually do the work.
Many of the calls are very specific, and often have wrappers of their own.
***In this section you need to call them manually, not with the wrappers, which I will work to call out whenever possible.***

There are some helpful instructions [here](https://jameshfisher.com/2018/02/19/how-to-syscall-in-c/).

One important thing to remember is that [different platforms use different numbers for system calls](https://stackoverflow.com/a/30291003), meaning that running on your computer and my computer requires you to use the symbolic constant instead of the system call number (e.g. `SYS_gettid` instead of [186](https://www.mail-archive.com/osv-dev@googlegroups.com/msg06206.html)).
This is part of how to make C more portable.

***Question:***: When we make system calls in C what are we doing?

#### Specific todos and point values

```c
FILE* open_file_to_read(char* path_to_file);        // 2 point
FILE* open_file_to_write(char* path_to_file);       // 2 point
FILE* open_file_to_readwrite(char* path_to_file);   // 1 point
void write_str_to_fid(char* str, FILE* fid);        // 2 points
char* read_str_from_fid(FILE* fid);                 // 2 points
void close_fid(FILE* fid);                          // 1 point
```

Note that for these functions you ***cannot*** use the "nice" file functions defined in `unistd.h` such as `fopen()` or `flcose()`.
Instead, you must use the systemcalls `open()` and `close()`.
The key difference is that functions that start with "f" are generally off limits.


## Conclusion

Good luck!
Remember, don't pour too much time into low-value functions!
Those are the ones that I expect to be the difficult or less important, but cool nevertheless!

p.s. - due to the timing there isn't an extra credit part to this assignment (as far as I'm aware).  Next time!

