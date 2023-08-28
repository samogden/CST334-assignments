# CST334 Lab 1: Introduction to C

The goal of this lab is to get you used to programming in C in your local environment, as well as using a few of the C debugging tools when things go wrong!

Throughout there are a number of steps labeled ***TODO*** which contain instructors to copy something into your document.
When you get to these please follow the instructions.

## Step 0: Preparation

Make sure that you've gone through the steps to install docker and get it running as per the slides on canvas.

Additionally, create a google document (or microsoft word, or apple pages, if you prefer) titled "Lab 1"

### Step 1: Start Docker

First, navigate to your working directory and type in the following command:
```bash
docker run -it -v ${PWD}:/tmp/lab samogden/csumb:cst334
```

This will start docker and mount the current folder inside of it, giving us access to our shared files.

Next, run the below command to change directory.

```bash
cd /tmp/lab
```

Because this folder was mounted with the `-v ${PWD}:/tmp/lab` flag when we started the docker image it is shared with our host operating system allowing us to edit files locally and have the changes automatically appear in the docker image.


## Step 1: Downloading the starter code

Type the following into your terminal:
```bash
git clone https://github.com/samogden/CST334-assignments
```

This will download the a git repository containing the lab data files.
To change to the directory containing the files for this lab (including a copy of this file) run the below commands.

```bash
cd CST334-assignments
cd labs
cd lab1-intro_to_c
```

Note that you can run all of these commands on a single line as `cd CST334-assignments/labs/lab1-intro_to_c`.

## Step 2: Open the starter code

To open the starter code you should navigate in your host operating system (e.g. windows or OSX) to the same directory as your terminal instance is.
That is, in the directory you started docker in click folders until you are in the `lab1-intro_to_c` directory.

In this folder you will find a file called `bin_to_dec.c`.
Open it in your text editor of choice (e.g. TextEdit, SublimeText, Notepad++, or an IDE).

Looking at the starter code we see the below:

```C
 1  #include <stdio.h>
 2  #include <stdlib.h>
 3  #include <unistd.h>
 4
 5  #define MAXSTR 8
 6
 7  int main() {
 8
 9     // user input string
10     char s[MAXSTR];
11
12     // prompt for input if input from terminal
13     if (isatty(fileno(stdin))) {
14         printf("> ");
15     }
16
17     return 0;
18  }
```

The first three lines are include statements, which import libraries.
`stdio.h` is used for input (short for "Standard IO"), `stdlib.h` is standard libraries, and `unistd.h` is a set of miscellaneous functions and types that give access to the POSIX operating system API, which linux uses.

Line 5 uses the preprocessing command `#define` to define MAXSTR to be 8.
Preprocessing commands are widely used in C to perform functions early in the compilation process.
In fact, the `#include` commands in the first three lines are other examples of preprocessing commands.
Preprocessing commands can be identified because they always start with a `#`.
In this case, `#define MAXSTR 8` means that the preprocessor should go through the source code and replace `MAXSTR` with `8` wherever it sees it.
Define statements like this are often used for variables to set them to particular values, similar to global variables but with lower runtime requirements.

Line 7 declares our main function -- every C program needs a main function (although in the homework we see that we don't need to write them ourselves when running unit tests).
In C the main function should always have a return type of `int`.
The return value corresponds to the success or failure of our program -- 0 indicates a success and other positive values mean a warning or error.
Although not calling return is technically acceptable it is good practice to always include a return value, which we do on line 17.

Line 10 declares a character array of length `MAXSTR`, using the compiler directive we declared before to set the length.
Therefore, if we want a longer input string to be possible, we could simply increase the value of `MAXSTR`.

Lines 13-14 are set up to identify if we are using a `tty` or not -- this stands for `TeleTYpewriter`.
What it means is whether we are running the program by calling it in the terminal or automatically inputting text, something called "piping" which we will see a bit later.
Right now, if we detect that a user is typing text in we automatically output a right angle bracket followed by a space to give them a prompt to enter in a character.

***TODO:*** Take a picture of your texteditor with this file open and paste it into your Lab1 document.

## Step 3: Test compilation

Run the below command to test compilation.  

```bash
gcc -o convert bin_to_dec.c
```

This command invokes `gcc`, which is the [GNU C Compiler](https://gcc.gnu.org/), a widely used open source compiler for the C language.
We are issuing two commands to this compiler.
First, the `-o` flag is telling the `gcc` program what to name the output file -- in this case `convert`.
Second, we are passing in the name of the input C code, `bin_to_dec.c`.
When we do this, we are compiling our source code, `bin_to_dec.c` to a executable called `convert`.

This compilation should work without any errors.

## Step 4: Running our new program

To run our program we simply type:

```bash
./convert
```

We will get more into command line usage in the future but this tells our operating system to look in the current directory (nicknamed `.`) and run an executable named `convert`.
We have combined these two by using the slash (`/`).

The outcome of this is minimal, but you can see it as the addition of the angle bracket (`> `) at the far left of the next line.
It's small but this means our program is working!

***TODO:*** Take a screenshot of your terminal showing the program running and add it to your google document





