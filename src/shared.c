#ifndef SHARED_C
#define SHARED_C

#include "shared.h"

void exitWithMessage(signed int exitStatus, string message) {
  printf("FATAL ERROR: %s", message);
  exit(exitStatus);
}

#endif