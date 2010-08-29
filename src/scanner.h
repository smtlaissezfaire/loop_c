/*
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
*/

enum tokenTypes {
  tINT,
  tFLOAT,
  tBOOLEAN
};

struct token {
  enum tokenTypes type;
  string str;
  struct token *nextToken;
};

typedef struct token Token;

Token *scan(string);