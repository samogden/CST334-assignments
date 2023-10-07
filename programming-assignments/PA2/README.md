# CST334 Project 2

## Background

In this project we'll be making a process scheduling simulator!
Or rather, you'll be fixing my broken priority implementation and then adding in a whole lot of new features!
This means you'll have to trace through code to see what's going wrong, and adapt an existing codebase to make it work and improve it!
All while seeing how we can make simple choices for scheduling (hopefully!)

## Overview

## Getting started

### Setting up your environment

To get started, start up your docker environment like you did for [PA1](../PA1).
Don't forget to either stash or commit any unchanged docker files.

Start docker, navigate to your working directory and update it with a `git pull`.

Once you are all set, change to the appropriate directory for PA2.

Now you're ready to get started coding!

***Question:*** Get docker running and upload me a screenshot of you running `tree` in the code directory 


### Testing Code

To test your code you will run two commands; one of them will compile your code and the other will run the unit tests.

#### Building code

The same as before, you can us `make unit_tests` to build the unit tests, or just `make` to make and run the unit tests.
There are different times that you may want to do each of these steps.
Also, if you run into problems, you may want to call `make clean` to erase your old code.

If you run `make` on the starter code you'll get a huuuuuge output.  
If we cut it down a bit using a few tricks we've learned in class I can show you the last few lines of it:

```shell
[DOCKER] /tmp/programming/ $ make 2>&1 | tail -n5
[----]   The expression selected == p2 is false.
[----]
[FAIL] STCF::e1_e1_e0: (0.00s)
[====] Synthesis: Tested: 45 | Passing: 1 | Failing: 44 | Crashing: 0
make: *** [Makefile:17: all] Error 1
```

So we see that 44 tests are failing and one is passing.  
Oof.
But don't worry, there aren't 44 functions this time, I just broke down the tests a little bit more fine-grained this time around.

***Question:*** How many tests are there per function you have to write?  Give me the breakdown per function. 

#### A side note
I'm actively working to improve the output of the tests to be more clear about what is passing and what is failing.
It's taking a bit of time, but if nothing else there may be a `make grade` that can calculate your grade so far, assuming everything works out well.



## Assignment description


This assignment consists of a process scheduling simulation where there are a number of different ways of selecting the next job.
For the sake of simplicity, we are running each job in a series of time slices and then selecting a new job when appropriate.  
Note that this causes a few of our algorithms to behave slightly differently -- for example, SJF now has preemption happen for it, which can lead to slightly different behavior than we saw in class.

The core of this simulation happens in `process_scheduling.c` between lines 50 and 73:

```c
    while (!is_empty(processes_to_schedule) && curr_time <= MAX_TIME) {
        printf("TIME: %.2fs\n", curr_time);
        // While we still have processes to schedule, pick one and run it

        // First, get jobs that have actually started, based on their entry time
        PROCESS_LIST* entered_processes = copy_only_entered_processes(processes_to_schedule, curr_time);

        // to debug better, uncommenting the next line might help
        //print_contents(entered_processes);

        if (is_empty(entered_processes)) {
            printf("No jobs ready, skipping time slice");
        } else {
            // Call our function to select our next process to run, passing in a process variable
            // By passing in a process point we can ensure we're modifying the existing process
            process_to_run = params.process_selection_func(entered_processes);

            // Run a step of the simulation
            run_simulation_step(processes_to_schedule, process_to_run, curr_time, stats, params.time_slice);
        }

        // Jump forward the length of a time slice
        curr_time += params.time_slice;
    }
```

***Question:*** What data structure do we use to hold the processes?

Essentially, at each step we pick a model using our selection function (`params.process_selection_func(entered_processes);`) and then use that to run one simulation step.
Your goal in this assignment is to write these selection functions.

I should note that these model selection functions are selected in individual unit tests using some function pointer stuff.
You can check it out, but you just need to know that you have to write these functions.

***Question:*** How do we choose the highest priority job?


### Your task

Your job is to:
1. Write the metrics gathering and calculating functions.  I have a few of these written to track the progress of jobs and calculate our metrics at the end but I've left it up to you to figure out how to implement them.
2. Fix my priority scheduler implementation.  We didn't talk about priority scheduling directly in class but the idea is that the job with the highest priority should be scheduled first, regardless of when it came in or what other jobs there are -- it's very closely related to MLFQ scheduling.
3. Write a few more scheduling algorithms.  To do this you'll have to look at what functions are available to you, and very possibly write a few more!  (You will likely be adding a few extra functions of your own to `student_code.c` and `student_code.h` for this assignment!)

### Functions you'll be writing

```c
// Write metric tracking code (35 points total)
void finalize_stats(SCHEDULER_STATS* stats); // 20 points
void mark_process_start(SCHEDULER_STATS* stats, PROCESS* p, float curr_time, float time_slice); // 5 points
void mark_process_run(SCHEDULER_STATS* stats, PROCESS* p, float curr_time, float time_slice); // 5 points
void mark_process_end(SCHEDULER_STATS* stats, PROCESS* p, float curr_time, float time_slice); // 5 points

// Fix this for 15 points
PROCESS* priority_process_selector(PROCESS_LIST* pl); // 15 points

// Implement these for 30 points
PROCESS* fifo_process_selector(PROCESS_LIST* pl); // 6 points
PROCESS* rr_process_selector(PROCESS_LIST* pl); // 6 points
PROCESS* sjf_process_selector(PROCESS_LIST* pl); // 6 points
PROCESS* lifo_process_selector(PROCESS_LIST* pl); // 6 points
PROCESS* stcf_process_selector(PROCESS_LIST* pl); // 6 points
```

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
You might need to add a few extra functions, but every function mentioned above is 1-5 lines of code.
If you find yourself with a function longer than ~5 lines think if there may be an easier way, and go back to checking out priority scheduling...
