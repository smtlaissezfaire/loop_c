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

static Object evalExpressions(Object expressions, Object environment) {
  Object returnValue = nil;

  Object nextExpression;
  Object restOfExpressions = expressions;

  do {
    nextExpression    = car(restOfExpressions);
    restOfExpressions = cdr(restOfExpressions);

    returnValue = eval(nextExpression, environment);
  } while (!empty_p(restOfExpressions));

  return returnValue;
}

static Object applyProc(Object self, Object argsUnevaluated) {
  Object argValues = listOfValues(argsUnevaluated, self->env);
  Object tmpEnv    = bind(self->env, self->formal_args, argValues);

  return evalExpressions(self->body, tmpEnv);
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
