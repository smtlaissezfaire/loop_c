#ifndef MAIN_C
#define MAIN_C

#include "loop.h"

#define MAX_FILE_LENGTH 1000000

static char *readFile(char **argv) {
  char contents[MAX_FILE_LENGTH];

  FILE *fp = fopen(argv[1], "r");

  if (!fp) {
    fprintf(stderr, "Can't open input file!\n");
    exit(1);
  }

  fread(contents, 1, MAX_FILE_LENGTH, fp);
  fclose(fp);

  string stackContents = calloc(sizeof(char), (strlen(contents) + 1));
  strcpy(stackContents, contents);
  return stackContents;
}

static void set_source_from_args(int argc, char **argv) {
  if (argc == 3 && strcmp(argv[1], "-e") == 0) { // it's using the -e command
    set_source(argv[2]);
  } else if (argc == 2) { // it's a file
    set_source(readFile(argv));
  } else {
    puts("No suitable arguments given to loop");
    exit(-1);
  }
}

int main(int argc, char **argv) {
  ds_start();

  set_source_from_args(argc, argv);

  while (true) {
    eval(read(), global_env);

    Token *nextToken = getToken();
    putBackToken();

    if (nextToken == NULL) {
      break;
    }
  }

  return 0;
}

#endif