static Object primitive_quote(Object args, Object env __attribute__ ((unused))) {
  return car(args);
}

static Object primitive_car(Object args, Object env) {
  Object fun_and_args = car(args);
  Object result = fun_and_args->eval(fun_and_args, env);

  return car(result);
}

static Object primitive_cdr(Object args, Object env) {
  Object fun_and_args = car(args);
  Object result = fun_and_args->eval(fun_and_args, env);
  return cdr(result);
}

static Object primitive_cons(Object args, Object env) {
  Object fun_and_args = car(args);
  Object result = fun_and_args->eval(fun_and_args, env);
  Object second_arg_and_fun = car(cdr(args));
  return cons(result, second_arg_and_fun->eval(second_arg_and_fun, env));
}

static Object primitive_lambda(Object args, Object env) {
  Object formal_args = car(args);
  Object body        = car(cdr(args));
  return makeProc(formal_args, body, env);
}

static Object primitive_equal_p(Object args, Object env) {
  Object o1 = eval(car(args), env);
  Object o2 = eval(car(cdr(args)), env);

  return isEqual(o1, o2);
}

static Object primitive_print(Object args, Object env) {
  Object obj = eval(car(args), env);

  print(obj);
  return obj;
}

static Object primitive_define(Object args, Object env) {
  Object variable = car(args);
  Object value    = eval(car(cdr(args)), env);

  setEnvironmentValue(env, variable, value);
  return value;
}

static Object primitive_cond(Object args, Object env) {
  if (empty_p(args)) {
    return booleanFalse;
  }

  Object pair = car(args);

  // fixme: else is working because identifiers
  // that aren't defined are evaluating to nil,
  // i.e. ().
  if (eval(car(pair), env) == booleanFalse) {
    return primitive_cond(cdr(args), env);
  } else {
    return eval(car(cdr(pair)), env);
  }

  return booleanTrue;
}

static string printPrimitiveProc() {
  return "#<primitive-proc>";
}

static Object applyPrimitiveProc(Object self, Object argValues, Object env) {
  return self->eval(argValues, env); // should this be the global env?
}

static Object makePrimitiveProc(string fun_name, Object (*fun)(Object, Object)) {
  Object obj = malloc(sizeof(sObject));

  obj->type  = PRIM_PROC;
  obj->print = &printPrimitiveProc;
  obj->eval  = fun;
  obj->body  = nil;
  obj->env   = global_env;

  setEnvironmentValue(global_env, symbolFromCString(fun_name), obj);

  return obj;
}
