enum types {
  INT,
  FLOAT,
  STRING,
  SYMBOL,
  BOOLEAN,
  CONS,
  PROC
};

struct sObject {
  enum types type;
  void *value;
  struct sObject *(*print)(struct sObject *);
  struct sObject *(*eval)(struct sObject *);
};

typedef struct sObject sObject;
typedef sObject*       Object;

static Token * getToken();
