#ifndef SHARED_C
#define SHARED_C

#include "shared.h"

void exitWithMessage(int exitStatus, string message) {
  printf("FATAL ERROR: %s", message);
  exit(exitStatus);
}

#endif