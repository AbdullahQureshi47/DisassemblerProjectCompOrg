/*
 * This file defines six functions that support the optional printing
 * of debugging messages:
 *      printDebug:     prints messages only when debugging is turned on
 *      debug_on:       turns debugging on
 *      debug_off:      turns debugging off
 *      debug_restore:  restores the previous debugging state, as it was
 *                      before the most recent call to debug_on or debug_off.
 *      debug_is_on:    returns 1 if debugging is on, 0 if it is off
 *      override_debug_changes:  deactivate future calls to debug_on,
 *                      debug_off, and debug_restore, freezing the
 *                      debugging state in its current state
 *
 * The file also defines a number of internal data values and helper
 * functions to support the six functions described above.
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "printFuncs.h"

/* Define the internal DEBUG variable shared by functions in this file. */
static const char DEBUG_DEFAULT_VALUE = 0;
static char OVERRIDE_DEBUG_CHANGES = 0;
static char DEBUG = 0; /* Not all compilers will accept DEBUG_DEFAULT_VALUE. */

/* Define the internal DEBUG stack and the functions that operate on it. */
static char * debugStack = NULL;
static unsigned debugStackCapacity = 0;
static unsigned debugStackNumEntries = 0;
static void debug_push(void);
static char debug_pop(void);
static int resizeDebugStack (void);

static const char * ERROR = "Error: cannot allocate space in memory.\n";

/**
 * void printDebug(const char * restrict_format, ...)
 *
 * This function prints a debugging message to standard output (stdout),
 * but only if debugging is currently turned on.  Debugging can be
 * turned on and off using the debug_on(), debug_off(), and
 * debug_restore() functions.
 *
 * Parameters:
 *  The parameters to printDebug are modeled on those to printf,
 *  consisting of a format and various other arguments as specified
 *  in the format.
 *
 * Output:
 *  This function prints its output to standard output (stdout).
 *
 */
void printDebug(const char * restrict_format, ...)
{
    if ( ! DEBUG )
        return;

    /* The following code allows us to call printf with the variable
     * parameters that were passed to printDebug.
     */
    va_list ap;
    va_start(ap, restrict_format);
    (void) vprintf(restrict_format, ap);
    va_end(ap);

}

/**
 * void debug_on(void)
 *
 * Turns debugging on.
 *
 */
void debug_on(void)
{
    if ( ! OVERRIDE_DEBUG_CHANGES )
    {
        debug_push();
        DEBUG = 1;
    }
}

/**
 * void debug_off(void)
 *
 * Turns debugging off.
 *
 */
void debug_off(void)
{
    if ( ! OVERRIDE_DEBUG_CHANGES )
    {
        debug_push();
        DEBUG = 0;
    }
}

/**
 * void debug_restore(void)
 *
 * Restores the DEBUG state to its previous value.  Once the debugging
 * state has been restored to its initial state, additional calls to
 * <code>debug_restore()</code> will have no effect until
 * <code>debug_on()</code> or <code>debug_off()</code> is called again.
 *
 */
void debug_restore(void)
{
    if ( ! OVERRIDE_DEBUG_CHANGES )
    {
        DEBUG = debug_pop();
    }
}

/**
 * int debug_is_on(void)
 *
 * Returns 1 if debugging is currently on, 0 if debugging is currently off.
 *
 */
int debug_is_on(void)
{
    return DEBUG;
}

/**
 * void override_debug_changes(void)
 *
 * Overrides future attempts to change the debug state, freezing it to
 * its current state (whatever that is).
 *
 */
void override_debug_changes(void)
{
    OVERRIDE_DEBUG_CHANGES = 1;
}

/**
 * void debug_push(void)
 *
 * Pushes the current debug state onto the stack.
 *
 */
static void debug_push(void)
{
    if ( debugStack == NULL || debugStackNumEntries <= debugStackCapacity )
        resizeDebugStack();

    debugStack[debugStackNumEntries++] = DEBUG;
}

/**
 * void debug_pop(void)
 *
 * Pops and returns the most recent debug state from the stack.  If
 * there was no value on the stack, returns the DEBUG_DEFAULT_VALUE.
 *
 */
static char debug_pop(void)
{
    if ( debugStackNumEntries > 0 )
        return debugStack[--debugStackNumEntries];

    return DEBUG_DEFAULT_VALUE;
}

static int resizeDebugStack (void)
  /* Postcondition: debug stack now has the capacity to hold a
   *      longer history of debug states.
   * Returns 1 if everything went OK; 0 if there was a memory
   *      allocation error
   */
{
        int    newSize;
        char * newStack;

        /* Handle initial case of new stack. */
        if ( debugStack == NULL || debugStackCapacity == 0 )
        {
            debugStackNumEntries = 0;
            newSize = 20;
        }
        else
            newSize = debugStackCapacity * 2;

        /* Create a new stack of the specified size. */
        debugStackCapacity = newSize * sizeof(*newStack);
        if ((newStack = malloc (debugStackCapacity)) == NULL)
        {
            printError ("%s", ERROR);
            return 0;           /* fatal error: couldn't allocate memory */
        }

        /* Move contents of old stack to new stack; free old stack. */
        if ( debugStack )           /* if there were entries */
        {
            (void) memcpy (newStack, debugStack, debugStackNumEntries);
            free (debugStack);
        }

        /* The new debug stack is ready to use. */
        debugStack = newStack;
        return 1;
}
