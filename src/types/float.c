#ifndef FLOAT_C
#define FLOAT_C

static float getValueFloat(Object self) {
  return self->value.floatValue;
}

static Object printFloat(Object self) {
  printf("%f", getValueFloat(self));
  return self;
}

static Object evalFloat(Object self) {
  return self;
}

void freeFloat() {

}

static Object makeFloat() {
  Token *token = getToken();
  Object obj   = malloc(sizeof(sObject));

  obj->type             = FLOAT;
  obj->value.floatValue = atof(token->str);
  obj->print            = &printFloat;
  obj->eval             = &evalFloat;
  obj->free             = &freeFloat;

  return obj;
}

#endif