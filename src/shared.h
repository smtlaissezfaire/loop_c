#ifndef SHARED_H
#define SHARED_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/* this must come last, as we don't system
   libraries, etc, using this */
#include <gc.h>
#define malloc(n)    GC_MALLOC(n)
#define calloc(m,n)  GC_MALLOC((m)*(n))
#define realloc(p,n) GC_REALLOC((p),(n))

typedef char * string;

void exitWithMessage(signed int, string);

#endif