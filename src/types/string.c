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

static Object makeString() {
  Token *token = getToken();
  Object obj   = malloc(sizeof(sObject));

  obj->type              = STRING;
  obj->value.stringValue = token->str;
  obj->print             = &printString;
  obj->eval              = &evalPrimtive;

  return obj;
}

#endif