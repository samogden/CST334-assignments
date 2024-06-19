# Lab 3: Paging

In this lab we get to practice our paging calculations.

This lab is going to be a mix of by-hand calculation and in-docker exploration of a simulation.  
As with all labs, feel free to work with classmates, friends, or external sources to get a better sense of the material!

Thanks to Dr. Glenn Bruns for this lab.

## Directions

For each of the questions below you should calculate the answer and show your work.
Please open up a google document to track your answers, and then when you are finished submit the google document.

## Background or all questions

We are going to assume the following;
- Pages are 256bytes in size
- There are 8 pages in the virtual address space
- There are 32 pages in the physical address space

## Question 1

### Questions 1a
How many bits do we need for the offset for each page?


<details>
  <summary>Answer</summary>

log2(256bytes) = 8bits for the offset

</details>

### Question 1b
How many bits do we need to represent the pages in our virtual address space?

<details>
  <summary>Answer</summary>

log2(8 pages) = 3bits for the VPNs

</details>

### Question 1c
How many bits do we need to represent the page frames in our physical address space?

<details>
  <summary>Answer</summary>

log2(32 pages) = 5bits for the PFNs

</details>

### Question 1d
How many bits do we need to present our full virtual address space?

<details>
  <summary>Answer</summary>

11bits = (8bits for the offset) + (3 bits for the VPNs)

</details>

### Question 1e
How many bits do we need to represent our full physical address?

<details>
  <summary>Answer</summary>

13bits = (8bits for the offset) + (5 bits for the PFNs)

</details>

## Question 2
For this question we are using the below page table:

| **VPN** | **PFN**      |
|---------|--------------|
| `000`   | `0x8000000d` |
| `001`   | `0x80000006` |
| `010`   | `0x8000001a` |
| `011`   | `0x80000005` |
| `100`   | `0x8000000a` |
| `101`   | `0x00000000` |
| `110`   | `0x8000001f` |
| `111`   | `0x00000000` |

In each row the leftmost bit says whether the VPN is valid or not.  
So if you see that the leftmost hex digit is 8, then is binary 1000, so the VPN is valid. 
Otherwise that virtual page is not valid.

Based on this table, please answer the following questions.

### Question 2a
Is VPN3 valid?

<details>
  <summary>Answer</summary>

For this, we look at the 4th entry (since we start indexing at 0), and see it is going to be `0x80000005`. 
The page table entry is `0x80000005` (`0b10000000000000000000000000000101`) has the leftmost bit as 1, so it is valid.
Note, I didn't convert this to binary except as an example, since the leading hex 8 indicates the leading bit is a 1.

Taking this, we know that our PFN is 5bits, which means we'd need 2 hex digits to represent it, so our PFN is 0x05`.

</details>


### Question 2b 
What is the PFN for VPN 1?

<details>
  <summary>Answer</summary>

In this case, VPN1 is going to have a page table entry of `0x80000006`, which is also valid, and has a PFN of `0x06`.


</details>


### Question 2c

Let's translate a virtual address to a physical address.  We'll try virtual address 0x06e1.  
In binary it looks like this:
```
110 1110 0001
```
What is the VPN for this address?


<details>
  <summary>Answer</summary>

In a previous question we identified how much of our address will be the VPN -- specifically, it will be the first 3bits.
So in this case, our VPN is going to be `110`. 

</details>

### Question 2d
How many offset bits in a physical address (in our scenario)?

<details>
  <summary>Answer</summary>

We know that the offset is the same in both the virtual and physical address spaces, so in both cases the offset is going ot be 8 bits.

</details>

### Question 2e
What is the PFN for the VPN in the virtual address above?


<details>
  <summary>Answer</summary>

In the example above we had VPN of `110`, which we see is `0x8000001f`.
From the leading `8` we see that it's a valid page, and then we want to grab out the appropriate part of the PFN.
In this case, since we know our PFN is 5bits (from above), that would be 2 hex digits, so `0x1f`.

</details>

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

Please complete the below table.  Note, adding extra columns may help you track things.

| ***Virtual Address*** | ***Physical Address*** |
|-----------------------|------------------------|
| `0x04d3`              |                        |
| `0x030d`              |                        |
| `0x0244`              |                        |
| `0x0566`              |                        |
| `0x03a7`              |                        |
| `0x057c`              |                        |
| `0x054b`              |                        |
| `0x0110`              |                        |
| `0x0624`              |                        |
| `0x07db`              |                        |
| `0x07c1`              |                        |


<details>

  <summary>Answer</summary>

| ***Virtual Address*** | Binary        | VPN | Page Table Entry | Valid? | PFN    | ***Physical Address*** |
|-----------------------|---------------|-----|------------------|--------|--------|------------------------|
| `0x04d3`              | 100 1101 0011 | 100 | `0x8000000a`     | yes    | `0x0a` | `0x0ad3`               |
| `0x030d`              | 011 0000 1101 | 011 | `0x80000005`     | yes    | `0x05` | `0x050d`               |
| `0x0244`              | 010 0100 0100 | 010 | `0x8000001a`     | yes    | `0x1a` | `0x1a44`               |
| `0x0566`              | 101 0110 0110 | 101 | `0x00000000`     | no     | N/A    | N/A                    |
| `0x03a7`              | 011 1010 0111 | 011 | `0x80000005`     | yes    | `0x05` | `0x05a7`               |
| `0x057c`              | 101 0111 1100 | 101 | `0x00000000`     | no     | N/A    | N/A                    |
| `0x054b`              | 101 0100 1011 | 101 | `0x00000000`     | no     | N/A    | N/A                    |
| `0x0110`              | 001 0001 0000 | 001 | `0x80000006`     | yes    | `0x06` | `0x0610`               |
| `0x0624`              | 110 0010 0100 | 110 | `0x8000001f`     | yes    | `0x1f` | `0x1f24`               |
| `0x07db`              | 111 1101 1011 | 111 | `0x00000000`     | no     | N/A    | N/A                    |
| `0x07c1`              | 111 1100 0001 | 111 | `0x00000000`     | no     | N/A    | N/A                    |
</details>

### Suggestion

If you want to dig deeper there are a number of simulations in `/tmp/OSTEP/` in the docker image.
The calculations from this lab were in `HW-Paging-LinearTranslate` using the below call:

```shell
$ python2 paging-linear-translate.py -P 256 -a 2k -p 8k -c -s 10 -n12

```

Note: to run this you'll have to either install python2 in your docker image or run a `docker pull ...` to get the latest image.

There are also multi-level paging examples available as well.

## What to submit

Please submit your google document with your answers!