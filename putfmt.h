/*
 putfmt.h
 foundation
 
 Created by Christopher Loonam on 11/9/15.
   Copyright (c) 2015 Christopher Loonam. All rights reserved.
*/

#ifndef __foundation__putfmt__
#define __foundation__putfmt__

#include <stdio.h>

struct dict;

/**
 @brief @c deflt is a global variable that defines the functions that will be used in the @c putfmt() group of functions. It is of the type @c dict_t, meaning that it can easily be extended by adding an entry to the dictionary. It can also be reassigned, but doing this will result in the loss of the default functions for handling integers, strings, etc.
 @example dictadd(deflt, (void *)pointerToFunc, "S");  S can be any character - this allows for the overriding of default functions
 @warning If you are adding your own functions to @c deflt, you must either call @c putfmt() or @c fmtdef() before attempting to add entries to the dictionary; if this is not done, @c deflt will be @c NULL.
 */
extern struct dict *deflt;

/**
 @brief Prints a formatted string to @c stdout.
 @param fmt The format string. Accepted formats can be extended; see @c deflt for more information.
 @return The number of characters printed.
 */
size_t putfmt(const char *fmt, ...);

/**
 @brief Creates and returns a formatted string.
 @param fmt The format string. Accepted formats can be extended; see @c deflt for more information.
 @return A newly allocated string containing the formatted output. This string is dynamically allocated, so, when it is no longer needed, its memory should be released with a call to @c free().
 */
char *sputfmt(const char *fmt, ...);

/**
 @brief Creates and returns a formatted string.
 @param fmt The format string. Accepted formats can be extended; see @c deflt for more information.
 @param lst The variable arguments list to use for the format string. @c va_start should be called prior to this function call, and @c va_end should be called after it has returned.
 @return A newly allocated string containing the formatted output. This string is dynamically allocated, so, when it is no longer needed, its memory should be released with a call to @c free().
 */
char *svputfmt(const char *fmt, va_list lst);

/**
 @brief Initializes @c deflt to its default state, holding the functions for the supported format types. Either this or @c putfmt() must be called prior to calling @c dictadd() on @c deflt.
 @sa deflt
 */
void fmtdef(void);

#endif /* defined(__foundation__putfmt__) */
