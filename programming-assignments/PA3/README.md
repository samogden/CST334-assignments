# CST334 Project: Let's build an MMU!

## Assignment Description

In this project we're going to build an MMU!

### Your task

You will be writing the pieces that find free memory, split chunks, free chunks, coalesce chunks, allocate, and free memory!

Also, there are a few questions scattered throughout the source code that you need to answer for the checkpoint this week!
I've labeled them with "question".
Note that these are not _just_ in `student_code.*`.
Also, please remember the context of how you are answering them, in that the goal is to make you dig through the code and think about it a bit.

### Functions you'll be writing

```c
/* Page Helpers */ // 20 points total
bool is_entry_valid(PageTableEntry pte); // 5 points
bool is_read_enabled(PageTableEntry pte);  // 5 points
bool is_write_enabled(PageTableEntry pte);  // 5 points
bool is_execute_enabled(PageTableEntry pte);  // 5 points

/* MMU Helpers*/ // 20 points
PFN convert_PageTableEntry_to_PFN(PageTableEntry pte); // 10 points
PFN find_free_page(MMU m); // 10 points

/* Page Table Functions */ // 20 points
PageTableEntry get_pagetableentry__MMU_pagetable(MMU m, VirtualAddress vpn); // 10 points
void map_page__MMU_pagetable(MMU* m, VPN vpn, bool can_read, bool can_write, bool can_exec); // 10 points

/* End to End functions that are the same regardless of MMU type */ // 20 points
Page* get_page(MMU m, VirtualAddress a, bool for_read, bool for_write, bool for_execute); // 10 points 
char read_byte(MMU m, VirtualAddress va); // 5 points
void write_byte(MMU m, VirtualAddress va, char val); // 5 points
```

### Getting started

Setting up this project is very similar to the [previous programming assignments](../), so please check those out if you have questions!

In terms of order to developing functions, I recommend starting with the helper functions since they will make the rest of the functions much, much easier!

In terms of what is available to you, I suggest checking out the functions I'm providing in [`memory_management_unit.h`](./src/memory_management_unit.h).
They provide a lot of really useful functionality.

For getting familiar with the code, checkout out [`defines.h`](./src/defines.h).
It sets a lot of the sizes and datatypes in this project.
It might look complicated at first, but you can get ChatGPT to simplify it for you (and as a hint there's only like 2 datatypes I use throughout pretty much all of this project).

#### Page Table Layout

The pagetable in this system contains information similar to what we discussed in class and in labs.
However, there is one addition.
In addition to the leading bit representing whether a page is valid, there are 3 more bits that represent Read, Write, and eXecute.
You will be writing functions for these.


## What to submit

You'll be submitting ***only*** `student_code.c` and `student_code.h`.
Any other files changed will be lost during the grading process.

## Conclusion

Good luck!
