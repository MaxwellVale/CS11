#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "memcheck.h"
#include "linked_list.h"

/*
 * usage
 * Prints out a usage message to stderr
 *
 * Arguments
 * program -> the name of the program being run
 *
 * Does not return anything
 */
void usage(char programp[]);

/*
 * quicksort
 * Sorts the given array using the quicksort algorithm
 * 
 * Arguments
 * nums -> Array containing the integers to be sorted
 * 
 * Return
 * A new array containing the integers from nums in increasing order
 */
node *quicksort(node *nums);

void usage(char program[]) {
  fprintf(stderr, "usage: %s [-q] int1 [int2 .. ]\n", program);
  exit(1);
}

node *quicksort(node *nums) {
    node *temp; /* Temporary node to create smaller and larger lists */
    node *sortedTemp; /* Temp pointer to concatenating smaller and 1st node */
    node *sorted; /* Final sorted list to be returned */
    node *curr; /* Pointer to current node in nums */
    node *smaller; /* List of nodes smaller than 1st node */
    node *smallerSorted; 
    node *larger; /* List of nodes equal or greater than 1st */
    node *largerSorted;
    node *copyNode; /* 1st Node in the LList */
    /* If the list is empty, there is nothing to sort */
    if (nums == NULL) {
        return NULL;
    }
    /* If the list consists of only one node, return that node */
    copyNode = create_node((*nums).data, NULL);
    if ((*nums).next == NULL) {
        return copyNode;
    }
    curr = nums->next;
    smaller = NULL;
    larger = NULL;
    /* Populating the smaller and larger lists */
    while (curr != NULL) {
        temp = (node *)malloc(sizeof(node));
        /* Checking for memory allocation! */
        if (temp == NULL) {
            fprintf(stderr, "Error: Memory allocation failed\n");
            exit(1);
        }
        temp->data = (*curr).data;
        if ((*curr).data < (*copyNode).data) {
            temp->next = smaller;
            smaller = temp;
        }
        else {
            temp->next = larger;
            larger = temp;
        }
        curr = curr->next;
    }
    /* Using new pointers so that old memory can be properly freed */
    smallerSorted = quicksort(smaller);
    largerSorted = quicksort(larger);
    free_list(smaller);
    free_list(larger);
    sortedTemp = append_lists(smallerSorted, copyNode);
    sorted = append_lists(sortedTemp, largerSorted);
    free_list(sortedTemp);
    free_list(smallerSorted);
    free_list(copyNode);
    free_list(largerSorted);
    assert(is_sorted(sorted));
    return sorted;
}

int main(int argc, char *argv[]) {
    int i;
    int numInts = 0;
    int quiet = 0;
    node *list = NULL;
    node *sortedList;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-q") == 0) {
            quiet = 1;
        }
        else { /* Filling in the LList */
            list = create_node(atoi(argv[i]), list);
            numInts++;
        }
    }
    if (numInts == 0) {
        usage(argv[0]);
    }
    /* Using another pointer so that memory @ list can be freed */
    sortedList = quicksort(list);
    free_list(list);
    list = sortedList;
    if (quiet == 0) {
        print_list(list);
    }
    free_list(sortedList);
    print_memory_leaks();
    return 0;
}
