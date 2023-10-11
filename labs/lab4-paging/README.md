# Lab 4: Paging

In this lab we get to practice our paging calculations.

This lab is going to be a mix of by-hand calculation and in-docker exploration of a simulation.  
As with all labs, feel free to work with classmates, friends, or external sources to get a better sense of the material!

Thanks to Dr. Glenn Bruns for this lab.

## Directions

For each of the questions below you should calculate the answer and show your work.
Please open up a google document to track your answers, and then when you are finished submit the google document.

## Backgrounf or all questions

We are going to assume the following;
- Pages are 256bytes in size
- There are 8 pages in the virtual address space
- There are 32 pages in the physical address space

## Question 1

### Questions 1a
How many bits do we need for the offset for each page?

### Question 1b
How many bits do we need to represent the pages in our virtual address space?

### Question 1c
How many bits do we need to represent the page frames in our physical address space?

### Question 1d
How many bits do we need to present our full virtual address space?

### Question 1e
How many bits do we need to represent our full physical address?

## Question 2
For this question we are using the below page table:

| **VPN** | **PFN**        |
|-----|------------|
| 000 | 0x8000000d |
| 001 | 0x80000006 |
| 010 | 0x8000001a |
| 011 | 0x80000005 |
| 100 | 0x8000000a |
| 101 | 0x00000000 |
| 110 | 0x8000001f |
| 111 | 0x00000000 |

In each row the leftmost bit says whether the VPN is valid or not.  
So if you see that the leftmost hex digit is 8, then is binary 1000, so the VPN is valid. 
Otherwise that virtual page is not valid.

Based on this table, please answer the following questions.

### Question 2a
Is VPN3 valid?

### Question 2b 
What is the PFN for VPN 1?

### Question 2c

Let's translate a virtual address to a physical address.  We'll try virtual address 0x06e1.  
In binary it looks like this:
```
110 1110 0001
```
What is the VPN for this address?

### Question 2d
How many offset bits in a physical address (in our scenario)?

### Question 2e
What is the PFN for the VPN in the virtual address above?

### Question 2f
Putting everything together, what is the physical address for the virtual address above? (`110 1110 0001`)

<details>
  <summary>Answer</summary>
  The physical address is this:

```
1 1111 1110 0001
```

Which is 0x1FE1 in hexadecimal.  
The VPN for the virtual address is 110 binary, which is 6 decimal.  
Looking at the page table, the row for VPN 6 is the seventh row, because we start counting at 0.

The value in the row starts with an 8, so VPN 6 is valid.  

What is the corresponding PFN?  
The value in the row is 1f, which in binary is 11111.  
This is the PFN corresponding to VPN 6.  
To get the virtual address we put the VPN in front of the offset.  
The offset is always the same in the virtual and the physical address.

</details>

### Question 2e

| ***Virtual Address*** | ***Physical Address*** |
|-----------------------|------------------------|
| 0x04d3                |                        |
| 0x030d                |                        |
| 0x0244                |                        |
| 0x0566                |                        |
| 0x03a7                |                        |
| 0x057c                |                        |
| 0x054b                |                        |
| 0x0110                |                        |
| 0x0624                |                        |
| 0x07db                |                        |
| 0x07c1                |                        |

### Suggestion

If you want to dig deeper there are a number of simulations in `/tmp/OSTEP/` in the docker image.
The calculations from this lab were in `HW-Paging-LinearTranslate` using the below call:

```shell
$ python2 paging-linear-translate.py -P 256 -a 2k -p 8k -c -s 10 -n12

```

There are also multi-level paging examples available as well.

## What to submit

Please submit your google document with your answers!