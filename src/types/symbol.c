#ifndef SYMBOL_C
#define SYMBOL_C

static Object symbol_table = NULL;

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

static Object makeSymbol() {
  Object obj = NULL;
  string str = getToken()->str;

  HASH_FIND_STR(symbol_table, str, obj);

  if (!obj) {
    obj = malloc(sizeof(sObject));
    obj->type              = SYMBOL;
    obj->value.stringValue = str;
    obj->print             = &printSymbol;
    obj->eval              = &evalPrimitive;

    HASH_ADD_STRING(symbol_table, str, obj);
  }

  return obj;
}

#endif