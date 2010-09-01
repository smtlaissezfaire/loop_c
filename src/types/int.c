#ifndef INT_C
#define INT_C

static long getValueInt(Object self) {
  return self->value.intValue;
}

static Object printInt(Object self) {
  printf("%lu", getValueInt(self));
  return self;
}

static Object evalInt(Object self) {
  return self;
}

void freeInt() {
}

static Object makeInt() {
  Token *token = getToken();
  Object obj   = malloc(sizeof(sObject));

  obj->type           = INT;
  obj->value.intValue = strtol(token->str, NULL, 10);
  obj->print          = &printInt;
  obj->eval           = &evalInt;
  obj->free           = &freeInt;

  return obj;
}

#endif