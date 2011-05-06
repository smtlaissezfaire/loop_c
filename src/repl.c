#ifndef REPL_C
#define REPL_C

#include "loop.h"

#define REPL_STRING_LENGTH 1000

void repl_intro() {
  puts("welcome to the loop repl!");
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
    set_source(buf);

    if (strcmp(buf, ".quit\n") == 0) {
      break;
    }

    print(eval(read(), global_env));
    puts("");

    repl_prompt();
  }

  return 0;
}

#endif