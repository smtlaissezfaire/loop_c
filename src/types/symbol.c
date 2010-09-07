#ifndef SYMBOL_C
#define SYMBOL_C

static string printSymbol(Object self) {
  size_t result;
  string str = calloc(MAX_SPRINTF_LENGTH, sizeof(string));
  string value = self->value.stringValue;

  result = snprintf(str, MAX_SPRINTF_LENGTH, "%s", value);

  if (result > MAX_SPRINTF_LENGTH) {
    str = calloc(result, sizeof(string));
    snprintf(str, result, "%s", value);
  }

  return str;
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