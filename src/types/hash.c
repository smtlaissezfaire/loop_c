#ifndef HASH_C
#define HASH_C

static Object HashGet(Object self, Object key) {
  string str = key->print(key);
  Object obj = NULL;
  HASH_FIND_STR(self->hashTable, str, obj);
  return obj;
}

static Object HashSet(Object self, Object key, Object value) {
  string str = key->print(key);
  HASH_ADD_STRING(self->hashTable, str, value);
  return self;
}

static string printHash() {
  return "<a hash>";
}

static Object makeHash() {
  Object obj = malloc(sizeof(sObject));
  obj->type  = HASH;
  obj->print = &printHash;
  obj->eval  = &evalPrimitive;
  obj->hashTable = NULL;

  return obj;
}

#endif