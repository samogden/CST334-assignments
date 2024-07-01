# CST334 Project: Process Scheduling

## Background

In this project we'll be making a process scheduling simulator!
Or rather, you'll be fixing my broken priority implementation and then adding in a whole lot of new features!
This means you'll have to trace through code to see what's going wrong, and adapt an existing codebase to make it work and improve it!
All while seeing how we can make simple choices for scheduling (hopefully!)

## Overview

## Getting started

Don't forget to run `git pull` before getting started!
You may need to use `git commit . -m "[your message here]"` first!

### Setting up your environment

To get started, start up your docker environment like you did for [PA1](../PA1).
Don't forget to commit any changed files and then pull the latest updates with a `git pull`.
Note: If you have changed certain files might get an error that you have a merge conflict.
There are instructions for fixing them online, such as from [github](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/addressing-merge-conflicts/resolving-a-merge-conflict-using-the-command-line).

Once you are all set, change to the appropriate directory for PA2.

Now you're ready to get started coding!


### Testing Code

To test your code you will run the `make` command.

#### Building code

The same as before, you can use `make unit_tests` to build the unit tests, or just `make` to make and run the unit tests.
There are different times that you may want to do each of these steps.
Also, if you run into problems, you may want to call `make clean` to erase your old code.

If you run `make` on the starter code you'll get a ***very*** long output.  
If we cut it down a bit using a few tricks we've learned in class I can show you the last few lines of it:

```shell
[DOCKER] /tmp/programming/ $ make 2>&1 | tail -n5
[----]
[FAIL] STCF::test_2proc_0entry_1entry_stcf: (0.00s)
-----------------------------------
[====] Synthesis: Tested: 51 | Passing: 1 | Failing: 50 | Crashing: 0
make: *** [Makefile:17: all] Error 1
```

So we see that 44 tests are failing and one is passing.  
Oof.
But don't worry, there aren't 44 functions this time, I just broke down the tests a little bit more fine-grained this time around.

#### A side note

You can check what tests are passing and which are failing with the `make grade` command.
This will list the tests that pass and fail, as well as an estimated grade.
Note, this might not be entirely accurate, but in general is very close to the actual grade.


## Assignment description


This assignment consists of a process scheduling simulation where there are a number of different ways of selecting the next job.
For the sake of simplicity, we are running each job in a series of time slices and then selecting a new job when appropriate.  
Note that this causes a few of our algorithms to behave slightly differently -- for example, SJF now has preemption happen for it, which can lead to slightly different behavior than we saw in class.

The core of this simulation happens in `process_scheduling.c` starting at line 21:

```c
while ( (! is_empty(incomplete_processes)) && (curr_time <= MAX_TIME) ) {

    // Get jobs that have actually started, based on their entry time
    PROCESS_LIST* entered_processes = get_entered_processes(incomplete_processes, curr_time);
    // Select a process using our function.
    // Note: this will be NULL if our entered_processes is empty
    PROCESS* selected_process = params.process_selection_func(entered_processes);

    // Start with a time slice that'll end the simulation
    float next_time_slice = FLT_MAX;

    if (params.time_quantum > 0) {
      // Then we have a defined time slice, and we respect that each time
      next_time_slice = params.time_quantum;
    } else {

      // Get the time until the next arrival
      float time_until_next_arrival = get_next_entry_time(processes_to_schedule, curr_time) - curr_time;

      if (selected_process == NULL) {
        // Then we want to jump ahead to the next job arrival time since there are no jobs (see note above)
        next_time_slice = time_until_next_arrival;
      } else {
        // Otherwise, if we are preemptable we only run until it arrives
        if (params.preemptable && time_until_next_arrival < selected_process->time_remaining) {
          next_time_slice = time_until_next_arrival;
        } else {
          // Otherwise, we simply run until the end of the job
          next_time_slice = selected_process->time_remaining;
        }
      }
    }

    if (next_time_slice < MINIMUM_TIME_QUANTUM) {
      next_time_slice = MINIMUM_TIME_QUANTUM;
    }

    if (selected_process != NULL) {
      run(selected_process, stats, curr_time);
      mark_last_used(processes_to_schedule, selected_process);
    }

    curr_time += next_time_slice;

    if (selected_process != NULL) {
      stop(selected_process, stats, curr_time);
    }

    // todo: fix this memory leak that I know is right here...
    incomplete_processes = get_incomplete_processes(processes_to_schedule);
  }
```

