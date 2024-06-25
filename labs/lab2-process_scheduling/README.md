# Lab 2: Process Scheduling

In this lab we get to practice process scheduling, and consider how different approaches will lead to different outcomes.

This lab is a little bit different in that it's not going to be in terminal or docker, and you're going to be drawing things.

Thanks to Dr. Glenn Bruns for this lab.

## Directions

For each of the below steps you should calculate both the requested time -- either response time or turnaround time (TAT).
You should report these, and any calculations or drawings you used along the way, in a google document that you will submit.

In general, I strongly suggest drawing these out -- in the solutions provided you will notice that I did so.
Drawing them out dramatically helps the ability to figure out time without having to keep track of too many factors.


## Question 1a

Suppose two jobs arrive at the same time and each takes 2 minutes to run.  What is the average turnaround time under round-robin scheduling? 
Assume the jobs are run with very short time slices.

## Question 1b

Redo problem 1a, but this time suppose one job takes 2 minutes to run and the other takes 4 minutes to run.

## Question 2

Five batch jobs A through E arrive at a computer center at almost the same time.  
They have estimated running times of 10, 6, 2, 4, and 8 minutes.  
For each of the following scheduling algorithms, determine the average turnaround time:

1. non-preemptive first-come, first-served (use order 10, 6, 2, 4, 8)
2. shortest job first
3. round robin (assume the time slice is very small and context switching negligable)

Which of these scheduling policies had the lowest average turnaround time?

## Question 3

Work out an expression for average response time given jobs with execution times A,B,C using shortest-job first.  
Assume the jobs arrive at the same time. (We did something similar in class, but with average turnaround time.)

## Question 4

Suppose you have three jobs run A, then B, then C.  
What is the difference between average turnaround time and average response time for this schedule?

## Solutions

You can reference my solutions to this lab [here](https://docs.google.com/document/d/1jmmczQcVCLko6ZJR8EAMJW1zz5Ma32as/edit?usp=sharing&ouid=101263792352541733911&rtpof=true&sd=true).
Please only check them after you are done, or to see how I'm approaching the problem (i.e. through logs of pictures)
