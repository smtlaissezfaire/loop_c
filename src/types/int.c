#ifndef INT_C
#define INT_C

static long getValueInt(Object self) {
  return self->value.intValue;
}

static string printInt(Object self) {
  size_t result;
  string str = calloc(MAX_SPRINTF_LENGTH, sizeof(string));
  long value = getValueInt(self);

  result = snprintf(str, MAX_SPRINTF_LENGTH, "%lu", value);

  if (result > MAX_SPRINTF_LENGTH) {
    str = calloc(result, sizeof(string));
    snprintf(str, result, "%lu", value);
  }

  return str;
}

static Object makeInt() {
  Token *token = getToken();
  Object obj   = malloc(sizeof(sObject));

  obj->type           = INT;
  obj->value.intValue = strtol(token->str, NULL, 10);
  obj->print          = &printInt;
  obj->eval           = &evalPrimitive;

  return obj;
}

#endif