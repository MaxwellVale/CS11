#include <stdio.h>
#include <stdlib.h>
#include "memcheck.h"
#include <string.h>
#include <time.h>

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
    int *newArr;
    int *p1, *p2, *p3, *idx; /* Pointers to cells in arrays */
    newArr = (int *) calloc(length, sizeof(int));
    /* Check for failed memory allocation! */
    if (newArr == NULL) {
        failed_allocation();
    }
    p1 = array; /* First element in array */
    p2 = array + 1; /* Second element */
    p3 = array + 2; /* Third element */
    idx = newArr; /* Pointer to index in new array */

    /* Change the 0th index of the new array first */
    if (*p1 == 0 && *p2 == 1) {
        *idx = 1;
    }
    else {
        *idx = 0;
    }
    idx++; /* Now idx matches p2 */
    for (i = 1; i < length - 1; i++) {
        /* Change idx depending on the given rule */
        if (*p2 == 0 && *p1 + *p3 == 1) {
            *idx = 1;
        }
        else {
            *idx = 0;
        }
        p1++;
        p2++;
        p3++;
        idx++;
    }
    idx++;
    if (*p3 == 0 && *p2 == 1) {
        *idx = 1;
    }
    else {
        *idx = 0;
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
    srand(time(NULL));
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
