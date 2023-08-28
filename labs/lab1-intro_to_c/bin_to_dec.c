#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXSTR 8

int main() {

   // user input string
   char s[MAXSTR]; 

   // prompt for input if input from terminal
   if (isatty(fileno(stdin))) {
       printf("> ");
   }
   
   return 0;
}
