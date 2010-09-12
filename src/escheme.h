#ifndef ESCHEME_H
#define ESCHEME_H

#include "shared.h"
#include "scanner.h"

/* this is to compensate for issues with asprintf
calling the generic malloc, not the malloc defined by the bohem GC

See http://stackoverflow.com/questions/3655031/how-to-use-asprintf-with-the-boehm-gc/3655083#3655083 */
#define MAX_SPRINTF_LENGTH (size_t)12

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
  struct sObject *formal_args;
  struct sObject *body;
          string (*print)(struct sObject *);
  struct sObject *(*eval)(struct sObject *);
};

typedef struct sObject sObject;
typedef sObject*       Object;

Object read();
Object eval();
void print();
Object apply();
void ds_start();
void set_source();

/* globals */
Object nil;

#endif