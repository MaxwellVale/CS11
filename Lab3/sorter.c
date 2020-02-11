/*
 * Sorter
 *
 * Program can read in a maximum of 32 integers and sort them in
 * increasing order. The program utilizes Bubble Sort and Minimal Element
 * Sort to sort the numbers provided. The program defaults to Minimal
 * Element Sort, but it can be changed to Bubble Sort by adding -b at the
 * command line. There is also the choice of not printing out the sorted
 * integers using -q at the command line.
 *
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
/* Max number of integers that can be read at the command line */
#define MAX_INTS 32

/*
 * usage
 * Prints out a usage message to stderr
 *
 * Arguments
 * program -> the name of the program being run
 *
 * Does not return anything
 */
void usage(char program[]) {
  fprintf(stderr, "usage: %s [-b] [-q] int1 [int2 .. ]\
   (maximum 32 numbers)\n", program);
  exit(1);
}

/*
 * bubbleSort
 * Sorts the given array in increasing order using the Bubble Sort algorithm
 *
 * Arguments
 * nums -> Array containing integers to be sorted
 * size -> Number of integers in nums
 *
 * Does not return anything
 */
void bubbleSort(int nums[], int size) {
  int i, j;
  int temp;
  int swapped;
  for (i = 0; i < size - 1; i++) {
    swapped = 0; /* Representing a boolean value */
    for (j = 0; j < size - i - 1; j++) {
      /* Comparing consecutive integers in the array and swapping if a
      bigger integer is followed by a smaller integer. */
      if (nums[j] > nums[j + 1]) {
        swapped = 1;
        temp = nums[j];
        nums[j] = nums[j + 1];
        nums[j + 1] = temp;
      }
    }
    /* If no swaps were necessary, then the array must be sorted -> can break
    from the loop. */
    if (swapped == 0) {
      break;
    }
  }
  for (i = 1; i < size; i++) {
    assert(nums[i] >= nums[i - 1]);
  }
}

/*
 * minSort
 * Sorts the given array in increasing order using the Minimal Element Sort
 * algorithm
 *
 * Arguments
 * nums -> Array containing integers to be sorted
 * size -> Number of integers in nums
 *
 * Does not return anything
 */
void minSort(int nums[], int size) {
  int i;
  int index;
  int start;
  int smallest;
  int temp;
  /* For each index in nums, we want to find the smallest integer that comes
  after start. */
  for (start = 0; start < size; start++) {
    smallest = start;
    for (index = start; index < size; index++) {
      if (nums[index] < nums[smallest]) {
        smallest = index;
      }
    }
    /* Once the smallest is found, put that integer at start and then increment
    start */
    temp = nums[start];
    nums[start] = nums[smallest];
    nums[smallest] = temp;
  }
  for (i = 1; i < size; i++) {
    assert(nums[i] >= nums[i - 1]);
  }
}

int main(int argc, char *argv[]) {
  int i;
  int numInts = 0;
  int bubble = 0;
  int quiet = 0;
  int nums[MAX_INTS];
  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-b") == 0) {
      bubble = 1;
    }
    else if (strcmp(argv[i], "-q") == 0) {
      quiet = 1;
    }
    else if (numInts == MAX_INTS) {
      usage(argv[0]);
    }
    else {
      nums[numInts] = atoi(argv[i]);
      numInts++;
    }
  }
  if (numInts == 0) {
    usage(argv[0]);
  }
  if (bubble) {
    bubbleSort(nums, numInts);
  }
  else {
    minSort(nums, numInts);
  }
  if (quiet == 0) {
    for (i = 0; i < numInts; i++) {
      printf("%d\n", nums[i]);
    }
  }
  return 0;
}
