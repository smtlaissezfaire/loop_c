static Object car(Object list);
static Object cdr(Object list);
static Object cons(Object head, Object tail);

static Object evalPrimitive(Object self) {
  return self;
}