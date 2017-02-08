# Interprocess-Communication-with-Pipes
Implementation of the communication between multiple child processes via a parent process using pipes



###LOGIC


The logic behind the program is that through the controller (parent) we:

(1) Create a pipe, then fork 3 child processes (c1, c2 & c3) one at a time, 
from child 1 (c1) we redirect it’s pipe to stdin, then also read its stdin and write it to stdout.

(2) Fork child 2 (c2) to start the second process and redirect that pipe to stdin in as well as the second pipe to stdout. 

(3) Fork the third child (c3) and redirect that pipe to stdin. 

Doing this connects all processes/children so that when we execute c1, c2 & c3 via the controller (parent) 
process all three stdin’s and stdout’s are redirected and communication between child processes is successful. 


c1: prompts for input, reads stdin and writes to stdout.

c2: reads stdin, converts to uppercase and writes to stdout.

c3: reads stdin, adds line number and writes to stdout.

controller: parent forks processes/children and communicates between them.



##PSEUDO CODE:


create pipe1
create pipe2

fork()
{

redirect pipe1 output
close pipe 1 
exec c1

c1
{
get stdin as char[]
}

}

fork()
{
redirect pipe2 input
close pipe 1

redirect pipe2 output
close pipe2

exec c2
{

get stdin as char[]
convert to uppercase
print stdout
}
}

fork()

redirect pipe2 input
close pipe 2


exec c3
{

get stdin as char[]
add number
print stdout
}

}



##TEST PLAN:

[mwahab@han ~]$ cc -o c1 c1.c
[mwahab@han ~]$ ./c1

Please enter the next line of input, enter 'q' or 'Q' to exit
The Quick brown fox     
The Quick brown fox 

Please enter the next line of input, enter 'q' or 'Q' to exit
jumps over the lazy dog.
jumps over the lazy dog.

Please enter the next line of input, enter 'q' or 'Q' to exit
Q
Thank you!

[mwahab@han ~]$ cc -o c2 c2.c
[mwahab@han ~]$ ./c2
The Quick brown fox
THE QUICK BROWN FOX
jumps over the lazy dog
JUMPS OVER THE LAZY DOG
Q
THANK YOU!

[mwahab@han ~]$ cc -o c3 c3.c
[mwahab@han ~]$ ./c3
The Quick brown fox
 1 The Quick brown fox
jumps over the lazy dog.
 2 jumps over the lazy dog.
Q
Thank you!

[mwahab@han ~]$ cc -o controller controller.c
[mwahab@han ~]$ ./controller

Please enter the next line of input, enter 'q' or 'Q' to exit
The Quick brown fox
 1 THE QUICK BROWN FOX

Please enter the next line of input, enter 'q' or 'Q' to exit
jumps over the lazy dog.
 2 JUMPS OVER THE LAZY DOG.

Please enter the next line of input, enter 'q' or 'Q' to exit
Q
 3 THANK YOU!


###LIMITATIONS: 


All though the output is correct and the redirections and pipes are all connected correctly the program has the following limitations:

- Does not 100% wait for all child processes to end and show each of their exit statuses. 
- Parent waits for all child processes at the end, the parent should wait for each child at a time after exec then print out all child processes status at the end.


NOTE: c1.c, c2.c & c3.c have commented out code that only loops once to test that the communication pipes and redirection is all correct, the output for that is also correct if you wanted to test that.
