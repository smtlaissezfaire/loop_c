#ifndef INT_C
#define INT_C

static long getValueInt(Object self) {
  return self->value.intValue;
}

static string printInt(Object self) {
  string str;
  asprintf(&str, "%lu", getValueInt(self));
  return str;
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

#endif