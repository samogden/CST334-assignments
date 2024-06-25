# Lab 4: VSFS

In this lab we'll be exploring VSFS a little bit more by using the simulation available in the docker container.

As usual, open a google document and record your progress.
You'll be submitting this document at the end of the lab.

Thanks to Dr. Glenn Bruns for this lab.

## Step 1.
Run “docker pull samogden/csumb:cst334” since I have very recently update the docker image

## Step 2
Start docker and go to the folder:
`/tmp/OSTEP/HW-VSFS`

## Step 3
Run the simulator with random seed 23:
```shell
$ python2 vsfs.py -s 23
```
Write down the operations that were used.  Remember, the possible operations are:
```shell
mkdir()
creat()
open(), write(), close()
link()
unlink()
```
You should identify both the operations and the parameters.

## Step 4
When you are finished, check your result by running:
```shell
$ python2 vsfs.py -s 23 -c
```

## Step 5
Repeat steps 2 and 3, but for random seed 26.

## Step 6
Run the simulator in reverse mode, with random seed 29:
```shell
$ python2 vsfs.py -s 29 -r
```

In your google document write down the states that result from the operations shown.

## Step 7
Check your answer by running the program again, but with the -c option.

## Step 8
Repeat steps 5 and 6, but this time with another seed of your choice

## Conclusion

Please submit your google document on canvas!
