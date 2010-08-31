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

struct sList {
  struct sObject *head;
  struct sObject *tail;
};

typedef struct sList  sList;
typedef struct sList* List;

typedef union {
  long         intValue;
  float        floatValue;
  bool         booleanValue;
  string       stringValue;
  List         listValue;
} oValue;

struct sObject {
  enum types type;
  oValue value;
  struct sObject *(*print)(struct sObject *);
  struct sObject *(*eval)(struct sObject *);
  void            (*free)(struct sObject *);
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