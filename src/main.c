#ifndef MAIN_C
#define MAIN_C

#include "escheme.h"

int main(int argc, char **argv) {
  ds_start();

  if (argc >= 2) {
    source = argv[2];
    print(eval(read()));
  }

  return 0;
}

#endif