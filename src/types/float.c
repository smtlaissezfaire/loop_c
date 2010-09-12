#ifndef FLOAT_C
#define FLOAT_C

static float getValueFloat(Object self) {
  return self->value.floatValue;
}

static string printFloat(Object self) {
  size_t result;
  string str = calloc(MAX_SPRINTF_LENGTH, sizeof(string));
  float value = getValueFloat(self);

  result = snprintf(str, MAX_SPRINTF_LENGTH, "%f", value);

  if (result > MAX_SPRINTF_LENGTH) {
    str = calloc(result, sizeof(string));
    snprintf(str, result, "%f", value);
  }

  return str;
}

static Object makeFloat() {
  Token *token = getToken();
  Object obj   = malloc(sizeof(sObject));

  obj->type             = FLOAT;
  obj->value.floatValue = atof(token->str);
  obj->print            = &printFloat;
  obj->eval             = &evalPrimitive;

  return obj;
}

#endif