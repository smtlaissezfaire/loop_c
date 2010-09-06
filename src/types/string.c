#ifndef STRING_C
#define STRING_C

static string printString(Object self) {
  string str;
  asprintf(&str, "\"%s\"", self->value.stringValue);
  return str;
}

static Object evalString(Object self) {
  return self;
}

static Object makeString() {
  Token *token = getToken();
  Object obj   = malloc(sizeof(sObject));

  obj->type              = STRING;
  obj->value.stringValue = token->str;
  obj->print             = &printString;
  obj->eval              = &evalString;

  return obj;
}

#endif