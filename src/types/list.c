#ifndef LIST_C
#define LIST_C

static Object printList(Object self) {
  exitWithMessage(1, "printList: NotYetImplemented");
  /*
  printf("(");
  printf(")");
  */

  return self;
}

static Object evalList(Object self) {
  Object head = self->value.listValue->head;
  Object tail = self->value.listValue->tail;

  if (strcmp(head->value.stringValue, "quote") == 0) {
    return tail->value.listValue->head;
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
  Object obj = malloc(sizeof(sObject));
  Token *token = getToken();

  if (token->type == tOPEN_PAREN) {
    /* skip the open paren */
    token = getToken();
  }

  if (token->type == tCLOSE_PAREN) {
    /* nil */
  } else {
    putBackToken();
    head = read();
    obj->value.listValue = makeCons(head, makeList());
  }

  obj->type            = LIST;
  obj->eval            = &evalList;
  obj->print           = &printList;

  return obj;
}

#endif