#ifndef REPL_C
#define REPL_C

#include "escheme.h"

#define REPL_STRING_LENGTH 1000

void repl_intro() {
  puts("welcome to the escheme repl!");
  puts("use .quit to exit");
}

void repl_prompt() {
  printf("repl> ");
}

int main() {
  char buf[REPL_STRING_LENGTH + 1];

  ds_start();

  repl_intro();
  repl_prompt();

  while (fgets(buf, REPL_STRING_LENGTH, stdin) != NULL) {
    source = buf;

    if (strcmp(source, ".quit") == 0) {
      break;
    }

    print(eval(read()));
    puts("");

    repl_prompt();
  }

  return 0;
}

#endif