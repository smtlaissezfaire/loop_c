#ifndef LIST_C
#define LIST_C

static Object evList(Object, Object);
static string printList(Object);

static Object car(Object list) {
  Object head = list->head;

  if (head == NULL) {
    exitWithMessage(4, "car: expects argument of type <pair>; given ()");
  }

  return head;
}

static Object cdr(Object list) {
  Object tail = list->tail;

  if (tail == NULL) {
    exitWithMessage(5, "cdr: expects argument of type <pair>; given ()");
  }

  return tail;
}

static Object cons(Object head, Object tail) {
  Object obj = malloc(sizeof(sObject));

  obj->head = head;
  obj->tail = tail;

  obj->type  = LIST;
  obj->eval  = &evList;
  obj->print = &printList;

  return obj;
}

int empty_p(Object self) {
  return self == nil;
}

static int list_p(Object obj) {
  return obj->type == LIST;
}

static string alloc_strcat(string s1, string s2) {
  s1 = realloc(s1, (strlen(s1) + strlen(s2) + 1) * sizeof(string));
  strcat(s1, s2);
  return s1;
}

static string printList(Object self) {
  Object next;
  int first = 1;
  string str = calloc(2, sizeof(string));

  if (!list_p(self)) {
    exitWithMessage(-2, "Internal error in printList");
  }

  str = alloc_strcat(str, "(");

  for (next = self ;;) {
    if (empty_p(next)) {
      str = alloc_strcat(str, ")");
      break;
    } else {
      if (first) {
        first = 0;
      } else {
        str = alloc_strcat(str, " ");
      }

      if (next->type == LIST) {
        str = alloc_strcat(str, car(next)->print(car(next)));
        next = cdr(next);
      } else {
        str = alloc_strcat(str, ". ");
        str = alloc_strcat(str, next->print(next));
        str = alloc_strcat(str, ")");
        break;
      }
    }
  }

  return str;
}

static Object evList(Object self, Object env) {
  Object fun = eval(car(self), env);
  Object args = cdr(self);

  return apply(fun, args, env);
}

static Object makeList() {
  Object head;
  Token *token = getToken();

  if (token->type == tCLOSE_PAREN) {
    return nil;
  } else {
    putBackToken();
    head = read();

    return cons(head, makeList());
  }
}

#endif