# Interprocess-Communication-with-Pipes
Implementation of the communication between multiple child processes via a parent process using pipes

  
 
##LOGIC

  
The logic behind the program is that through the controller (parent) we:

**(1)** Create a pipe, then fork 3 child processes (c1, c2 & c3) one at a time, 
from child 1 (c1) we redirect it’s pipe to stdin, then also read its stdin and write it to stdout.

**(2)** Fork child 2 (c2) to start the second process and redirect that pipe to stdin in as well as the second pipe to stdout. 

**(3)** Fork the third child (c3) and redirect that pipe to stdin. 

Doing this connects all processes/children so that when we execute c1, c2 & c3 via the controller (parent) 
process all three stdin’s and stdout’s are redirected and communication between child processes is successful. 


**c1:** prompts for input, reads stdin and writes to stdout. <br />
**c2:** reads stdin, converts to uppercase and writes to stdout. <br />
**c3:** reads stdin, adds line number and writes to stdout.<br />
**controller:** parent forks processes/children and communicates between them.<br />

    

##PSEUDO CODE:


create pipe1 <br />
create pipe2 <br />

fork()
{

redirect pipe1 output <br />
close pipe 1  <br />s
exec c1 <br />

c1
{

get stdin as char[] <br />
}

}

fork()<br />
{

redirect pipe2 input <br />
close pipe 1 <br />

redirect pipe2 output <br />
close pipe2 <br />

exec c2
{

get stdin as char[] <br />
convert to uppercase <br />
print stdout <br />
}

}

fork()


redirect pipe2 input <br /> 
close pipe 2 <br />


exec c3
{

get stdin as char[] <br />
add number <br />
print stdout <br />

}

}


 <br />
##TEST PLAN: <br />
 <br />
[mwahab@han ~]$ cc -o c1 c1.c <br />
[mwahab@han ~]$ ./c1 <br />

Please enter the next line of input, enter 'q' or 'Q' to exit <br />
The Quick brown fox   <br />   
The Quick brown fox  <br />
 <br />
Please enter the next line of input, enter 'q' or 'Q' to exit <br />
jumps over the lazy dog. <br />
jumps over the lazy dog. <br />
 <br />
Please enter the next line of input, enter 'q' or 'Q' to exit <br />
Q <br />
Thank you! <br />

[mwahab@han ~]$ cc -o c2 c2.c <br />
[mwahab@han ~]$ ./c2 <br />
The Quick brown fox <br />
THE QUICK BROWN FOX <br />
jumps over the lazy dog <br />
JUMPS OVER THE LAZY DOG <br />
Q <br />
THANK YOU! <br />

[mwahab@han ~]$ cc -o c3 c3.c <br />
[mwahab@han ~]$ ./c3 <br />
The Quick brown fox <br />
 1 The Quick brown fox <br />
jumps over the lazy dog. <br />
 2 jumps over the lazy dog. <br />
Q <br />
Thank you! <br />

[mwahab@han ~]$ cc -o controller controller.c<br />
[mwahab@han ~]$ ./controller <br />

Please enter the next line of input, enter 'q' or 'Q' to exit <br />
The Quick brown fox <br />
 1 THE QUICK BROWN FOX <br />
 <br />
Please enter the next line of input, enter 'q' or 'Q' to exit <br />
jumps over the lazy dog. <br />
 2 JUMPS OVER THE LAZY DOG. <br />
 <br />
Please enter the next line of input, enter 'q' or 'Q' to exit <br />
Q <br />
 3 THANK YOU! <br />
 <br />

##LIMITATIONS:  <br />


All though the output is correct and the redirections and pipes are all connected correctly the program has the following limitations: <br />

- Does not 100% wait for all child processes to end and show each of their exit statuses.  <br />
- Parent waits for all child processes at the end, the parent should wait for each child at a time after exec then print out all child processes status at the end. <br />


NOTE: c1.c, c2.c & c3.c have commented out code that only loops once to test that the communication pipes and redirection is all correct, the output for that is also correct if you wanted to test that. <br />
