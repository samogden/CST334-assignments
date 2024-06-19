# Lab 5: Anderson/Dahlin Method

In this lab we'll be constructing a thread-safe object with the Anderson/Dahlin method.
The core idea behind this method is that we want to incrementally update our code to first produce thread-safe code, and then produce code that leverages conditional variables.

The steps for doing so are:
1. add a single lock
2. add code to acquire and release the lock
3. add zero or more condition variables
4. add signal and broadcast calls
5. add wait calls within loops

I am providing basecode for you that is the general object, so it's up to you to do each of the steps!

Open up a google doc to save your progress for submission.

Thanks to Dr. Glenn Bruns for this lab.


## Step 0

Once you have started docker update your git repository with `git pull`.
Please refer to earlier labs if you need a reminder of how to get it set up.

## Step 1

The provided code already has the core functionality of the bounded buffer class.
Additionally, it has a lock that is initialized.
Now, you need to add in the code to lock and unlock it as necessary.

For this step, take a screenshot showing where we set up the lock and initialize it.
Please make sure to highlight these lines of code in some way and not just take a screenshot of the entire program.

## Step 2

The two functions that we are going to focus on are `sbuf_read` and `sbuf_write`, both of which are marked with `// todo`

To use the lock we want to be using the `pthread_mutex_lock` and `pthread_mutex_unlock` functions that we have discussed in class.
Add in the appropriate lock and unlock statements.

Run your code and take a screenshot of your code running along with of the edits you had to the program.

## Step 3

The 3rd step is to add in condition variables, and initialize them.
Similar to the lock, we've already done this step so take a specific screenshot of where they're set up and where they're initilized and add this to your google doc.

## Step 4

Condition variables have two sides -- those that wait and those that signal.
The waiting side will stop execution until a signal is generated, while a signal on a condition variable is non-blocking.
Based on this, we generally want to add in the signals first.

So, in this step add in any signal and broadcast calls on the condition variables.
These are made with the `pthread_cond_signal` and `pthread_cond_broadcast` calls.

These calls are often only made under certain conditions.
In our program, are there any specific conditions that we need to pay attention to?

Take a screenshot of three things:
1. Your code with the signal and broadcast calls added in
2. The output of running your code
3. A short description of the conditions under which our program wants to signal and broadcast.

## Step 5

Finally we get to add in our wait calls!
These are blocking so if we haven't added in our signal calls we might find a deadlock, but if we've followed the previous steps we should be safe!

Go through and add in your wait calls, making sure to put them in an appropriate `while` loop.
The call we are making is going to be `pthread_cond_wait`.
This while loop will be based off of what is being waited on -- for the reader this would be whether there's anything to read from the buffer.

Take a screenshot of your completed code, as well as it running and add that to your google doc.


## Step 6

Compare your results to the code in the [`solution`](./solution) folder and see how it looks!

## Conclusion

Please submit your google document on canvas!
