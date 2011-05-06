#ifndef STRING_C
#define STRING_C

static string printString(Object self) {
  size_t result;
  string str = calloc(MAX_SPRINTF_LENGTH, sizeof(string));
  string value = self->value.stringValue;

  result = snprintf(str, MAX_SPRINTF_LENGTH, "\"%s\"", value);

  if (result > MAX_SPRINTF_LENGTH) {
    str = calloc(result, sizeof(string));
    snprintf(str, result, "\"%s\"", value);
  }

  return str;
}

static Object makeStringFromCString(string str) {
  Object obj = malloc(sizeof(sObject));

  obj->type              = STRING;
  obj->value.stringValue = str;
  obj->print             = &printString;
  obj->eval              = &evalPrimitive;

  return obj;
}

static Object makeString() {
  Token *token = getToken();
  return makeStringFromCString(token->str);
}

#endif