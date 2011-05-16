#ifndef PROC_C
#define PROC_C

// given a list of expressions, return the list of values
static Object listOfValues(Object list, Object env) {
  if (empty_p(list)) {
    return list;
  } else {
    return cons(eval(car(list), env),
                listOfValues(cdr(list), env));
  }
}

static Object applyProc(Object self, Object argsUnevaluated) {
  Object argValues = listOfValues(argsUnevaluated, self->env);

  return eval(self->body, bind(self->env, self->formal_args, argValues));
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