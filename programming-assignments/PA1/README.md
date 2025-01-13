# CST334 Project 1: Intro to C

## Project Goals

1. Understand hiow C handles data, and how it is different from Object-Oriented languages (like C++ and Java)
2. Get comfortable writing C code, and ensure that your development environment is configured properly

## Overview

In this project we are developing a C library similar to the C++ and Java libraries for strings.
The core idea of this project is that in C we are directly dealing with data and have a very low-level view of what it is doing.
To support this we need to manually manage our memory, which is what you will be doing in this project.

Key sections in this document are:
- [Background](#background)
- [Getting Started](#getting-started)
- [Functions](#functions)

You can read more background in the [background](#background) section below.



## Background

Both of these languages are "object oriented" which means they approach coding by considering "objects" which combine data with functions that act upon that data, explicitly tying the two together.
That is, we can call functions directly on the object we are using.
This leads to libraries where you can have code along the lines of:

```java

String str = new Str("Hello");
str.append("!");

```

In contrast, C treats data and the functions that act upon it separately, where we can define data (which we refer to as `struct`s, short for "structures"), and then functions that can be called on the memory location of that data.
This leads to functions calls along the lines of:

```c

typedef String struct {
  char* data;
} String;

String str;
str.data = malloc(1024);
strcpy(str.data, "Hello");

append(&str, "!");
// Note: This is not how we are handling this in our library, but close enough for the demonstration. 

```

The difference for this is a little beyond this class, but essentially C is much more focused on processing data while Object-Oriented languages are instead focused on building structures with datas -- they act as an abstraction that we don't need when dealing with operating systems.



## Getting started

### Setting up your environment

To get started move to the same directory where you did your lab work.
We will be running similar, but slightly different, commands to get started on this assignment.

Before we get started, let's check for updates to the docker image by running:
```shell
docker pull samogden/cst334
```

Then, navigate using your terminal on your local machine to your working directory (i.e. the github repo `CST334-assignments`) and run the below command to start docker:
```shell
docker run -it --rm -v ${PWD}:/tmp/hw samogden/cst334
```

And then change to the appropriate directory:
```shell
cd /tmp/hw/programming-assignments/PA1
```

Now you're ready to get started coding!


### Testing Code

The easiest way to test your code is to run the below command:

```shell
make
```

This will, by default, compile the code and run the unit tests.
We will discuss in class what exactly a `make` command is and how they work, but for now this should get you going.

#### Alternative build commands

There are a few alternative build commands that are also potentially useful for you.
These will allow you to build and run the tests as separate steps, see the grading output of your tests, and check to see whether your code is passing a lint test.

##### Building and running as separate steps

To build your code and then run it, you will run the below two commands.

```shell
make clean unit_tests
./unit_tests -j1
```

The first command tells make to clean out your old code (which ensures any changes you made took), and then build the unit tests.
the second command runs the unit_tests executable one test at a time.
If you get an error on the second command that `./unit_tests` is not found then it is likely that your compilation failed and you should check the output of the first command for errors.

##### Grading your submission

Any submissions to canvas will be automatically graded within ~5 minutes but if you want to test your submission (and see what you might have left to work on) you can do so with the below command:

```shell
make grade
```

This will run the grading script and show you the results.
The output is not terribly well formatted and I have no intent to make it better formatted and so I strongly recommend using the plain `make` command for more helpful feedback.

##### Lint tests

You can get 1 point of extra credit on each assignment that passes a lint check.
A [lint check](https://en.wikipedia.org/wiki/Lint_(software)) is a check of how your code looks.
Some have more in-depth checks but these are making sure that you are following standard coding conventions.

You can run this test to see how your code is doing with the below command.
Note that the lint check is run as part of the `make grade` above.

```shell
make grade
```


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
./unit_tests -j1
```

This command runs the unit tests.
You will see that initially that there are a lot of failing tests -- in fact all of them fail.
There are also a few crashing tests -- these should be due to things that are necessary to fix later one.

The above lines will have `FAIL` and point you to the assertions that are failing.
Exploring the code to figure out _why_ these are failing will be helpful.

Note that if it helps you can also call `./unit_tests --help` to get more information on calling the unit tests.

Also, note that the tests do not yet have point values associated with them.
You will have to consult the below point values to calculate your score.


## Functions




## Conclusion

Good luck!
Remember, don't pour too much time into low-value functions!
Those are the ones that I expect to be the difficult or less important, but cool nevertheless!
