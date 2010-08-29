#include "shared.h"
#include "scanner.h"
#include "escheme.h"

#include "types/int.c"
#include "types/float.c"

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
    default:
      exitWithMessage(1, "default case in makeObject - couldn't make object.  INTERNAL ERROR");
  }

  /* just here to make the compiler happy */
  return makeInt();
}

static Object eval(Object obj) {
  return obj->eval(obj);
}

static void print(Object obj) {
  obj->print(obj);
}

int main(int argc, char **argv) {
  if (argc >= 2) {
    source = argv[2];
    print(eval(read()));
  }

  return 0;
}