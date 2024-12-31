# CST334 Project: Process Scheduling

## Note

As a heads-up, assignments often change after I first write them and might become a little out of sync with this README file.
I will do my best to keep them up to date, but specific numbers of tests run might be different than what you see.

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
[DOCKER] /tmp/hw/programming-assignments/PA2/ $ make 2>&1 | tail -n5
[----]
[FAIL] STCF::test_2proc_0entry_1entry_stcf: (0.00s)
-----------------------------------
[====] Synthesis: Tested: 55 | Passing: 16 | Failing: 39 | Crashing: 0
make: *** [Makefile:22: all] Error 1
```

So we see that 39 tests are failing and 16 that are passing.
Oof.
But don't worry, there aren't 39 functions this time, I just broke down the tests a little bit more fine-grained this time around.

(As a note, the 16 that are passing are generally due to the "default" choice of process to schedule being correct, but you will still need to fix them to get the unit tests working overall.)

#### A side note

You can check what tests are passing and which are failing with the `make grade` command.
This will list the tests that pass and fail, as well as an estimated grade.
Note, this might not be entirely accurate, but in general is very close to the actual grade.


## Assignment description


This assignment consists of a process scheduling simulation where there are a number of different ways of selecting the next job.

The core of this simulation happens in `process_scheduling.c` starting at line 21:

```c
 1	SCHEDULER_STATS* main_simulation_loop(SCHEDULER_PARAMS params, SCHEDULER_STATS* stats, PROCESS_LIST* processes_to_schedule) {
 2
 3	  fprintf(stderr, "\nStarting processing loop\n");
 4	  float curr_time = 0.0f; // Record the current time of the simulation
 5
 6	  PROCESS_LIST* incomplete_processes = get_incomplete_processes(processes_to_schedule);
 7
 8	  while ( (! is_empty(incomplete_processes)) && (curr_time <= MAX_TIME) ) {
 9
10	    // Get jobs that have actually started, based on their entry time
11	    PROCESS_LIST* entered_processes = get_entered_processes(incomplete_processes, curr_time);
12	    // Select a process using our function.
13	    // Note: this will be NULL if our entered_processes is empty
14	    PROCESS* selected_process = params.process_selection_func(entered_processes);
15
16	    // Start with a time slice that'll end the simulation
17	    float next_time_slice = FLT_MAX;
18
19	    if (params.time_quantum > 0) {
20	      // Then we have a defined time slice, and we respect that each time
21	      next_time_slice = params.time_quantum;
22	    } else {
23
24	      // Get the time until the next arrival
25	      float time_until_next_arrival = get_next_entry_time(processes_to_schedule, curr_time) - curr_time;
26
27	      if (selected_process == NULL) {
28	        // Then we want to jump ahead to the next job arrival time since there are no jobs (see note above)
29	        next_time_slice = time_until_next_arrival;
30	      } else {
31	        // Otherwise, if we are preemptable we only run until it arrives
32	        if (params.preemptable && time_until_next_arrival < selected_process->time_remaining) {
33	          next_time_slice = time_until_next_arrival;
34	        } else {
35	          // Otherwise, we simply run until the end of the job
36	          next_time_slice = selected_process->time_remaining;
37	        }
38	      }
39	    }
40
41	    if (next_time_slice < MINIMUM_TIME_QUANTUM) {
42	      next_time_slice = MINIMUM_TIME_QUANTUM;
43	    }
44
45	    if (selected_process != NULL) {
46	      run(selected_process, stats, curr_time);
47	      selected_process->last_run = curr_time;
48	    }
49
50	    curr_time += next_time_slice;
51
52	    if (selected_process != NULL) {
53	      stop(selected_process, stats, curr_time);
54	    }
55
56	    delete_process_list(incomplete_processes);
57	    incomplete_processes = get_incomplete_processes(processes_to_schedule);
58	  }
59
60
61	  stats->completion_time = curr_time;
62	  finalize_stats(stats);
63	  print_stats(*stats);
64
65	  return stats;
66	}
```

Essentially, at each step we pick a model using our selection function (`params.process_selection_func(entered_processes);`) and then use that to run one simulation step.
Your goal in this assignment is to write these selection functions.

I should note that these model selection functions are selected in individual unit tests using some function pointer stuff.
You can check it out, but you just need to know that you have to write these functions.

***Question:*** Dig into the assignment code a bit -- how do we choose the highest priority job in this code base?

(Note: You may see these questions scattered throughout -- you don't need to answer them but they are often good to think about and usually are connected to tricky aspects of the PA.)

### Your task

Your job is to:
1. Write the metrics gathering and calculating functions.  I have a few of these written to track the progress of jobs and calculate our metrics at the end but I've left it up to you to figure out how to implement them.
2. Write some scheduling functions.  We didn't talk about priority scheduling directly in class but the idea is that the job with the highest priority should be scheduled first, regardless of when it came in or what other jobs there are -- it's very closely related to MLFQ scheduling.
   - To do this you'll have to look at what functions are being used and what is going on.  I'd recommend stepping through the scheduler loop and checking out each of the unit tests!

### Functions you'll be writing

```c
// Write metric tracking code (35 points total)
void finalize_stats(SCHEDULER_STATS* stats); // 15 points
void mark_start(PROCESS* p, SCHEDULER_STATS* stats, float time_started); // 10 points
void mark_end(PROCESS* p, SCHEDULER_STATS* stats, float time_completed); // 10 points

// Implement these
PROCESS* priority_process_selector(PROCESS_LIST* pl); // 15 points
PROCESS* fifo_process_selector(PROCESS_LIST* pl); // 6 points
PROCESS* rr_process_selector(PROCESS_LIST* pl); // 6 points
PROCESS* sjf_process_selector(PROCESS_LIST* pl); // 6 points
PROCESS* lifo_process_selector(PROCESS_LIST* pl); // 6 points
PROCESS* stcf_process_selector(PROCESS_LIST* pl); // 6 points
```

***Question:*** Look at all the unit tests that are being run, specifically at the files.  What order do you think we should look at these unit tests in?  What suite should we consider first, and what suite should we consider last?  Why?

***Note:***
There's a bunch more functions in `student_code.c` that you'll need to write along the way!

## Where to start

I strongly recommend starting by looking at the `priority_process_selector` function that needs fixing.
Look at what it's doing and what functions it is using.
You need to fix it anyway, and it gives a pattern for a way to approach the other selectors.

***Question:*** Draw out a picture of the layout of memory when we have a bit of it allocated.  Include all of the pointers in the nodes and indicate which will have to change when we split the node.

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


