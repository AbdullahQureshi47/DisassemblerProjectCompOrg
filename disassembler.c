/*
 * Test Driver to test verifyMIPSInstruction and binToDec.
 *
 * This program reads lines from a file.  For each line, the program
 *      calls verifyMIPSInstruction.  If the line contains characters
 *      representing a valid MIPS instruction, the program calls
 *      binToDec for various segments of the instruction to test the
 *      binToDec function.
 *
 * Usage:
 *          name [ filename ] [ 0|1 ]
 *      where "name" is the name of the executable, "filename" is an
 *      optional file containing the input to read, and " 0" or
 *      "1" specifies that debugging should be turned off or on,
 *      respectively, regardless of any calls to debug_on, debug_off,
 *      or debug_restore in the program.  Both arguments are optional;
 *      if both are present they may appear in either order.  If no
 *      filename is provided, the program reads its input from stdin.
 *      If no debugging choice is provided, the program prints debugging
 *      messages, or not, depending on indications in the code.
 *
 * Input:
 *      The program reads its input from a file passed in as a parameter
 *      on the command line, or reads from the standard input.
 *      To test verifyMIPSInstruction, the file should contain ...
 *
 *      1) A line that has characters less than 32 but all the characters are Invalid
 *        so that we can check if the code block that checks for invalid length works.
 *      2) Few lines that contain invalid characters. Invalid characters are anything
 *        but '0's and '1's.
 *      3) A line that has 32 characters and all the characters are valid. (This line passes the test)
 *      4) A line that has invalid characters but has length 32 so that we can check the
 *        that the code block that detects for invalid character works.
 *
 * Output:
 *      For each valid line, the program prints a series of decimal
 *      numbers to test binToDec, representing
 *
 *  Test Cases:
 * Our test cases check for all the diffferent functions for R,J, and I format.
 * Furthermore, we also have cases a binary instruction to test verifyMIPSInstruction.
 * Few test cases also check for in-valid MIPS instuctions. For example a binary instructions
 * that does not have the op-code that match either of the format. For example a binary instruction
 * which has all 1's in its bits would be an in-valid Mips instruction.
 *
 *      For each invalid line, the program prints an error message to
 *      stderr saying so.  (The program also prints an error message if
 *      it cannot open the file.)
 *
 * Author:  Abdullah Qureshi and Lincoln Wang
 *        with assistance from: Maria Katrantzi
 *
 * Creation Date: 04/14/19
 *        modified:04/14/19  In this class we iterate through each line and
 * check if its valid and if it is we perform some binary to decimal conversions.
 *
 */

/* include files go here */
#include "disassembler.h"

const int SAME = 0;		/* useful for making strcmp readable */
                                /* e.g., if (strcmp (str1, str2) == SAME) */
int getOpCode(char string[]);
void  getFunctforR(char string[]);
void getFunctionJ(char string[]);
int getAdd(char string[]);
int getImmediate(char String[]);
void getFunctionI(char String[]);
int main (int argc, char *argv[])

