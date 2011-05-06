#ifndef PROC_C
#define PROC_C

static Object applyProc(Object self, Object argValues) {
  Object body = self->body;

  if (body == nil) { // primitive proc
    // this should be apply, structed under the primitive proc type, right?
    return self->eval(argValues, global_env); // should this be the global env?
  } else {
    // this should be the body of self->apply
    return eval(body, bind(self->env, self->formal_args, argValues));
  }
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