#ifndef ESCHEME_H
#define ESCHEME_H

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

#endif