#ifndef FLOAT_C
#define FLOAT_C

static float getValueFloat(Object self) {
  return self->value.floatValue;
}

static string printFloat(Object self) {
  string str;
  asprintf(&str, "%f", getValueFloat(self));
  return str;
}

static Object evalFloat(Object self) {
  return self;
}

static Object makeFloat() {
  Token *token = getToken();
  Object obj   = malloc(sizeof(sObject));

  obj->type             = FLOAT;
  obj->value.floatValue = atof(token->str);
  obj->print            = &printFloat;
  obj->eval             = &evalFloat;

  return obj;
}

#endif