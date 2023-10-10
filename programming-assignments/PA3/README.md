# CST334 Project 3

## Assignment Description

In this project we're going to be writing a memory allocation library!
Similar to how C presents `malloc()` and `free()` we will be writing for `mem_alloc()` and `mem_free()`, and any functions we need to help implement them.

The general idea behind the approach that we're using is that we are allocating one large piece of memory (aka the "arena"), and then giving out smaller pieces of it as requested by calls to `mem_alloc()`, and returning these pieces to the general pool when `mem_free()` is called on them.
Setting up the arena and destroying it at taken care of for you, and may be some clues about the various pieces that are used in the memory arena.
Throughout the area we have a list of memory chunks including whether they are free or not.

On a call to `mem_alloc()` there are a few steps that need to be done.
First, we need to find an appropriate piece of memory.
In this allocator we are using a find-first approach, where we grab the first available piece of memory that is suitably sized.
After this, we adjust its size, if necessary, by potentially forming a new element in our list of memory allocations.

On a call to `mem_free()` we need to take the input pointer, determine its length and free up that much memory.
We need to update this chunk, and possibly "coalesce" it, where we combine it with the surrounding empty chunks.


### Splitting chunks

When we need to create a new node in our free list we need to split a chunk into smaller pieces.
To do this we need to create a new node within the chunk that gives us enough room for _both_ the size of the object we want to allocate and the new header we are allocating.

### Coalescing chunks

When we have two chunks next to each other that are free, we want to combine them in order to allow us to allocate bigger objects.
The idea, is that we have a list of nodes tracking whether they are free or not, and we want to combine two nodes together, similar to the picture below.

```
-----------------------------------------------------
| node0 hdr | freed space | node1 hdr | freed space | 
-----------------------------------------------------
-->
-----------------------------------------------------
| node0 hdr | freed space                           | 
-----------------------------------------------------
```

### Your task

You will be writing the pieces that find free memory, split chunks, free chunks, coalesce chunks, allocate, and free memory!

Also, there are a few questions scattered throughout the source code that you need to answer for the checkpoint this week!
I've labeled them with "question".
Note that these are not _just_ in `student_code.*`.

### Functions you'll be writing

```c
node_t * find_first_free_chunk(size_t size, node_t* starting_node); // 15 points
void split_node(node_t* node, size_t size);                         // 20 points
node_t* get_header(void* ptr);                                      // 15 points
void coalesce_nodes(node_t* front, node_t* back);                   // 20 points

extern void* mem_alloc(size_t size);                                // 5 points
extern void mem_free(void *ptr);                                    // 5 points
```

Note, you'll be using the first four functions to build the last two functions.  
Think about how to use this to de-duplicate your code as much as possible!

Another note:
Some of these functions will be setting error codes!  Do not use the raw numbers for this -- instead, use the error codes from `student_code.h`!  
Failure to do so will result in a points deduction.

### Getting started

Setting up this project is very similar to [PA1](../PA1) and [PA2](../PA2), so please check those out if you have questions!

A thing to note is that `mem_alloc()` and `mem_free()` rely on the other functions, so starting on the other functions is a good idea!

## What to submit

You'll be submitting ***only*** `student_code.c` and `student_code.h`.
Any other files changed will be lost during the grading process.


## Conclusion

Good luck!
