PROJECT TITLE: The Disassembler Project
PURPOSE OF PROJECT: This program reads in Machine Language and writes out the corresponding assembly language code.

VERSION or DATE: 5/20/2019

HOW TO START THIS PROJECT: To starts this project the user first needs to open up the Ubuntu or any other linux/unix terminal and access the folder containing the project.
Then the user needs to compile the program using the make command. The user needs to type 'make disassembler' to compile project.
Now that the project is compiled the user needs to needs to run the program to see the results. The user needs to use the following instruction:
"./disassembler testfileStarter.txt".
This would run the program for the user.   

AUTHORS: Abdullah Qureshi and Lincoln Wang
USER INSTRUCTIONS:
The user should expect a MIPS instruction as an output. Following is a sample input and its corresponding output of the program:
Input:
100011	01001	01000	0000 0100 1011 0000
000000	10010	01000	01000	00000	100000
101011	01001	01000	0000 0100 1011 0000
Output:
lw   $t0, 1200($t1)
add  $t0, $s2, $t0
sw   $t0, 1200($t1)

Furthermore, the user can add valid binary instructions to the test file and the program will output valid MIPS instructions associated with the code. 
