long getValue(Object self) {
  return self->value.intValue;
}

Object printInt(Object self) {
  printf("%lu", getValue(self));
  return self;
}

Object evalInt(Object self) {
  return self;
}

Object makeInt() {
  Token *token = getToken();
  Object obj   = malloc(sizeof(sObject));

  obj->type           = INT;
  obj->value.intValue = (long) atoi(token->str);
  obj->print          = &printInt;
  obj->eval           = &evalInt;

  return obj;
}
