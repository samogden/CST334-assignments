# CST334 Project 4: Databases and concurrency!

## Assignment Description

In this project we're going to do two things.
First, we're going to make a database be thread-safe by adding in locks and condition variables.
Second, we're going to make a webserver be multi-threaded and able to use the thread-safe database.

### Your task

You'll be doing two things.
1. You will be writing a set of funtions to implement read and write locks to make a database object threadsafe.  These functions should use both locks and condition variables.
2. You will be converting a webserver from being single-thread to multi-threaded


### Functions you'll be writing

In this assignment you'll be writing 5 functions.
Note that these funtions are used through the rest of the code in `student_code.c`, and only these 5 should be changed.

```c
void pass_to_client_handler(void* arg) {
  // todo: Convert this to run multi-threaded
  client_handler(arg);
}


void read_lock(PlayerDatabase* db) {
  // todo
}

void read_unlock(PlayerDatabase* db) {
  // todo
}

void write_lock(PlayerDatabase* db) {
  // todo
}

void write_unlock(PlayerDatabase* db) {
  // todo
}
```

#### Scoring

For this assignment, scoring works a little bit differently.  Instead of being scored on the individual functions, I have implemented tests that will test parts of how you implement the functions.
To accomplish thisI have implemented three sets of unit tests.
1. (40 points) [`unittests_locks.c`](tests/unittests_locks.c): contains lock-related unit tests and will evaluate each of your functions to determine if they utilize locks to protect data
2. (20 points) [`unittests_conditions.c`](tests/unittests_conditions.c): contains conditional variable unit tests and sees whether your code is appropriately waiting and checking for these
3. (20 points) [`unittests_server.c`](tests/unittests_server.c): tests for whether you have correctly implemented threading, and performs end-to end tests

#### Testing your code

Please note, I added in a number of waits for this code to allow for more accurate testing.
This means that unit tests can take much longer to run than on previous assignments.
Please be patient and consider disabling tests that you aren't currently working on.

### Getting started

Setting up this project is very similar to the [previous programming assignments](../), so please check those out if you have questions!

## What to submit

You'll be submitting ***only*** `student_code.c` and `student_code.h`.
Any other files changed will be lost during the grading process.

## Conclusion

Good luck!
