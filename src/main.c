#ifndef MAIN_C
#define MAIN_C

#include "loop.h"

int main(int argc, char **argv) {
  ds_start();

  if (argc >= 2) {
    set_source(argv[2]);

    while (true) {
      eval(read(), global_env);

      Token *nextToken = getToken();
      putBackToken();

      if (nextToken == NULL) {
        break;
      }
    }
  }

  return 0;
}

#endif