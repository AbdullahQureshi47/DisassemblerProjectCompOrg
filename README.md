# disassembler-assignments: Disassembler Assignments
##  Disassembler Utility Functions, and <br> Working Disassember

### Disassembler Utility Functions
This repository contains the starter code (including a `Makefile` and a
template test file) for a program in which students will write and
test two functions (`verifyMIPSInstruction` and `binToDec`).  These
functions will be useful in the Disassembler program to be written later.
(See [here](http://www.cs.kzoo.edu/cs230/Projects/DisUtilitiesProj.html)
for the project description for this program.)

The provided code processes 2 optional command-line arguments, a file name
and a debugging indicator, reads in lines from the file (or standard input,
if no file name is provided), and prints the lines back out to standard
output.  If debugging is turned on, it also prints the length of the line.
To compile the initial provided code, type `make testArgs`.
Look at the code in `disUtil.c` to see what it does, then try the following
tests:
    ./testArgs testfileStarter.txt 0
    ./testArgs testfileStarter.txt 1
    ./testArgs 0 testfileStarter.txt
    ./testArgs 1 testfileStarter.txt
    ./testArgs testfileStarter.txt
If you test it without providing a file name, it will wait for you to type
in the input; you can do this line-by-line, typing Control-D (end-of-file)
when you're done.  For example:
    ./testArgs 1
    Hi there!
    Just testing ...
    Control-D

Once you are comfortable with `disUtil.c` you should write and test the
two functions for this assignment: `verifyMIPSInstruction` and `binToDec`.

### Working Disassembler
The repository also contains some additional starter code for the
full disassembler program.
(See [here](http://www.cs.kzoo.edu/cs230/Projects/DisassemblerProj.html)
for the project description for the full disassembler program.)
