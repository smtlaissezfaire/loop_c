#ifndef ESCHEME_C
#define ESCHEME_C

#include "shared.h"
#include "scanner.h"
#include "escheme.h"

#include "types/int.c"
#include "types/float.c"
#include "types/booleans.c"
#include "types/string.c"
#include "types/list.c"
#include "types/symbol.c"

static string source;
static Token *currentToken  = NULL;
static Token *previousToken = NULL;

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

static Object print(Object obj) {
  return obj->print(obj);
}

static void allocate_globals() {
  nil = cons(NULL, NULL);
}

int main(int argc, char **argv) {
  GC_INIT();
  allocate_globals();

  if (argc >= 2) {
    source = argv[2];
    print(eval(read()));
  }

  return 0;
}

#endif