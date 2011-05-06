#ifndef SYMBOL_C
#define SYMBOL_C

static Object evalSymbol(Object self, Object env) {
  return getEnvironmentValue(env, self);
}

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

static Object symbolFromCString(string str) {
  Object oString = makeStringFromCString(str);
  Object obj = HashGet(symbol_table, oString);

  if (!obj) {
    obj = malloc(sizeof(sObject));
    obj->type              = SYMBOL;
    obj->value.stringValue = str;
    obj->print             = &printSymbol;
    obj->eval              = &evalSymbol;

    HashSet(symbol_table, oString, obj);
  }

  return obj;
}

static Object makeSymbol() {
  return symbolFromCString(getToken()->str);
}

#endif