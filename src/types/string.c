#ifndef STRING_C
#define STRING_C

static Object printString(Object self) {
  printf("\"%s\"", self->value.stringValue);
  return self;
}

static Object evalString(Object self) {
  return self;
}

void freeString() {

}

static Object makeString() {
  Token *token = getToken();
  Object obj   = malloc(sizeof(sObject));

  obj->type              = STRING;
  obj->value.stringValue = token->str;
  obj->print             = &printString;
  obj->eval              = &evalString;
  obj->free              = &freeString;

  return obj;
}

#endif