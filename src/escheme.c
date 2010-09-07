#ifndef ESCHEME_C
#define ESCHEME_C

#include "escheme.h"

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

static Object read() {
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

static Object eval(Object obj) {
  return obj->eval(obj);
}

static void print(Object obj) {
  string str = obj->print(obj);
  printf("%s", str);
}

static void allocate_globals() {
  nil = cons(NULL, NULL);
}

static void ds_start() {
  GC_INIT();
  allocate_globals();
}

int main(int argc, char **argv) {
  ds_start();

  if (argc >= 2) {
    source = argv[2];
    print(eval(read()));
  }

  return 0;
}

#endif