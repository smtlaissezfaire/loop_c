#ifndef ENVIRONMENT_C
#define ENVIRONMENT_C

Object bind(Object self, Object keys, Object values) {
  Object hash = makeHash();

  Object keysList = keys;
  Object valuesList = values;

  while (true) {
    if (keysList == nil || valuesList == nil) {
      break;
    } else {
      Object key = car(keysList);
      Object value = car(valuesList);

      HashSet(hash, key, value);

      keysList = cdr(keysList);
      valuesList = cdr(valuesList);
    }
  }

  return cons(hash, self);
}

Object getEnvironmentValue(Object self, Object key) {
  Object value;
  Object list = self;

  while (true) {
    if (list == nil) {
      return nil;
    }

    value = HashGet(car(list), key);

    if (value) {
      return value;
    }

    list = cdr(list);
  }
}

Object getEnvironmentValues(Object self, Object keys) {
  if (empty_p(keys)) {
    return nil;
  } else {
    return cons(getEnvironmentValue(self, car(keys)),
                getEnvironmentValues(self, cdr(keys)));
  }
}

Object setEnvironmentValue(Object self, Object key, Object value) {
  HashSet(car(self), key, value);
  return self;
}

static Object makeEnvironment() {
  return cons(makeHash(), nil);
}

#endif