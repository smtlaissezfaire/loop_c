unsigned long int getValue(Object self) {
  return((long) self->value);
}

Object printInt(Object self) {
  printf("%lu", getValue(self));
  return self;
}

Object makeInt() {
  Token *token = getToken();
  Object obj   = malloc(sizeof(sObject));

  unsigned long int num = atoi(token->str);

  obj->value = (unsigned long int *) num;
  obj->type  = INT;
  obj->print = &printInt;
  return obj;
}
