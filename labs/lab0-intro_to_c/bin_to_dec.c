#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXSTR 8

int main() {
    printf("Hello!\n");
   // user input string
   char input_s[MAXSTR]; 
   int output_val = 0;

   // prompt for input if input from terminal
   if (isatty(fileno(stdin))) {
       printf("> ");
   }
   
   return 0;
}
