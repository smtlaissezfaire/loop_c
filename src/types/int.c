static long getValue(Object self) {
  return self->value.intValue;
}

static Object printInt(Object self) {
  printf("%lu", getValue(self));
  return self;
}

static Object evalInt(Object self) {
  return self;
}

static Object makeInt() {
  Token *token = getToken();
  Object obj   = malloc(sizeof(sObject));

  obj->type           = INT;
  obj->value.intValue = strtol(token->str, NULL, 10);
  obj->print          = &printInt;
  obj->eval           = &evalInt;

  return obj;
}
