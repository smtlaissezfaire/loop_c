#ifndef ESCHEME_C
#define ESCHEME_C

#include "loop.h"

static Token *currentToken;
static Token *previousToken;
static string source;

#include "types/primitives.c"
#include "types/int.c"
#include "types/float.c"
#include "types/booleans.c"
#include "types/string.c"
#include "types/symbol.c"
#include "types/proc.c"
#include "types/primitive_procs.c"
#include "types/list.c"
#include "types/hash.c"
#include "types/environment.c"

Token *getToken() {
  if (currentToken == NULL) {
    currentToken = scan(source);
    previousToken = NULL;
  } else {
    previousToken = currentToken;
    currentToken = currentToken->nextToken;
  }

  return currentToken;
}

Token *putBackToken() {
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

Object eval(Object obj, Object env) {
  // should env = global env if env = NULL?
  return obj->eval(obj, env);
}

Object apply(Object fun, Object args) {
  Object obj;
  assert(fun->type == PRIM_PROC || fun->type == PROC);

  switch(fun->type) {
    case PRIM_PROC:
      return applyPrimitiveProc(fun, args);
    case PROC:
      return applyProc(fun, args);
    default:
      // should never reach here, as assertion should have already failed
      return obj;
  }
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
  global_env   = makeEnvironment();
  symbol_table = makeHash();

  makePrimitiveProc("quote",  &primitive_quote);
  makePrimitiveProc("car",    &primitive_car);
  makePrimitiveProc("cdr",    &primitive_cdr);
  makePrimitiveProc("cons",   &primitive_cons);
  makePrimitiveProc("lambda", &primitive_lambda);
  makePrimitiveProc("equal?", &primitive_equal_p);
  makePrimitiveProc("print",  &primitive_print);
  makePrimitiveProc("define", &primitive_define);
  makePrimitiveProc("cond",   &primitive_cond);
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