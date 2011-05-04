#ifndef PROC_C
#define PROC_C

static Object applyProc(Object self, Object values) {
  Object body = self->body;

  return eval(body, bind(self->env, self->formal_args, values));
}

static string printProc() {
  return "#<proc>";
}

static Object makeProc(Object formal_args, Object body, Object env) {
  Object obj = malloc(sizeof(sObject));

  obj->type        = PROC;
  obj->print       = &printProc;
  obj->eval        = &evalPrimitive;
  obj->formal_args = formal_args;
  obj->body        = body;
  obj->env         = env;

  return obj;
}

#endif