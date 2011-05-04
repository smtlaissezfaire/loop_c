#ifndef ENVIRONMENT_C
#define ENVIRONMENT_C

Object bind(Object self, Object keys, Object values) {
  Object hash = makeHash();

  Object keysList = keys;
  Object valuesList = values;

  do {
    if (keysList == nil || valuesList == nil) {
      break;
    } else {
      Object key = car(keysList);
      Object value = car(valuesList);

      HashSet(hash, key, value);

      keysList = cdr(keysList);
      valuesList = cdr(valuesList);
    }
  } while(1);

  return cons(hash, self);
}

static Object getEnvironmentValue(Object self, Object key) {
  Object value;
  Object list = self;

  do {
    if (list == nil) {
      return nil;
    }

    value = HashGet(car(self), key);

    if (value) {
      return value;
    }

    list = cdr(list);
  } while (1);
}

#endif