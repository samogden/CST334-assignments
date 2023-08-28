#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXSTR 8

int main() {

   // user input string
   char input_s[MAXSTR];
   int output_val = 0;

   // prompt for input if input from terminal
   if (isatty(fileno(stdin))) {
       printf("> ");
   }
   
   scanf("%s", input_s);
   printf("input: %s\n", input_s);
   
   int length = strlen(input_s);
   printf("length: %d\n", length);
   
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
   
   printf("In decimal that is: %d\n", output_val);
   
   return 0;
}
