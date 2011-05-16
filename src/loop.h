#ifndef ESCHEME_H
#define ESCHEME_H

#include "shared.h"
#include "scanner.h"
#include "uthash.h"

#define HASH_ADD_STRING(table, str, obj) HASH_ADD_KEYPTR(hh, (table), (str), strlen((str)), (obj))

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
  PROC,
  PRIM_PROC,
  HASH
};

typedef union {
  long         intValue;
  float        floatValue;
  bool         booleanValue;
  string       stringValue;
} oValue;

struct sObject {
  UT_hash_handle hh;
  struct sObject *hashTable;

  enum types type;
  oValue value;
  struct sObject *head;
  struct sObject *tail;
  struct sObject *formal_args;
  struct sObject *body;
          string (*print)(struct sObject *);
  struct sObject *(*eval)(struct sObject *, struct sObject *);
  struct sObject *env;
};

typedef struct sObject sObject;
typedef sObject*       Object;

Object read();
Object eval(Object obj, Object env);
void print();
Object apply();
Object isEqual();
void ds_start();
void set_source();
Object bind(Object self, Object keys, Object values);
Token *getToken();
Token *putBackToken();
Object getEnvironmentValue(Object self, Object key);
Object getEnvironmentValues(Object self, Object keys);
Object setEnvironmentValue(Object self, Object key, Object value);
Object HashGet(Object self, Object key);
Object HashSet(Object self, Object key, Object value);
int empty_p(Object self);

/* globals */
Object nil;
Object booleanTrue;
Object booleanFalse;
Object global_env;
Object symbol_table;

#endif