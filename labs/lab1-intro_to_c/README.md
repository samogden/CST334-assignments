# CST334 Lab 1: Introduction to C

The goal of this lab is to get you used to programming in C in your local environment, as well as using a few of the C debugging tools when things go wrong!

Throughout there are a number of steps labeled ***TODO*** which contain instructions to copy something into your document.
When you get to these please follow the instructions.
You will turn in this document as a PDF when you are done.

A note on notation: I will use `0b1` to say "binary number with representation 1" to differentiate it from the decimal one.
A more complete example would be `0b10` which is equal to 2 in decimal.

## Step 0: Preparation

Make sure that you've gone through the steps to install docker and get it running as per the slides on canvas.

Additionally, create a google document (or microsoft word, or apple pages, if you prefer) titled "Lab 1"

### Step 1: Start Docker

First, navigate to your working directory in your terminal of choice (e.g. PowerShell on Windows or Terminal on macOS) and type in the following command:
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
10     char input_s[MAXSTR];
11     int output_val = 0;
12
13     // prompt for input if input from terminal
14     if (isatty(fileno(stdin))) {
15         printf("> ");
16     }
17
18     return 0;
19  }
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

Line 11 declares an int that will be our output value.
In `gcc` there is no guarantee that a value that is declared but not initialized (e.g. `int i;`) will have a reasonable value in it so we make sure to initialize it to 0.

Lines 14-15 are set up to identify if we are using a `tty` or not -- this stands for `TeleTYpewriter`.
What it means is whether we are running the program by calling it in the terminal or automatically inputting text, something called "piping" which we will see a bit later.
Right now, if we detect that a user is typing text in we automatically output a right angle bracket followed by a space to give them a prompt to enter in a character.

***TODO:*** Take a picture of your texteditor with this file open and paste it into your Lab1 document.

## Step 3: Test compilation

Run the below command to test compilation.  

```bash
gcc -o convert bin_to_dec.c
```

***Note:*** If this gives you an error or a warning then reach out to the teaching staff.  
You may not be correctly running docker and we'll be able to help get you sorted out pretty quickly.

