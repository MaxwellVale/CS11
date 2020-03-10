/*
 * CS 11, C Track, lab 7
 *
 * FILE: hash_table.c
 *
 *       Implementation of the hash table functionality.
 *
 */

/*
 * Include the declaration of the hash table data structures
 * and the function prototypes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "memcheck.h"


/*** Hash function. ***/

int hash(char *s)
{
    int i;
    int sum = 0;
    for (i = 0; s[i] != '\0'; i++) {
        sum += (int) s[i];
    }
    /* printf("Hash value for '%s' is %d\n", s, sum); */
    return sum % NSLOTS;
}


/*** Linked list utilities. ***/

/* Create a single node. */
node *create_node(char *key, int value)
{
    node *newNode = (node*) malloc(sizeof(node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }
    newNode->key = key;
    newNode->value = value;
    return newNode;
}


/* Free all the nodes of a linked list. */
void free_list(node *list)
{
    node *n;
    while (list != NULL) {
        n = list;
        list = list->next;
        free(n->key);
        free(n);
    }
}


/*** Hash table utilities. ***/

/* Create a new hash table. */
hash_table *create_hash_table()
{
    hash_table *newTable;
    node **htArray;
    htArray = (node **) calloc(NSLOTS, sizeof(node *));
    if (htArray == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }
    newTable = (hash_table *) malloc(sizeof(htArray));
    if (newTable == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }
    newTable->slot = htArray;
    /* printf("Hash table created!\n"); */
    return newTable;
}


/* Free a hash table. */
void free_hash_table(hash_table *ht)
{
    int i;
    node **htArray;
    if (ht != NULL) {
        htArray = ht->slot;
        for (i = 0; i < NSLOTS; i++) {
            free_list(htArray[i]);
        }
        /* Must free the internal array as well as the struct */
        free(ht->slot);
        free(ht);
    }
}


/*
 * Look for a key in the hash table.  Return 0 if not found.
 * If it is found return the associated value.
 */
int get_value(hash_table *ht, char *key)
{
    node *n;
    int hashVal = hash(key);
    /* printf("Getting the value for '%s'\n", key); */
    if (ht->slot[hashVal] != NULL) {
        n = ht->slot[hashVal];
        while (n != NULL) {
            if (strcmp(n->key, key) == 0) {
                /* printf("'%s' found! Value is %d\n", key, n->value); */
                return n->value;
            }
            n = n->next;
        }
    }
    /* printf("'%s' not found!\n", key); */
    return 0;
}


/*
 * Set the value stored at a key.  If the key is not in the table,
 * create a new node and set the value to 'value'.  Note that this
 * function alters the hash table that was passed to it.
 */
void set_value(hash_table *ht, char *key, int value)
{
    node *n;
    int oldValue = get_value(ht, key);
    /* printf("Setting a key '%s' to value %d...\n", key, value);
    printf("Old value of '%s' is %d\n", key, oldValue); */
    /* If the key isn't in the hash table, add new node  */
    if (oldValue == 0) {
        n = create_node(key, value);
        n->next = ht->slot[hash(key)];
        ht->slot[hash(key)] = n;
    }
    /* Otherwise look for the key and replace its value */
    else {
        n = ht->slot[hash(key)];
        while (n != NULL) {
            if (strcmp(n->key, key) == 0) {
                n->value = value;
                break;
            }
            n = n->next;
        }
        /* Need to free the key if it is not used */
        free(key);
    }
}


/* Print out the contents of the hash table as key/value pairs. */
void print_hash_table(hash_table *ht)
{
    int i;
    node *n;
    for (i = 0; i < NSLOTS; i++) {
        n = ht->slot[i];
        while (n != NULL) {
            printf("%s %d\n", n->key, n->value);
            n = n->next;
        }
    }
}
