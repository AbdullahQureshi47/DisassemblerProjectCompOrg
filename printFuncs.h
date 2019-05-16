#ifndef _PRINT_FUNCS_H
#define _PRINT_FUNCS_H

/*
 * printError will print an error message to stderr.  After a certain
 *      number of errors have been printed, it will stop execution.
 *      printError takes a variable number of arguments, the first of
 *      which should specify the format of what should be printed
 *      (exactly like the parameters to printf).
 *
 * ERROR_LIMIT is a global variable that can be set to a different value
 *      to change the number of errors that get printed before the
 *      programs stops execution.
 *
 * printDebug will print a debugging message to stdout, but only if
 *      debugging has been turned on.
 *      printDebug takes a variable number of arguments, the first of
 *      which should specify the format of what should be printed
 *      (exactly like the parameters to printf).
 *
 * debug_on turns debugging on.
 *
 * debug_off turns debugging off.
 *
 * debug_restore goes back to the previous debugging state before the
 *      most recent call to debug_on or debug_off.
 *
 *      If you turn debugging on and off at the function level, you
 *      should restore the state at the end of the function.  In other
 *      words, you can explicitly turn debugging on (or off) at any
 *      time, but the way to reverse that is to restore to the previous
 *      state rather than to explicitly turn debugging back off (or on).
 *      This will work regardless of whether the previous state was on
 *      or off.
 *
 *      Once the debugging state has been restored to its initial state,
 *      additional calls to debug_restore will have no effect until
 *      debug_on or debug_off is called again.
 *
 * debug_is_on returns 1 if debugging is on and 0 if debugging is off.
 *
 * override_debug_changes "freezes" the debugging state in its current
 *      state, whether on or off, nulling the effect of any future calls
 *      to debug_on, debug_off, or debug_restore.
 */

void printError(const char * restrict_format, ...);

extern int ERROR_LIMIT;

void printDebug(const char * restrict_format, ...);

void debug_on(void);
void debug_off(void);
void debug_restore(void);
int  debug_is_on(void);
void override_debug_changes(void);

#endif
