/*
 * This file includes common system header files, a local header
 * file with declarations for printDebug and printError, and signatures
 * for other commonly used functions.
 */

#ifndef _DISASSEMBLER_H
#define _DISASSEMBLER_H

#include <stdio.h>
#include <stdlib.h>     /* May need to be _stdlib.h on some machines. */
#include <string.h>	/* May need to be memory.h on some machines. */
#include <ctype.h>

#include "printFuncs.h"
#include "process_arguments.h"
#include "same.h"

int binToDec (char string[], int begin, int end);
int verifyMIPSInstruction (int lineNum, char string[]);

char * getRegName (int regNbr);

#endif