{
    FILE * fptr;               /* file pointer */
    char   buffer[BUFSIZ];     /* place to store line that is read in */
    int    length;             /* length of line read in */
    int    lineNum = 0;
    //char *cptr;       /* keep track of input line numbers */


    /* Process command-line arguments (if any) -- input file name
     *    and/or debugging indicator (1 = on; 0 = off).
     */
    fptr = process_arguments(argc, argv);
    if ( fptr == NULL )
    {
        return 1;   /* Fatal error when processing arguments */
    }

    /* Can turn debugging on or off here (debug_on() or debug_off())
     * if not specified on the command line.
     */

    /* Continuously read next line of input until EOF is encountered.
     * Each line should contain an ASCII version of a valid MIPS machine
     * language instruction, represented as 32 character '0's and '1's
     * followed by a newline, rather an actual 32-bit binary MIPS
     * machine language instruction.
     */
    while (fgets (buffer, BUFSIZ, fptr))   /* fgets returns NULL if EOF */
    {
        lineNum++;

        /* If the last character in the string is a newline, "remove" it
         * by replacing it with a null byte. (On Windows, the newline might
         * be preceded by a separate carriage return.)
         */
        length = strlen(buffer);
        if (buffer[length - 1] == '\n')
            buffer[--length] = '\0';      /* remove; pre-decrement length */
        if (buffer[length - 1] == '\r')
            buffer[--length] = '\0';      /* remove; pre-decrement length */
        printf ("\nLine %d: %s\n", lineNum, buffer);
        printDebug ("Length: %d\n", length);

        /*
         * Verify that the string contains 32 '0' and '1' characters.  If
         * it does, do various tests to ensure that binToDec works correctly.
         * If the string is invalid, verifyMIPSinstruction should print
         * an informative error message.
         */

         /* If verifyMIPSInstruction says the string is valid, ... */
            /* Test binToDec with a variety of calls.
             * An example of a test call to binToDec:
             *   printf("\tbits 3..7: %.5s = %d (decimal)\n",
             *          &buffer[3], binToDec(buffer, 3, 7));
             * (The %.5s prints a 5-character substring starting at the
             * charcter indicated by the 2nd parameter.  The %d prints the
             * 3rd parameter as a decimal integer.
             */
             if(verifyMIPSInstruction(lineNum,buffer)==1)
             {
               if(getOpCode(buffer)==0)
               {
                printf("This is R-format");

                if(binToDec(buffer,26,31)==0 || binToDec(buffer,26,31)==2)
                  {// The printf adds a line to put the fucntion before the Mips instruction
                    printf("\n");
                    getFunctforR(buffer);
                    //Adds space to after the function.
                    printf(" ");
                    printf("%s,%s,%d",
                     getRegName(binToDec(buffer,16,20)),getRegName(binToDec(buffer,6,10)),binToDec(buffer,21,26));
                  }

                else if (binToDec(buffer,26,31)==8)
                { // The printf adds a line to put the fucntion before the Mips instruction
                  printf("\n");
                  getFunctforR(buffer);
                  printf(" ");
                  printf("%s", getRegName(binToDec(buffer,6,10)));
                }

                else
                {// The printf adds a line to put the fucntion before the Mips instruction
                  printf("\n");
                 getFunctforR(buffer);
                 printf(" ");
                 printf("%s,%s,%s",
                  getRegName(binToDec(buffer,16,20)),getRegName(binToDec(buffer,6,10)),getRegName(binToDec(buffer,11,16)));
               }
             }

              else if(getOpCode(buffer)==1)
               { printf("This is J-format");
               // The printf adds a line to put the fucntion before the Mips instruction
                printf("\n");
                 getFunctionJ(buffer);
                 printf(" ");
                 printf("%d", getAdd(buffer));
               }

            else if(getOpCode(buffer)==2)
               {
                 printf("This is I-format");
                 //commands for lw and sw since they have a different print format from other fucntions
                 if(binToDec(buffer,0,5)==43 || binToDec(buffer,0,5)==35)
                 {
                   printf("\n");
                   getFunctionI(buffer);
                   printf(" ");
                   printf("%s,%d(%s)",getRegName(binToDec(buffer,11,15)),getImmediate(buffer),getRegName(binToDec(buffer,6,10)));
                 }
                 //lui has a different print format as well so we have another if statement for it
              else   if(binToDec(buffer,0,5)==15)
                  {  printf("\n");
                    getFunctionI(buffer);
                    printf(" ");
                    printf("%s,%d",getRegName(binToDec(buffer,11,15)),getImmediate(buffer));
                  }

                  //commands for bne and beq
              else if(binToDec(buffer,0,5)==4 || binToDec(buffer,0,5)==5)
                  { printf("\n");
                    getFunctionI(buffer);
                    printf(" ");
                    printf("%s,%s,%d",getRegName(binToDec(buffer,11,15)),getRegName(binToDec(buffer,6,10)),getImmediate(buffer));
                  }

                  //instructions for all other functions
                else if(binToDec(buffer,0,5)==8 ||binToDec(buffer,0,5)==9||binToDec(buffer,0,5)==12||binToDec(buffer,0,5)==13)
                  {  printf("\n");
                    getFunctionI(buffer);
                    printf(" ");
                    printf("%s,%s,%d",getRegName(binToDec(buffer,11,15)),getRegName(binToDec(buffer,6,10)),binToDec(buffer,16,31));

                  }

               }
               //If its not I,J, or R format
               else if(getOpCode(buffer)==3)
               {
                 printf("It is not one of R,J,I-format. Its an invalid MIPS instruction" );
               }
             }

             // verifyMIPSInstruction is unstatisfied
             else
             {
               printf("This instruction has fewer bits than 32 and is hence an invalid MIPS instruction ");
             }

    }

    /* End-of-file encountered; close the file. */
    fclose (fptr);
    return 0;
}
//Gets the opcode using for a binary instruction
int getOpCode(char string[])
{
    if(binToDec(string,0,5)==0)
    { //This is R-format
      return 0;
    }

    else if((binToDec(string,0,5)==2 || binToDec(string,0,5)==3))
    { //This is J format
      return 1;
    }
//This is I format
    else if((binToDec(string,0,5)==4 || binToDec(string,0,5)==5)|| binToDec(string,0,5)==8|| binToDec(string,0,5)==9|| binToDec(string,0,5)==12
            || binToDec(string,0,5)==13|| binToDec(string,0,5)==15|| binToDec(string,0,5)==35|| binToDec(string,0,5)==43)
    {
      return 2;
    }
    else
    //This means that the opcode is not of any of the three formats I/J/K
    return 3;
  }

