#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>

#define BUFSIZE 256

/*
This program reads its stdin and writes this to stdout
with a line number prepended (i.e. added to the beginning)
*/


int main(int ac,char**av)
{
   int num = 1;
   int i = 1;
   int readChar;
   char line[100];

    do 
    {   
 
        readChar = read(0, line, sizeof(line)); // Reads a line  of size 100 from stdin 
	    
	    if ( readChar == -1 )
	    {
	         fprintf(stderr, "reading error");
	    }
	    else 
	    {
	         line[readChar] = '\0';
	         fprintf(stdout, " %d %s", i, line); // writes line to stdout, adding a line number to front 
	         i++; // increments the line number 
	         fflush(stdout); // flushes stdout
	    }
   } 
   while( num == 1); // just to keep the while loop going





/* USED TO TEST THAT COMMUNICATION BETWEEN PROCESSES IS CONNECTED CORRECTLY
   COMMENT ABOVE AND UN-COMMENT BELOW TO SEE REDIRECTION CORRECT AND WORKING
   ONLY LOOPS ONCE AS PURPOSE IS JUST FOR TESTING  */
		
	/*
	fgets(line, 100, stdin);
     	fprintf(stdout, " %d %s\n", i, line);
        i++;
        */

}
