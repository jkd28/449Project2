# My Strings and Debug Analysis
I created this program as an assignment for the University of Pittsburgh's Introduction to System Software course (COE 0449).  This project involved using `gdb` and the `strings` command to analyze executables and find the correct 'password' for each.  In addition, I was required to write my own `mystrings` program, which prints a combination of bytes that matches the definition of "string" that I was provided.

## Mystrings Command
This program reads the bytes of a file to find strings, which are defined as patterns of characters with ASCII values of 32 <= character <= 126 that are more than 4 characters long.  
Compile: `gcc -o mystrings mystrings.c`  
Execute: `./mystrings <file>`

Example:
```
$ gcc -o mystrings mystrings.c
$ ./mystrings Description.txt
jkd28_1
Attempts:
My first attempt was made immediately after recitation on 2/20/17.  I created a breakpoint at main and used the 'disas' keyword to exam
ine the x86 for jkd28_1.  From this, the following instruction line appeared suspicious:
0x0804830c <+61>:    repz cmpsb %es:(%edi),%ds:(%esi)
Upon further investigation, I learned that it was a comparison of strings.  Using the debug and examine tools, I was able to determine
that the register $esi contained the string to which input was compared.  This yielded the correct result.
Solution:
ycSzZqniOdtPSkhYkVbrAwosHgIfg
jkd28_2
Attempts:
I first set a breakpoint at main and disassembled the code.  This allowed me to see a line that once again looked suspicious:
0x080485c0 <+121>:   repnz scas %es:(%edi),%al
I set a breakpoint at this line and continued, entering
test
as my input.  I noticed that this instruction repeated a number of times equal to the length of my string.  This was interesting to me
, but it didn
t really give me what I wanted.  So I looked elsewhere.  I noticed a strcmp:
0x080485db <+148>:   call   0x80483d8 <strcmp@plt>
...
```

## Included Files
  * `Description.docx`  
This MS Word Document details the processes I used to determine the correct password for each of the three executables I was assigned: jkd28_1, jkd28_2, jkd28_3.
  * `Description.txt`  
A plaintext transcription of `Description.docx`
