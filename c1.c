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

/* 
This program repeatedly prompts the user for input, 
reads this input in and writes it to stdout. You may send your
prompts to stderr.
*/


int main(int ac,char**av)
{
    int num = 1; // just to keep the while loop going
	  int quartersec = 250000; // to set sleep() to quarter second
    int readChar;
 	  char line[100];
 	

    do 
    {   // Repeatedly prompts user for input 
        fprintf(stderr, "\nPlease enter the next line of input, enter 'q' or 'Q' to exit\n");
        readChar = read(0, line, sizeof(line)); // Reads a line  of size 100 from stdin 
    	
    	if ( readChar == -1 ) 
    	{
    		// Prints to std error if reading error occurs 
        	fprintf(stderr, "\nReading error\n");
    	}

    	else 
    	{
        
	        line[readChar] = '\0';
	        fprintf(stdout, "%s", line); // writes line to stdout 
	        fflush(stdout); // flushes stdout 
	
	      	usleep(quartersec); // c1 sleeps for quarter of a second
   	 	}
   } 
   while(*line != 'q' && *line != 'Q'); // random num just to keep the while loop going
   printf("\nThank you!\n");





/* USED TO TEST THAT COMMUNICATION BETWEEN PROCESSES IS CONNECTED CORRECTLY
   COMMENT ABOVE AND UN-COMMENT BELOW TO SEE REDIRECTION CORRECT AND WORKING
   ONLY LOOPS ONCE AS PURPOSE IS JUST FOR TESTING  */
    
    /*

		fprintf(stderr, "\nPlease enter the next line of input:\n");
		fgets(line, 100, stdin);
        fprintf(stdout, "%s\n", line);
       
     */ 


} // end of main  
