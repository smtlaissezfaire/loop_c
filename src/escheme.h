enum types {
  INT,
  FLOAT,
  STRING,
  SYMBOL,
  BOOLEAN,
  CONS,
  PROC
};

typedef union {
  long   intValue;
  float  floatValue;
  bool   booleanValue;
  string stringValue;
} oValue;

struct sObject {
  enum types type;
  oValue value;
  struct sObject *(*print)(struct sObject *);
  struct sObject *(*eval)(struct sObject *);
};

typedef struct sObject sObject;
typedef sObject*       Object;

static Token * getToken();
