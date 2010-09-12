#ifndef BOOLEANS_C
#define BOOLEANS_C

static Object evalBoolean(Object self) {
  return self;
}

static string printBooleanTrue() {
  return "#t";
}

static string printBooleanFalse() {
  return "#f";
}

static Object makePrimitiveBoolean(bool value) {
  Object obj = malloc(sizeof(sObject));

  obj->type               = BOOLEAN;
  obj->value.booleanValue = value;
  obj->eval               = &evalBoolean;

  if (value == true) {
    obj->print = &printBooleanTrue;
  } else {
    obj->print = &printBooleanFalse;
  }

  return obj;
}

static Object parseBooleanToken(Token *token) {
  return (token->str[1] == 't') ? booleanTrue : booleanFalse;
}

static Object makeBoolean() {
  Token *token = getToken();
  return parseBooleanToken(token);
}

#endif