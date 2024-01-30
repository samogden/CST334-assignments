# CST334 Project: Intro to C

## Background

In this project we're going to be mostly playing around with C to get a sense of how it works.
This means we'll not only be trying out building our own structs, but also will be making system calls, using libraries, and trying to find some erroneous calls.

## Overview

There are four parts to this homework, each worth a different amount of the overall grade.
These four are [strings](#strings), [system calls](#system-calls), [caesar cipher](#caesar-cipher), and [substitution cipher](#general-substitution-cipher-bonus-points).

Note that throughout the code there are a few questions that you should answer for the PA1 checkpoint.

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

***Question:*** What are the differences between these commands and the ones for lab1?  What do the differences mean?

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
***(25 points)***

Remember from class that Strings in C are null-terminated character arrays.
In this section you should practice using string functions and mimic them on your own.
Note that some of these functions (e.g. `copy_str` and `length_of_str`) are available in the c string library, but you should implement your own version of them.
I will reiterate this in the code itself, and use of these standard functions will result in a 0 for these problems.

#### Specific todos and point values

```c
int get_str_length(char* str);                      // 5 points
char* copy_str(char* str);                          // 5 points
void truncate_string(char* str, int new_length);    // 4 points
void to_uppercase(char* str);                       // 4 points
void to_lowercase(char* str);                       // 4 points
void find_first_index(char* str, char target);      // 2 points
void find_last_index(char* str, char target);       // 1 points
```

### Structs 
***(25 points)***

Structs in C are contiguous memory objects, where we group together more primative object types to make more complex types.
They are similar to objects in object-oriented languages, but consist of only the data instead of the associated functions as well.
With that said, we can also have functions associated with them, albeit with a more verbose usage (i.e. a longer and more explicit set of input parameters).
In this section we'll practice both designing new structs, but also see how to use them and how to make functions for them.

#### Specific todos and point values

```c
struct Group;                                                       // 5 points
Person person_make_new(char* first_name, char* last_name, int age); // 4 points
char* person_to_string(Person person);                              // 2 points
Group group_make_new(char* group_name);                             // 3 points
int num_people_in_group(Group* group);                              // 2 points
int free_spaces_in_group(Group* group);                             // 4 points
int add_person(Group* group, Person* person_to_add);                // 4 points
int remove_person(Group* group, Person* person_to_remove);          // 1 point
```

***NOTE:***
You will need to change the `struct Group` definition in `student_code.h` to pass the unit tests.
The `void*` types are placeholders for you to change in the struct in order to get unit tests to pass.

### Caesar Cipher
***(30 points)***

C is ideal for low-level bit manipulation, making it perfect for playing around with encryption.
We're going to be doing this through the [Caesar cipher](https://en.wikipedia.org/wiki/Caesar_cipher), which is one of the earliest known encryption ciphers.
The core idea of a caesar cipher is that you "shift" the letter of the input by some amount.
For instance, a caesar cipher with shift of 1 would change 'a' to 'b' and 'z' to 'a'.

Your job is to implement these functions!

```c
char shift_left(char input_char, int shift_size);     // 10 points
char shift_right(char input_char, int shift_size);    // 10 points
void encrypt_caesar(char* input_str, int shift_size); // 5 points
void decrypt_caesar(char* input_str, int shift_size); // 5 points
```

### General substitution cipher (bonus points)
***(10 bonus points)***

This general substituion cipher will take in a list of shifts and make the appropriate replacements.
Since it is extra credit details are left to you to figure out, but some unit tests are provided.

```c
bool is_reversible(int[] encryption_key);                             // 4 points
int* get_decryption_key(int[] encryption_key);                        // 4 points
void encrypt_substitution(char* input_str, int[] encryption_key);     // 1 point
void decrypt_substitution(char* input_str, int[] get_decryption_key); // 1 point

```



## Conclusion

Good luck!
Remember, don't pour too much time into low-value functions!
Those are the ones that I expect to be the difficult or less important, but cool nevertheless!
