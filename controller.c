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


void upper_string(char []);
void child1_code(), child2_code(), child3_code(), parent_code();

int main(int ac, char**av)
{
    
        int     i = 1;
        int     status, readChar;
        int     pipeC1ToC2[2], pipeC2ToC3[2];
        pid_t   pid1, pid2, pid3, parentPID;
        char    line[100];

      
       parentPID = getpid();


     //  Creating two pipes, pipeC1ToC2: Child 1 -> Child 2 &
    //                       pipeC2ToC3: Child 2 -> Child 3  
        if ( pipe( pipeC1ToC2 ) == -1 || pipe(pipeC2ToC3) == -1)
        {
                fprintf(stderr, "Cannot get a pipe");
        }

        //forking Child 1 process (c1.c)
        if((pid1 = fork()) == -1)
        {
                fprintf(stderr, "Cannot fork  pid1\n");
        }

        // If 0 returns then its a child process and the below will run else its the Parent
        if (pid1 == 0)
        {
                // start off by connecting the first communication pipe (pipeC1ToC2)
                if  ( close(pipeC1ToC2[0]) == -1) //Child 1 closes up input/reading side of pipe 
                { 
                    //Prints to std error if pipe could not be closed
                    fprintf(stderr, "\npipeC1ToC2[0] not closed\n"); 
                }

                if ( dup2(pipeC1ToC2[1], 1) == -1 ) // redirects writing end of pipe to stdout 1
                {
                    //Prints to std error if pipe could not be redirected
                    fprintf(stderr, "\nCould not redirect pipeC1ToC2[1] to stdout\n");
                }            

                  if  ( close(pipeC1ToC2[1]) == -1) // close writing end of pipe, since its redirected to stdout 
                { 
                    //Prints to std error if pipe could not be closed
                    fprintf(stderr, "\npipeC1ToC2[1] not closed\n");  
                }

            child1_code(); // executes c1.c (reads stdin & writes to stdout)
            
        } // end of child 1 process (c1.c)
        
        //forking Child 2 process (c2.c)
        if((pid2 = fork()) == -1)
        {
            //Prints to std error if child 2 not forked
            fprintf(stderr, "\nCannot fork pid2\n");
        }

        // If 0 returns then its a child process and the below will run else its the Parent 
        if ( pid2 == 0 )
        {
            if  ( close(pipeC1ToC2[1]) == -1) //writing closed, child 1 writes to pipe    
            { 
                //Prints to std error if pipe could not be closed
                fprintf(stderr, "\npipeC1ToC2[1] not closed\n");  
            }

            if ( dup2(pipeC1ToC2[0], 0) == -1 ) // redirects reading end of pipe to stdin 0
            {
                //Prints to std error if pipe could not be redirected
                fprintf(stderr, "\nCould not redirect pipeC1ToC2[0] to stdin\n");
            }
 
            if  ( close(pipeC1ToC2[0]) == -1) //writing closed, child 1 writes to pipe    
            { 
                //Prints to std error if pipe could not be closed
                fprintf(stderr, "\npipeC1ToC2[0] not closed\n");  
            } 
            /* end of connecting first communication pipe (pipeC1ToC2) */

 
                // Now we start connecting second communication pipe (pipeC2ToC3)
                if  ( close(pipeC2ToC3[0]) == -1) //reading closed, child 1 writes to pipe    
                { 
                    //Prints to std error if pipe could not be closed
                    fprintf(stderr, "\npipeC2ToC3[0] not closed\n");  
                }

                if ( dup2(pipeC2ToC3[1], 1) == -1 ) // redirects writing end of pipe to stdout 1
                {
                    //Prints to std error if pipe could not be redirected
                    fprintf(stderr, "\nCould not redirect pipeC2ToC3[1] to stdout\n");
                }            
                
                if  ( close(pipeC2ToC3[1]) == -1) //close writing end of pipe, since its redirected to stdout  
                { 
                    //Prints to std error if pipe could not be closed
                    fprintf(stderr, "\npipeC2ToC3[1] not closed\n");  
                }
                 
            child2_code(); // executes c2.c (reads stdin, converts to uppercase & writes to stdout)
       
        } // end of child 2 process (c2.c)

        //forking Child 3 process (c3.c)
        if ( (pid3 = fork()) == -1 )
        {
            //Prints to std error if child 2 not forked
            fprintf(stderr, "\nCannot fork pid3\n");
        }

        // If 0 returns then its a child process and the below will run else its the Parent 
        if ( pid3 == 0 )
        {

            // Closing both ends of first pipe before starting Child 3
            if  ( close(pipeC1ToC2[0]) == -1) //writing closed, child 2 reads from pipe    
            { 
                //Prints to std error if pipe could not be closed
                fprintf(stderr,"\npipeC1ToC2[0] not closed\n");
            }   

            if  ( close(pipeC1ToC2[1]) == -1) //writing closed, child 2 reads from pipe    
            { 
                //Prints to std error if pipe could not be closed
                fprintf(stderr,"\npipeC1ToC2[1] not closed\n");
            }   


            if  ( close(pipeC2ToC3[1]) == -1) //writing end closed, child 3 reads from pipe    
            { 
                //Prints to std error if pipe could not be closed
                fprintf(stderr,"\npipeC2ToC3[1] not closed\n");
            }   

            if ( dup2(pipeC2ToC3[0], 0) == -1 ) // redirects reading end of pipe to stdin 0
            {
                //Prints to std error if pipe could not be redirected
                fprintf(stderr,"\nCould not redirect stdin of pipeC2ToC3[0]\n"); 
            }

            if  ( close(pipeC2ToC3[0]) == -1) //reading end closed, child 2 reads from pipe    
            { 
                //Prints to std error if pipe could not be closed
                fprintf(stderr, "\npipeC2ToC3[0] not closed\n");
            } 
            
        child3_code();
                   
        } // end of child 3 process (c3.c)


    else // This is the parent process 
    {

        // Parent wait for all three child processes and prints exit status 
        waitpid(pid1, &status, 0);
        fprintf(stderr, "Child 1 exit status: %d\n", status);

        // waitpid(pid2, &status, 0);
        // fprintf(stderr, "Child 2 exit status: %d\n", status);

        // waitpid(pid3, &status, 0);
        // fprintf(stderr, "Child 3 exit status: %d\n", status);
                
        // Parent only controls children so close both ends of both pipes
        if  (close(pipeC1ToC2[0]) == -1|| close(pipeC2ToC3[0]) )
        {
            //Prints to std error if pipe could not be closed
            fprintf(stderr, "\nParent 0 not closed\n");
        }

        if  (close(pipeC1ToC2[1]) == -1 || close(pipeC2ToC3[1]) == -1)
        {
            //Prints to std error if pipe could not be closed
            fprintf(stderr, "\nParent 1 not closed\n");
        }   
    }

    return 0;
} // end of main






void upper_string(char s[]) 
{
   int c = 0;
 
   while (s[c] != '\0') 
   {
      if (s[c] >= 'a' && s[c] <= 'z') 
      {
         s[c] = s[c] - 32;
      }
      c++;
   }
}

void child1_code()
{ 
     execl("./c1", NULL);

}

void child2_code()
{ 
     execl("./c2", NULL);
}

void child3_code()
{ 
     execl("./c3", NULL);
}
