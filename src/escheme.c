#include "shared.h"
#include "scanner.h"
#include "escheme.h"
#include "types/int.c"

static string source;
static Token *currentToken  = NULL;
static Token *previousToken = NULL;

static Token *getToken() {
  if (currentToken == NULL) {
    currentToken = scan(source);
    previousToken = currentToken;
  } else {
    previousToken = currentToken;
    currentToken = currentToken->nextToken;
  }

  return currentToken;
}

Object read() {
  return makeInt();
}

Object eval(Object obj) {
  return obj;
}

void print(Object obj) {
  obj->print(obj);
}

int main(int argc, char **argv) {
  if (argc >= 2) {
    source = argv[2];
    print(eval(read()));
  }

  return 0;
}