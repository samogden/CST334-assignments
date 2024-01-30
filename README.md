# CST334-assignments


This repository contains code for CST334 (Operating Systems) at CSUMB.
This repository will be used both for in-class work and homework assignments.

## Organization

- [programming-assignments](programming-assignments) contains the starter code for programming assignments assigned as homework.
- [labs](labs): contains starter code and instructions for labs to be completed in class.
- [demos](demos): contains code used for demos in class.
- [helpers](helpers): contains a number of helper scripts, generally related to grading homework.  

## Working ahead

Note that while you are welcome to work ahead, programming assignments are not guaranteed to be considered "stable" until they are assigned.
Therefore, you are welcome to get an early start but make sure you test before you submit assignments to ensure they still work.

## Helpful hints

- When working through assignments make sure that you commit your code consistently.  It is recommended that for programming assignemnts you run a `git commit ...` command every time you get a new unit test to pass.  This ensures that if new changes lead to your code compiling you can always either submit your old version or roll back to a known good checkpoint.
  - If you are unfamiliar with `git` there are plenty of resources available online, such as [this one about git commit](https://www.git-tower.com/learn/git/commands/git-commit).  Don't hesitate to ask google or LLMs about git usage (altough I've been seeing memes recently about ChatGPT deleting repos so heads up)
- To update to the latest version of the code you will be using the `git pull` command.  This might result in what is called a `merge conflict` so make sure you read the outputted text closely!
  - Same as above, google is your friend as git is widely used and there are plenty of good resources
- In general there are three commands we will be using when checking whether the homework is working.  I have written them below in order of preference for debugging homework.
  - `make clean unit_tests && ./unit_tests`
    - This will erase old files, build the code and then, if the build succeeded, run the new code.  Don't forget to check output for errors!
  - `make`
    - This will erase old files, build the code and then, if the build succeeded, run the new code.  Don't forget to check output for errors!
  - `make grade`
    - This will report what unit tests you are passing/failing, and then will try to calculate a grade.  It's the same script I use for grading, but I don't always set up the grading before the project is due.  
    - ***Note***: The error reporting in this command is very difficult to understand and should only be used for reference, not as a many debugging command