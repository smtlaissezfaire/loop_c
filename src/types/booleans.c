#ifndef BOOLEANS_C
#define BOOLEANS_C

static Object printBoolean(Object self) {
  printf("#%c", self->value.booleanValue ? 't' : 'f');
  return self;
}

static Object evalBoolean(Object self) {
  return self;
}

static bool parseBooleanToken(Token *token) {
  return (token->str[1] == 't') ? true : false;
}

void freeBoolean() {

}

static Object makeBoolean() {
  Token *token = getToken();
  Object obj   = malloc(sizeof(sObject));

  obj->type               = BOOLEAN;
  obj->value.booleanValue = parseBooleanToken(token);
  obj->print              = &printBoolean;
  obj->eval               = &evalBoolean;
  obj->free               = &freeBoolean;

  return obj;
}

#endif