#ifndef BOOLEANS_C
#define BOOLEANS_C

static string trueString = "#t";
static string falseString = "#f";

static string printBoolean(Object self) {
  return(self->value.booleanValue ? trueString : falseString);
}

static Object evalBoolean(Object self) {
  return self;
}

static bool parseBooleanToken(Token *token) {
  return (token->str[1] == 't') ? true : false;
}

static Object makeBoolean() {
  Token *token = getToken();
  Object obj   = malloc(sizeof(sObject));

  obj->type               = BOOLEAN;
  obj->value.booleanValue = parseBooleanToken(token);
  obj->print              = &printBoolean;
  obj->eval               = &evalBoolean;

  return obj;
}

#endif