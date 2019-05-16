/*
 * binToDec
 *
 * This function converts the binary digits from string[begin] to
 * string[end] to a decimal integer.
 *
 * int binToDec(char string[], int begin, int end)
 *   Pre-condition:  begin and end are valid indices in array string;
 *   		     every character from string[begin] to string[end]
 *		     (including those two) has a character value '0' or '1'
 *   Returns: the decimal equivalent of the binary number represented by
 *	      the characters in string[begin] - string[end].
 *            (If begin > end, this function arbitrarily returns 0.)
 *
 * For example, assume A is a character array that contains the
 *    following characters:
 *            '1'  '0'  '1'  '1'  '0'  '1'  '0'  '0'  '1'
 *    The call binToDec(A, 2, 5) converts the binary number 1101
 *    (represented by the substring A[2] - A[5]) to the decimal integer
 *    13 and returns it.
 *
 * Note: The decimal value returned may appear to be negative if the
 * string being converted is long enough (end - begin + 1 == 32)
 * and if the first character is '1'.
 *
 * Implementation:
 *	The funtion starts from the least significant figure checks if the value
 *of that bit is 1. If it is then the function takes the power of two for that
 *position and adds it to a constant called decimal. Outside the if statement
 *the function increments power variable so the powers of two can be incremented
 *and added as we go from right to left of the binary sequence.
 *
 * Author:  Abdullah Qureshi and Lincoln Wang
 *	with assistance from: Maria Katrantzi
 *
 * Creation Date:  4/13/2019
 *	modified:  4/13/2019	This program now converts a binary number (eg 0101010)
 *to its decimal equivelant.
 *
 */
#include <math.h>
int binToDec(char string[], int begin, int end)
{
	int i;
	//Variables intialized
	int decimal = 0;
	int power=0;
//Reverse for-loop that goes from the least significant bit to the most significant bit
	for(i=end; i>=begin; i--)
	{
		// If the bit doesn't contain 1 we just move to next bit.
		if(string[i]=='1')
		{
			decimal+= 1<<(power);
		}
		power++;
	}

	return decimal;
}
