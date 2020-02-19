#include <stdio.h>
#include <stdlib.h>
#include "memcheck.h"
#include <string.h>

/* Prints usage message if incorrect number of command line arguments given */
void usage(char program[]);

/* Populates the array with a pseudorandom arrangement of 0s and 1s */
void populate_array(int array[], int length);

/* Updates the array and returns the next generation */
int *update(int array[], int length);

/* Prints out the array with "." representing 0 and "*" representing 1 */
void print_array(int array[], int length);

void usage(char program[]) {
    fprintf(stderr, "usage: %s numCells numGenerations\n", program);
    exit(1);
}

void failed_allocation() {
    fprintf(stderr, "Error! Memory allocation failed!\n");
    exit(1);
}

void populate_array(int array[], int length) {
    int i;
    for (i = 0; i < length; i++) {
        /* Will populate the array with all 0s and 1s */
        array[i] = rand() % 2;
    }
}

int *update(int array[], int length) {
    int i;
    int before; /* Previous index */
    int after; /* Next index */
    int *newArr; /* Pointer to the next generation array */
    newArr = (int *) calloc(length, sizeof(int));
    if (newArr == NULL) { /* Check for failed allocation! */
        failed_allocation();
    }
    for (i = 0; i < length; i++) {
        before = i - 1;
        after = i + 1;
        /* If looking at 0th index, compare index 0 and 1 */
        if (before < 0) {
            before = 0;
        }
        /* If looking at last index, compare index length - 1 and length - 2 */
        if (after == length) {
            after = length - 1;
        }
        /* General rule for updating the array */
        /* Only allows for one of the neighbors to be "full" */
        if (array[i] == 0 && array[before] + array[after] == 1) {
            newArr[i] = 1;
        }
        else {
            newArr[i] = 0;
        }
    }
    return newArr;
}

void print_array(int array[], int length) {
    int i;
    for (i = 0; i < length; i++) {
        /* 
         * 0 --> "."
         * 1 --> "*"
         */
        if (array[i] == 0) {
            printf(".");
        }
        else {
            printf("*");
        }
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int numCells;
    int numGens;
    int *arr;
    int *newArr;
    int i;
    int j;
    /* Check for incorrect number of cmd line args */
    if (argc != 3) {
        usage(argv[0]);
    }
    numCells = atoi(argv[1]);
    numGens = atoi(argv[2]);
    arr = (int *) calloc(numCells, sizeof(int));
    /* Check for failed memory allocation! */
    if (arr == NULL) {
        failed_allocation();
    }
    populate_array(arr, numCells);
    print_array(arr, numCells);
    /* Updates the array numGens times */
    for (i = 0; i < numGens; i++) {
        newArr = update(arr, numCells);
        /* Copies over the next generation array and then frees the memory */
        for (j = 0; j < numCells; j++) {
            arr[j] = newArr[j];
        }
        free(newArr);
        print_array(arr, numCells);
    }
    free(arr);
    print_memory_leaks();
    return 0;
}
