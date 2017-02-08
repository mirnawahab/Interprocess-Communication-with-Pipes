#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>
#include <string.h>

#define BUFSIZE 256

 
// This program reads its stdin, converts the lower case of
// the input to upper case, and writes this to stdout.

void turnToUppercase(char []);

int main(int ac,char**av)
{
   int num = 1;
   int readChar;
   char line[100];

   //    fprintf(stderr, "\n**** child 2 Type 'quit' to stop inputting text ****\n" );


    do 
    {   
      readChar = read(0, line, sizeof(line)); // Reads a line  of size 100 from stdin 
      
      if ( readChar == -1 )
      {
        // Prints to std error if reading error occurs 
        fprintf(stderr, "reading error");
      }
      else 
      {
        line[readChar] = '\0';
        turnToUppercase(line); // converts line read to uppercase before writing to stdout
        fprintf(stdout, "%s", line); // writes line to stdout 
        fflush(stdout); // flushes stdout 
      }
   } 
   while( num == 1); // just to keep the while loop going




/* USED TO TEST THAT COMMUNICATION BETWEEN PROCESSES IS CONNECTED CORRECTLY
   COMMENT ABOVE AND UN-COMMENT BELOW TO SEE REDIRECTION CORRECT AND WORKING
   ONLY LOOPS ONCE AS PURPOSE IS JUST FOR TESTING  */
    
    /*

      fgets(line, 100, stdin);
      turnToUppercase(line);
      fprintf(stdout, "%s\n", line);
       
     */ 


} // end of main


void turnToUppercase(char string[]) 
{
   int i = 0;
 
   while (string[i] != '\0') 
   {
      if (string[i] >= 'a' && string[i] <= 'z') 
      {
         string[i] = string[i] - 32;
      }
      i++;
   }
}