/*
 * This function looks up and returns the mnemonic name for a given
 * register number.
 *
 * How to call this function:
 *
 *      char * getRegName(int regNbr)
 *          Parameter: regNbr is a valid register number
 *          Pre-condition: 0 <= regNbr < 32
 *          Returns: returns a pointer to the mnemonic name associated with
 *              register number; for example: "$t0" or "$a1"
 *
 *    You do not need to allocate space for the mnemonic name that this
 *    function returns; it will return a pointer to a name (a string)
 *    that is statically scoped (i.e., does not disappear as soon as the
 *    function returns).
 *
 *    For example:
 *	  int rNbr1, rNbr2, rNbr3;	   // register numbers between 0 and 31
 *	  char *rName1, *rName2, *rName3;  // will point to names, e.g., "$t0"
 *	  ...				   // set register numbers
 *	  rName1 = getRegName (rNbr1);
 *	  rName2 = getRegName (rNbr2);
 *	  rName3 = getRegName (rNbr3);
 *	  printf ("add %s, %s, %s\n", rName1, rName2, rName3);
 *    If rNbr1 = 8, rNbr2 = 9, rNbr3 = 16, this will print:
 *		add $t0, $t1, $s0
 *
 * Author: Alyce Brady and Garrett Olson
 * Modifiers: Abdullah and Lincoln
 * Modification: We added some register names and a return statement that returns the
 * register name assosiated with the register number.
 * Date:   2/10/99
 *
 */

char * getRegName (int regNbr)
  /* returns mnemonic name for given register */
{
	/* Create a static (persistent) array of the mnemonic names,
	 *    each of which is a string (char *).
	 */
	static char * regArray[] =
        {
		"$zero",
		"$at",
		"$v0","$v1",
		"$a0","$a1","$a2","$a3",
		"$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7",
		"$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7",
		"$t8","$t9",
		"$k0","$k1",
		"$gp","$sp","$fp","$ra"

	};
	//return the register name assosiated with the register number.

return regArray[regNbr];
}
