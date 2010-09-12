#ifndef ESCHEME_C
#define ESCHEME_C

#include "escheme.h"

static Token *currentToken;
static Token *previousToken;
static Token *getToken();
static Token *putBackToken();
static string source;

#include "types/int.c"
#include "types/float.c"
#include "types/booleans.c"
#include "types/string.c"
#include "types/symbol.c"
#include "types/proc.c"
#include "types/list.c"

static Token *getToken() {
  if (currentToken == NULL) {
    currentToken = scan(source);
    previousToken = NULL;
  } else {
    previousToken = currentToken;
    currentToken = currentToken->nextToken;
  }

  return currentToken;
}

static Token *putBackToken() {
  currentToken = previousToken;
  return currentToken;
}

Object read() {
  Token *token = getToken();
  putBackToken();

  switch(token->type) {
    case tINT:
      return makeInt();
    case tFLOAT:
      return makeFloat();
    case tBOOLEAN:
      return makeBoolean();
    case tSTRING:
      return makeString();
    case tSYMBOL:
      return makeSymbol();
    case tOPEN_PAREN:
      getToken(); /* skip the open paren */
      return makeList();
    default:
      exitWithMessage(-1, "default case in makeObject - couldn't make object.  INTERNAL ERROR");
  }

  /* just here to make the compiler happy */
  return makeInt();
}

Object eval(Object obj) {
  return obj->eval(obj);
}

Object apply(Object fun, Object applied_params) {
  return fun->eval(fun);
}

void print(Object obj) {
  string str = obj->print(obj);
  printf("%s", str);
}

Object isEqual(Object o1, Object o2) {
  return o1 == o2 ? booleanTrue : booleanFalse;
}

static void allocate_globals() {
  nil          = cons(NULL, NULL);
  booleanTrue  = makePrimitiveBoolean(true);
  booleanFalse = makePrimitiveBoolean(false);
}

void ds_start() {
  GC_INIT();
  allocate_globals();
}

void set_source(string src) {
  source = src;
  currentToken = NULL;
  previousToken = NULL;
}

#endif