This command invokes `gcc`, which is the [GNU C Compiler](https://gcc.gnu.org/), a widely used open source compiler for the C language.
We are issuing two commands to this compiler.
First, the `-o` flag is telling the `gcc` program what to name the output file -- in this case `convert`.
Second, we are passing in the name of the input C code, `bin_to_dec.c`.
When we do this, we are compiling our source code, `bin_to_dec.c` to a executable called `convert`.

This compilation should work without any errors.

Note, there is also a file called `Makefile` which contains an alternative way of compiling programs.
I will be mentioning it later in class but I encourage you to ask ChatGPT what it does.


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


## Step 5: Let's capture some user input!

We have a nice prompt being printed out but we aren't doing anything to read input.
After line 16 (i.e. after we check if we are using a tty but before we return) add the following two lines:

```C
scanf("%s", input_s);
printf("input: %s\n", input_s);
```

Make sure to make the indentation match as pretty code is much easier to debug!

These two lines do two things.
First, `scanf("%s", input_s);` calls the `scanf` function and passes it the format string `%s` as well as our string, `input_s`.
[Format strings](https://www.geeksforgeeks.org/scanf-in-c/#) in C specify how to to convert strings into variables and vice versa.
The format string `%s` specifically tells `scanf` that it will be reading a string.
The second argument `input_s` is our string, and it is where `scanf` will store what it reads in from the command line.

The second line is a `printf` statement, which is how we output text in C.
In this case we give it a format string `%s\n` which means it is going to be passed a string to output with a bit of text on either side.

***TODO:*** What does the `\n` at the end of the do?  Write your answer in your Lab1 document.

Compile with the same `gcc` command as before (or use the `Makefile` if you've asked ChatGPT about its usage) and re-run to test it out.

### Aside: Safety

We just did something unsafe when we were using `scanf` to read into a string.
When reading in a string using `scanf` C will copy as long a string as it can into the given character array, even if it is longer than the size of the array.
Our array, declared on line 10, is only `MAXSTR` long, so any input string longer than 7 will overwhelm it.

Why 7 characters when `MAXSTR` is 8?
Remember, strings in C have a null terminator character (`\0`) at the end of them and without it the string is technically malformed.
Given a long enough input you can cause what is called a "Segmentation Fault", which is when you access memory that you shouldn't access -- something we'll cover in more detail in future lectures.

## Step 6: String functions!

Assuming that our string is wellformed (see the note just above), we can now play with a few string functions.
The one we'll be using is `strlen` which, as the name suggests, tells us how long a string is.

Add the following two lines after we read and print out the input string:

```C
int length = strlen(input_s);
printf("length: %d\n", length);
```

Here we use a new format specifier, `%d`, which is how we print out decimals.
It should print out the length of our string.

Recompile (either via `gcc` or the `Makefile`) and test it running

### Compilation warnings!

Oh no!
There are compilation warnings.
While warnings still allow us to compile they often indicate that we'll run into problems down the line.
Therefore it's usually best to fix them early to prevent us from running into weird outcomes later.

```bash
$ gcc -o convert bin_to_dec.
c
bin_to_dec.c: In function 'main':
bin_to_dec.c:20:17: warning: implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
   20 |    int length = strlen(input_s);
      |                 ^~~~~~
bin_to_dec.c:4:1: note: include '<string.h>' or provide a declaration of 'strlen'
    3 | #include <unistd.h>
  +++ |+#include <string.h>
    4 |
bin_to_dec.c:20:17: warning: incompatible implicit declaration of built-in function 'strlen' [-Wbuiltin-declaration-mismatch]
   20 |    int length = strlen(input_s);
      |                 ^~~~~~
bin_to_dec.c:20:17: note: include '<string.h>' or provide a declaration of 'strlen'
```

What do these mean?
Well, as with most compilation warnings and errors it's always good to start at the very beginning and see what the error there is.

In this case it says that on like 20 we are using a function `strlen` that has been implicitly declared.
Implicit declarations of functions occur when you use them but the compiler doesn't know what they are.
This might mean that you define a function later on in your `.c` source file, or that you are using a function in another source code file and not importing the header file.

In this case `gcc` knows that `strlen` probably is, because it's a commonly used function, and tells us how to fix it -- we just need to include `string.h`.
We add this to the top of our file (right where `gcc` tells us to!) and try recompiling.

Success!  We should see something similar to the below:

```bash
$ ./convert
> 2134
input: 2134
length: 4
```

***TODO:*** Screenshot this output (using any input number you want) and copy it into your Lab1 document.


## Quick aside on converting binary numbers to 

As mentioned in lecture, part of what makes C so nice for operating systems is that it lets manipulate bits at a very low level.
Many languages have bit manipulation but in C it's an essential part of what we do.
Therefore it's helpful to start thinking about bits here and there.

In this case, we want to think about how to convert a number from binary to decimal.  
We know that if we have a number `0b1010` it means that we have `1 * 2^3 + 0 * 2^2 + 1 * 2^1 + 0 * 2 ^ 0`.
That is, each digit of the binary input is either 1 or 0 times the power of how far into the number it is.

We therefore need to figure out two things.
1. Whether each digit of the binary input is 1 or 0, and 
2. How large a power of 2 it is multiplied by.

For the first part we can do by checking to see if each of the input characters is either a 0 or a 1.
The second part we can do by keeping track of what the current power is -- or by using a trick of bit manipulation.
All of this should be within a for loop.


## Step 7: Control structures in C

Since many other languages are based on C the structure of control structures should be fairly similar.

As expected, for loops look like:
```C
for ( ; ; ) {
  // do things in a loop
}
```

Similarly, we expect conditionals to take the form of:

```C
if (condition) {
  // Then do this
} else if (other condition) {
  // Then do that
} else {
  // A third thing
}
```

So to check for whether a character is a `0` or a `1` we simply need to walk through the string and check the value of each character in the string.
The below does this.

```C
for (int i = 0; i < length ; i++ ) {
  if (input_s[i] == '0') {
    // todo 1
  } else if (input_s[i] == '1') {
    // todo 2
  } else {
    // todo 3
  }
}
```

The big thing to notice in this code is that we use `'0'` and `'1'` instead of `"0"` and `"1"`.
This is because single quotation marks (`'`) in C denote chars, which double quotes (`"`) denote strings.
Since strings in C are terminated with a null-terminator `"1"` is actually equivalent to the array `{'1', '\0'}`, and not a single character.

Paste the above code snippet into your source code after the length is printed out.
Recompile to check that your code is working properly.


## Step 8: Bit manipulation in C

Now we need to fill in what we actually do for each of these different options.
To do this, let's think about how we can use bit manipulation for our problem.

First, let's think about `0b1`, which is equal to just 1 in decimal.
If we were to "shift" this bits to the left one we would have `0b10`, which is equal to 2 in decimal.
If we repeat this we have `0b100`, which is 4 in decimal.
Therefore, every time we perform a left shift we double.
Note that I am leaving out the leaving 0s (similar to how 3 and 03 are the same number).

This also holds for numbers that are not powers of two.
For instance, `0b11` is equal to 3 in decimal, and a left shift gives us `0b110`, which is 6.

We have an operation like this in C, called the left-shift operator.
It is represented as `a<<b` where `a` is the number we are shifting and `b` is the number that we are shifting it by.
So, `5<<1` shifts 5 by one bit to the left, giving us 10, and `5<<2` gives us 20.

So how does this help us?
Well, we can start with a small number and slowly shift and add to it as we read through it.
For each character we read in we shift our existing value to the left by 1 space (effectively increasing the power of two it is multiplied by), and then add a 1 if we see the current character is a 1, or nothing if it is a 0.


### A concrete example

Say we start with the input string "110" and we want to generate the number.
If we walk through this string one character at a time we will get '1', '1', and '0'.

We will start with our initial value being 0, or `0b0` in binary.

When we read in the first character we shift our current output value to the left one giving us `0b00`.
When we see the first character is a '1' we add 1 to our value, giving us `0b001`.

When we read in the second character we shift to the left once giving us `0b0010`.
When we see it is also a '1' we add one to our value giving us `0b0011`.

Finally, we read in the third character so we shift to the left once more, giving us `0b00110`.
The third character is a '0' so we don't add anything, giving us `0b00110`.

When we drop the leading zeros we get `0b110`, which is our input string, and equivalent to 6.

So by just shifting bits we can easily multiple by powers of 2, giving us a fairly clean way to convert binary to decimal!

### What does this code look like?

We want to change our for loop to do two things -- we want to do a shift every time we read in a character and if it's a '1' we want to add one.
This makes our loop look like:

```C
for (int i = 0; i < length ; i++ ) {
  output_val = output_val << 1;
  if (input_s[i] == '0') {
     // do nothing
  } else if (input_s[i] == '1') {
     output_val += 1;
  } else {
     // todo 3
  }
}
```

## Step 9: Error handling

But wait, what about that `todo 3` that we have?
When would we run into that?
It would only get there if the input is neither '0' or '1', right?
If we get something besides one of those in a binary that's a bit of a problem, isn't it.

When this happens we want to throw an error to let the user know that something's gone wrong.
This has two steps.
First, we print a message to `stderr`, which is "standard error", a special output that is for reporting errors and lots.
Next, we exit with a non-zero code to indicate that something went wrong.

Therefore, `todo 3` will become:

```C
fprintf(stderr, "Unknown input character: '%c'.\n", input_s[i]);
return 4;
```

Notice that we're using a new function, `fprintf` stands for `file printf`, and allows us to specify a "file handle" to print to.
A file handle is a variable that contains a reference to a file, which we talk about in greater detail later in class.
In this case we write to `stderr`, but we normally write to `stdout`.

Additionally, we are using a new format specifier `%c`, which is for outputting characters.
Therefore, we pass it the specific character that caused the problem.

This makes our full for loop into:

```C
for (int i = 0; i < length ; i++ ) {
  output_val = output_val << 1;
  if (input_s[i] == '0') {
     // do nothing
  } else if (input_s[i] == '1') {
     output_val += 1;
  } else {
     fprintf(stderr, "Unknown input character: '%c'.\n", input_s[i]);
     return 4;
  }
}
```

Compile and test your code catching and reporting an incorrect input

***TODO:*** Screenshot your program reporting an error and put it into the Lab1 document

I also encourage you to ask ChatGPT how to check the return code of a program.
We'll be discussing it in class but it can help debug issues in code.


## Step 10: Printing our output

Finally!
We have converted a number and are ready to display it!
To do this we just add one last `printf` statement to our code and run it.
The statement should be:

```C
printf("In decimal that is: %d\n", output_val);
```

Compile it again and rerun and pass in input and it should now convert binary to decimal for you!

```bash
$ ./convert
> 110
input: 110
length: 3
In decimal that is: 6
```

Congratulations!
Your first C program in OS is now complete!

***TODO:*** Screenshot your program running and copy it into the Lab1 document.

## Conclusion

Your program is now complete!
We've seen a lot of things in this lab, including format specifiers, bit shifting, I/O in C, and some preprocessor commands.

***TODO:*** Take a few minutes to write a short bit at the end of your Lab1 document reflecting on what worked how you expected or what was new for you.  If you used ChatGPT at all, did you find it useful or did it just add complexity?


Submit your "Lab 1" document on canvas.

If you want to check it out, the complete code I wrote is in `bin_to_dec.complete.c`.
It isn't heavily commented (homework code should be!) so I'm a bad example, but try to go through and add in comments explaining it in your own words.
