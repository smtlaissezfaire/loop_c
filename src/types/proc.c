#ifndef PROC_C
#define PROC_C

static Object evalProc(Object self) {
  return eval(self->body);
}

static string printProc(Object self) {
  return "#<proc>";
}

static Object makeProc(Object formal_args, Object body) {
  Object obj = malloc(sizeof(sObject));

  obj->type        = PROC;
  obj->print       = &printProc;
  obj->eval        = &evalProc;
  obj->formal_args = formal_args;
  obj->body        = body;

  return obj;
}

#endif