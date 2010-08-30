#ifndef SYMBOL_C
#define SYMBOL_C

static Object printSymbol(Object self) {
  printf("%s", self->value.stringValue);
  return self;
}

static Object evalSymbol(Object self) {
  return self;
}

static Object makeSymbol() {
  Token *token = getToken();
  Object obj   = malloc(sizeof(sObject));

  obj->type              = SYMBOL;
  obj->value.stringValue = token->str;
  obj->print             = &printSymbol;
  obj->eval              = &evalSymbol;

  return obj;
}

#endif