#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "printFuncs.h"

/** Define the global ERROR_LIMIT variable. **/
int ERROR_LIMIT = 20;

/**
 * printError(const char * restrict_format, ...)
 *
 * This function prints an error message to standard error (stderr),
 * until a certain number of error messages have been printed.  This
 * limit is defined in a global variable, ERROR_LIMIT. By default,
 * the limit is 20, but it can be set to a different value; the
 * most logical place to set the limit is in the main function.
 * Once that number of error messages have been printed, printError
 * will cause the program to exit.  If the error limit is less than or
 * equal to 0, the program will disregard it, allowing the program to
 * continue (and continue to generate error messages) until it stops on
 * its own.
 *
 * Parameters:
 *  The parameters to printError are modeled on those to printf,
 *  consisting of a format and various other arguments as specified
 *  in the format.
 *
 * Exit Value:
 *  If ERROR_LIMIT is greater than zero and the program has reached the
 *  limit, printError will exit the program with an error code of 1.
 */
void printError(const char * restrict_format, ...)
{
    static int error_count = 0;

    /* The following code allows us to call fprintf with the variable
     * parameters that were passed to printError.
     */
    va_list ap;
    va_start(ap, restrict_format);
    (void) vfprintf(stderr, restrict_format, ap);
    va_end(ap);

    /* Keep track of the error count, and exit if it goes too high. */
    error_count++;
    if ( ERROR_LIMIT > 0 && error_count > ERROR_LIMIT )
    {
        exit(1);
    }

}