//Get function for the R format
//Gets the decimal values for the last 6 bits and determines the function accordingly
void  getFunctforR(char string[])
  {
    if(binToDec(string,26,31)==32)
      printf("add");
    else if(binToDec(string,26,31)==33)
      printf("addu");
    else if(binToDec(string,26,31)==34)
          printf("sub");
    else if(binToDec(string,26,31)==35)
        printf("subu");
    else if(binToDec(string,26,31)==36)
        printf("and");
    else if(binToDec(string,26,31)==37)
        printf("or");
    else if(binToDec(string,26,31)==39)
        printf("nor");
    else if(binToDec(string,26,31)==42)
        printf("slt");
    else if(binToDec(string,26,31)==43)
        printf("sltu");
    else if(binToDec(string,26,31)==0)
        printf("sll");
    else if(binToDec(string,26,31)==2)
        printf("srl");
    else if(binToDec(string,26,31)==8)
        printf("jr");
    else
    printf("This is not the correct function value");

  }

//Gets address for J format
int getAdd(char string[])
{
  int address;
  address=binToDec(string,6,31) *4;
  return address;
}

//Gets functon for J depending on the first 6 bits
void getFunctionJ(char string[])
{  //jumo instruction
  if(binToDec(string,0,5)==2)
  {
    printf("j");
  }
   //Jump and link instruction
  if(binToDec(string,0,5)==3)
  {
    printf("jal");
  }
}

//Getting function for I-format depending on the op-code
void getFunctionI(char string[])
{
  if(binToDec(string,0,5)==4)
  {
    printf("beq");
  }

else if(binToDec(string,0,5)==5)
  {
    printf("bne");
  }

else  if(binToDec(string,0,5)==8)
  {
    printf("addi");
  }

else  if(binToDec(string,0,5)==9)
  {
    printf("addiu");
  }

else  if(binToDec(string,0,5)==12)
  {
    printf("andi");
  }

else  if(binToDec(string,0,5)==13)
  {
    printf("ori");
  }

else  if(binToDec(string,0,5)==15)
  {
    printf("lui");
  }

else  if(binToDec(string,0,5)==35)
  {
    printf("lw");
  }

else  if(binToDec(string,0,5)==43)
  {
    printf("sw");
  }

  else
  printf("A function to solve this binary number does not exist");
}

//Gets immediate for I format. Immediate is the decimal value of the binary numbers
//from bit 16 to bit 31
int getImmediate(char string[])
{
  int immediate;
  immediate= binToDec(string,16,31);
  return immediate;
}
