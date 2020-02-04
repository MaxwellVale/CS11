#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INTS = 32;

void usage(char program[]) {
  fprintf(stderr, "usage: %s [-b] [-q] int1 [int2 .. ] (maximum 32 numbers)\n", program);
  exit(1);
}

void bubbleSort(int nums[]) {

}

void minSort(int nums[]) {

}

int main(int argc, char *argv[]) {
  int i;
  int arrIndex = 0;
  int nums[MAX_INTS];
  int bubble = 0;
  int quiet = 0;
  int numInts = 0;
  if (argc == 0) {
    usage(argv[0]);
  }
  for (i = 0; i < argc, i++) {
    if (arrIndex == MAX_INTS) {
      usage(argv[0]);
    }
    else if (strcmp(argv[i], "-b") == 0) {
      bubble = 1;
    }
    else if (strcmp(argv[i], "-q") == 0) {
      quiet = 1;
    }
    else {
      nums[arrIndex] = atoi(argv[i]);
      arrIndex++;
    }
  }
  return 0;
}