Essentially, at each step we pick a model using our selection function (`params.process_selection_func(entered_processes);`) and then use that to run one simulation step.
Your goal in this assignment is to write these selection functions.

I should note that these model selection functions are selected in individual unit tests using some function pointer stuff.
You can check it out, but you just need to know that you have to write these functions.

***Question:*** Dig into the assignment code a bit -- how do we choose the highest priority job in this code base?


### Your task

Your job is to:
1. Write the metrics gathering and calculating functions.  I have a few of these written to track the progress of jobs and calculate our metrics at the end but I've left it up to you to figure out how to implement them.
2. Fix my priority scheduler implementation.  We didn't talk about priority scheduling directly in class but the idea is that the job with the highest priority should be scheduled first, regardless of when it came in or what other jobs there are -- it's very closely related to MLFQ scheduling.
3. Write a few more scheduling algorithms.  To do this you'll have to look at what functions are available to you, and very possibly write a few more!  (You will likely be adding a few extra functions of your own to `student_code.c` and `student_code.h` for this assignment!)

### Functions you'll be writing

```c
// Write metric tracking code (35 points total)
void finalize_stats(SCHEDULER_STATS* stats); // 15 points
void mark_start(PROCESS* p, SCHEDULER_STATS* stats, float time_started); // 10 points
void mark_end(PROCESS* p, SCHEDULER_STATS* stats, float time_completed); // 10 points

// Fix this for 15 points
PROCESS* priority_process_selector(PROCESS_LIST* pl); // 15 points

// Implement these for 30 points
PROCESS* fifo_process_selector(PROCESS_LIST* pl); // 6 points
PROCESS* rr_process_selector(PROCESS_LIST* pl); // 6 points
PROCESS* sjf_process_selector(PROCESS_LIST* pl); // 6 points
PROCESS* lifo_process_selector(PROCESS_LIST* pl); // 6 points
PROCESS* stcf_process_selector(PROCESS_LIST* pl); // 6 points
```

***Question:*** Look at all the unit tests that are being run, specifically at the files.  What order do you think we should look at these unit tests in?  What suite should we consider first, and what suite should we consider last?  Why?

## Where to start

I strongly recommend starting by looking at the `priority_process_selector` function that needs fixing.
Look at what it's doing and what functions it is using.
You need to fix it anyway, and it gives a pattern for a way to approach the other selectors.

## What to submit

You'll be submitting ***only*** `student_code.c` and `student_code.h`.
Any other files changed will be lost during the grading process.

## Other considerations

This project is much bigger than the previous projects you've tried -- before you were writing more or less all the code yourself but now you are given a fair bit of code.
It is structure as what is essentially a library in C, where I provide a number of structs and functions that act on those structs -- almost like objects in object-oriented languages.

To approach this project you don't need to understand all of the code in all of the provided files, but you should be aware of what functionality is available.
This functionality is provided by way of the associated header (e.g. `.h`) files, that list the available structs and functions.
Similar to `student_code.h`, these list the functions that the outside world can see and give a sense of how to use it.

Therefore, I strongly recommend you check out `process.h`, `process_list.h`, and `process_scheduling.h` as these may alert you to some helpful functions that you can use -- I use one of them in the `priority_process_selector function`


## Conclusion

Good luck!
Remember, using your debugging skills will come in useful!  
Reading the code may help you think about how we schedule in this system.

p.s. - due to the timing there isn't an extra credit part to this assignment (as far as I'm aware).  Next time!

## A hint...

This assignment actually doesn't require much code.
You might need to add a few extra functions as a helper function, but once you have that helper then all the `selector` functions above are 1-5 lines of code.
If you find yourself with a function longer than ~5 lines think if there may be an easier way, and go back to checking out priority scheduling...

## Another hint...

Don't forget to check out the functions available to you already!
You can see the functions that I wrote available in the `*.h` files provided!
While you can only change `student_code.c` and `student_code.h`, you are more than welcome (and encouraged) to use any functions you find in any of the `.h` files that seem useful!


