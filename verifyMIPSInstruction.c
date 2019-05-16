/*
 * verifyMIPSInstruction
 *
 * This function verifies that the string provided to it as a paramater
 * contains 32 characters representing binary digits (characters '0' and
 * '1'), followed by a null byte.  If the string contains the wrong
 * number of characters or contains invalid charaters (not '0' or '1'),
 * then the function prints an error message to stderr giving the line
 * number and an appropriate error message.
 *
 *   int verifyMIPSInstruction (int lineNum, char * instruction);
 *
 *	    Pre-condition:  instruction is a null-terminated string
 *	    Post-condition: the characters in "instruction" have not
 *			    been modified
 *	    Returns: 1 if instr contained 32 characters representing binary
 *			    digits ('0' and '1') followed by a null byte
 *		     0 if instr has the wrong number of characters or
 *		            contains invalid characters
 *	    Output: Prints an error message to stderr if necessary
 *
 * Implementation:
 *	Describe interesting implementation details here, if any.
 *      (HOW does this function work?  What non-trivial data structures
 *	or algorithms does it use?  Does it have performance
 *	characteristics that the user should be aware of?)
 *
 * Author: Abdullah Qureshi and Lincoln Wang
 *	with assistance from: MARIA Katrantzi
 *
 * Creation Date:  Creation_Date
 *	modified: Modification_Date	reason
 *	modified: Modification_Date	reason
 *
 */

#include "disassembler.h"
#include <stdio.h>
#include <string.h>

static const int INSTR_LENGTH = 32;

int verifyMIPSInstruction (int lineNum, char * instr)
  /*  returns 1 if instr contains INSTR_LENGTH characters representing binary
   *  digits ('0' and '1'); 0 otherwise
   */
{
    int   length;
    int counter=0;
    //Gets the length of the String
    length = strlen(instr);

    //Prints the error message if the length is not equal to 32
    if (length != INSTR_LENGTH)
    {
        printError ("Error: line %d does not have %d chars.\n",
                    lineNum, INSTR_LENGTH);
        return 0;
    }
//Null byte represents the end of the String. untill it the program reaches the NULL
//byte the function is going to keep on looping.
    while(*instr != '\0')
    {
      // If the bit is '1' or '0' the loop keeps on going
      if( *instr=='0' || *instr=='1')
      //counter basically counts the number of elements in the string
       counter++;

    instr++;
    }
  // iF counter is not equal to the INSTR_LENGTH then there are invalid
  //characters in the string and the function prints an error and returns 0
    if(counter == INSTR_LENGTH)
        return 1;
    else
      printError ("Error: line %d does not contain all 0's or 1's. \n", lineNum);

    return 0;
}
