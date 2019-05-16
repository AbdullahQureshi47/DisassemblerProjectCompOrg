/*
 * The process_arguments function parses the command-line arguments for
 * an optional filename and an optional choice (1 or 0) to turn all
 * debugging messages on or off.  It returns a FILE pointer to an open
 * file (stdin if no filename was passed in) or NULL if process_arguments
 * encounters a fatal error.
 *
 * Usage:
 *      programName  [filename] [0|1]
 * If both a filename and a debugging choice are provided, they may
 * be in either order.
 *
 * The optional filename indicates the input file; if it is provided,
 * process_arguments opens the file and returns it after also processing
 * the debugging option.  If it is not provided, the program reads its
 * input from stdin.
 *
 * A debugging choice argument of 0 or 1 indicates a choice to globally
 * turn debugging off or on, overriding any calls to debug_on,
 * debug_off, and debug_restore in the code.  0 means that no debugging
 * messages should be printed, 1 means that all debugging messages
 * should be printed.  If no debugging choice is specified, the
 * debug_print function will either print or not print messages
 * depending on the current debugging state set by the debug_on,
 * debug_off, and debug_restore functions.
 */

#include "process_arguments.h"

/* SAME is defined in disUtil.c and should be defined in other main files also. */

FILE * process_arguments(int argc, char * argv[])
{
    FILE * fptr;               /* file pointer */

    /* Implementation notes:
     * The arguments are both optional and may be provided in either
     * order, which makes the logic more complicated.  This function
     * processes the debugging choice first, if one was specified, then
     * "erases" it from the argument list so that when we come to process
     * the filename we can assume that it is the first and only argument
     * (if provided at all).  If two arguments are provided but neither
     * is a debugging choice, or if more than two arguments are provided,
     * then a usage error message is printed.
     * The valid combinations are:
     *   program               no arguments are provided
     *   program 0|1           process debugging choice and decrement
     *                         argc so it looks like there were no arguments
     *   program filename      no debugging choice; process filename
     *   program 0|1 filename  process debugging choice and shift
     *                         filename into first argument; now it looks
     *                         like there was just one argument, filename
     *   program filename 0|1  process debugging choice and decrement
     *                         argc; now it looks like there was just
     *                         one argument, filename
     */

    /* Process debugging choice and then "erase" this argument by
     * shifting the filename into its place or just by reducing the
     * argument count, argc, whichever is appropriate (see above for details).
     */
    if ( argc > 1 )
    {
        if ( strcmp(argv[1], "0") == SAME )
        {
            debug_off();  override_debug_changes();
            /* Done processing; move filename down (if it's there). */
            argv[1] = argc > 2 ? argv[2] : argv[1];
            argc--;
        }
        else if ( strcmp(argv[1], "1") == SAME )
        {
            debug_on();  override_debug_changes();
            /* Done processing; move filename down (if it's there). */
            argv[1] = argc > 2 ? argv[2] : argv[1];
            argc--;
        }
        else if ( argc > 2 && strcmp(argv[2], "0") == SAME )
        {
            debug_off();  override_debug_changes();
            argc--;
        }
        else if ( argc > 2 && strcmp(argv[2], "1") == SAME )
        {
            debug_on();  override_debug_changes();
            argc--;
        }
    }

    /* At this point, we have handled/erased the debugging choice, so
     * argc should be 0 or 1, depending on whether a filename was
     * provided.  Check the argument count now, since there's no need to
     * open the file if the argument count is wrong.
     */
    if ( argc > 2 )
    {
        printError("Usage:  %s [filename] [0|1]\n", argv[0]);
        return 0;
    }

    /* Process the filename, if one was passed in. */
    if ( argc > 1 )
    {
        /* Open the file for reading */
        if ((fptr = fopen (argv[1], "r")) == NULL)
        {
            printError("Error: Cannot open file %s.\n", argv[1]);
            return NULL;
        }
    }
    else  /* No file passed in; use standard input. */
        fptr = stdin;

    return fptr;   /* Everything was OK! */
}
