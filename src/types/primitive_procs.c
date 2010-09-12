static Object primitive_quote(Object args) {
  return car(args);
}

static Object primitive_car(Object args) {
  Object fun_and_args = car(args);
  Object result = fun_and_args->eval(fun_and_args);

  return car(result);
}

static Object primitive_cdr(Object args) {
  Object fun_and_args = car(args);
  Object result = fun_and_args->eval(fun_and_args);
  return cdr(result);
}

static Object primitive_cons(Object args) {
  Object fun_and_args = car(args);
  Object result = fun_and_args->eval(fun_and_args);
  Object second_arg_and_fun = car(cdr(args));
  return cons(result, second_arg_and_fun->eval(second_arg_and_fun));
}

static Object primitive_lambda(Object args) {
  Object formal_args = car(args);
  Object body        = car(cdr(args));
  return makeProc(formal_args, body);
}

static Object primtive_equal_p(Object args) {
  Object o1 = eval(car(args));
  Object o2 = eval(car(cdr(args)));

  return isEqual(o1, o2);
}