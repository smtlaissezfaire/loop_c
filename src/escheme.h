#ifndef ESCHEME_H
#define ESCHEME_H

#include "shared.h"
#include "scanner.h"

enum types {
  INT,
  FLOAT,
  STRING,
  SYMBOL,
  BOOLEAN,
  LIST,
  PROC
};

typedef union {
  long         intValue;
  float        floatValue;
  bool         booleanValue;
  string       stringValue;
} oValue;

struct sObject {
  enum types type;
  oValue value;
  struct sObject *head;
  struct sObject *tail;
          string (*print)(struct sObject *);
  struct sObject *(*eval)(struct sObject *);
};

typedef struct sObject sObject;
typedef sObject*       Object;

static Token *getToken();
static Token *putBackToken();
static Object read();
static Object eval();

/* globals */
Object nil;


/* this is to compensate for issues with asprintf
calling the generic malloc, not the malloc defined by the bohem GC

See http://stackoverflow.com/questions/3655031/how-to-use-asprintf-with-the-boehm-gc/3655083#3655083 */
#define MAX_SPRINTF_LENGTH (size_t)12

#include "types/int.c"
#include "types/float.c"
#include "types/booleans.c"
#include "types/string.c"
#include "types/list.c"
#include "types/symbol.c"

static string source;
static Token *currentToken  = NULL;
static Token *previousToken = NULL;

#endif