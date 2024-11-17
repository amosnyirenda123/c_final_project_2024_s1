#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MAPSIZE 100
#define MAX_STRLEN 80
#define TABLE_SIZE 50

// Define the Node structure
typedef struct Node {
    char key[MAX_STRLEN];
    char value[MAX_STRLEN];
    struct Node* nxt; 
} Node;

// Declare the hash table (defined elsewhere)
extern Node* hashTable[TABLE_SIZE];

// Declare the functions
unsigned int hash(const char *key);
void insert(Node* hashTable[], const char* key, const char* value);
char* search(Node* hashTable[], const char* key);
void delete(Node* hashTable[], const char* key);
void display(Node* hashTable[]);
void saveToFile(Node* hashTable[], const char* filename);
void loadFromFile(Node* hashTable[], const char* filename);

#endif
