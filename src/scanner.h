enum tokenTypes {
  tINT,
  tFLOAT,
  tSTRING,
  tID,
  tQUOTE,
  tBOOLEAN,
  tOPEN_PAREN,
  tCLOSE_PAREN
};

struct token {
  enum tokenTypes type;
  string str;
  struct token *nextToken;
};

typedef struct token Token;

Token *scan(string);