#ifndef MAIN_C
#define MAIN_C

#include "loop.h"

int main(int argc, char **argv) {
  ds_start();

  if (argc >= 2) {
    set_source(argv[2]);

    do {
      print(eval(read()));

      Token *nextToken = getToken();
      putBackToken();

      if (nextToken == NULL) {
        break;
      } else {
        puts("");
      }
    } while (1);
  }

  return 0;
}

#endif