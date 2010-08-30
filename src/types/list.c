#ifndef LIST_C
#define LIST_C

static Object car(Object list) {
  return list->value.listValue->head;
}

static Object cdr(Object list) {
  return list->value.listValue->tail;
}

static int empty_p(Object self) {
  return self == nil;
}

static int list_p(Object obj) {
  return obj->type == LIST;
}

static Object printList(Object self) {
  Object head = car(self);
  Object next;
  int first = 1;

  if (!list_p(head)) {
    head->print(head);
  } else {
    printf("(");

    next = head;

    for(;;) {
      if (list_p(next)) {
        if (empty_p(next)) {
          printf(")");
          break;
        } else {
          if (first) {
            first = 0;
          } else {
            printf(" ");
          }

          next->print(next);
        }
      } else {
        exitWithMessage(-2, "Internal error in printList");
        break;
      }

      next = cdr(next);
    }
  }

  return self;
}

static Object evalList(Object self) {
  Object head = car(self);
  Object tail = cdr(self);
  string fun_name = head->value.stringValue;

  if (strcmp(fun_name, "quote") == 0) {
    return tail;
  } else {
    printf("UNKNOWN FUNCTION: %s", head->value.stringValue);
  }

  return self;
}

static List makeCons(Object head, Object tail) {
  List list = malloc(sizeof(sList));
  list->head = head;
  list->tail = tail;
  return list;
}

static Object makeList() {
  Object head;
  Object obj;
  Token *token = getToken();

  if (token->type == tCLOSE_PAREN) {
    return nil;
  } else {
    putBackToken();
    head = read();

    obj = malloc(sizeof(sObject));
    obj->value.listValue = makeCons(head, makeList());

    obj->type            = LIST;
    obj->eval            = &evalList;
    obj->print           = &printList;

    return obj;
  }
}

#endif