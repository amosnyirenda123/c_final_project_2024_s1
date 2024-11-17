#include "map.h"

// Hash function using the DJB2 algorithm
unsigned int hash(const char *key) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % TABLE_SIZE;
} 

// Search for a key in the hash table
char* search(Node* hashTable[], const char* key) {
    unsigned int index = hash(key);
    Node* current = hashTable[index];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            return current->value; 
        }
        current = current->nxt;
    }
    return NULL;
}


void insert(Node* hashTable[], const char* key, const char* value) {
    char* existing_value = search(hashTable, key);
    if (existing_value == NULL) {
        unsigned int index = hash(key);
        Node* newNode = (Node*)malloc(sizeof(Node));
        strcpy(newNode->key, key);
        strcpy(newNode->value, value);
        newNode->nxt = hashTable[index];
        hashTable[index] = newNode;
    } else {
        printf("Key '%s' with value '%s' already exists in the hash table.\n", key, existing_value);
    }
}


void delete(Node* hashTable[], const char* key) {
    unsigned int index = hash(key);
    Node* current = hashTable[index];
    Node* prev = NULL;

    while (current && strcmp(current->key, key) != 0) {
        prev = current;
        current = current->nxt;
    }

    if (!current) return;

    if (prev) {
        prev->nxt = current->nxt;
    } else {
        hashTable[index] = current->nxt;
    }

    free(current);
}

void update(Node* hashTable[], const char* key){
    char value[MAX_STRLEN];
    delete(hashTable, key);
    printf("Enter new value: ");
    scanf("%s", value);
    insert(hashTable, key, value);
}


void display(Node* hashTable[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        Node* current = hashTable[i];
        while (current) {
            printf("(%s, %s) -> ", current->key, current->value);
            current = current->nxt;
        }
        printf("NULL\n");
    }
}


void saveToFile(Node* hashTable[], const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error opening file for appending.\n");
        return;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = hashTable[i];
        while (current) {
            fwrite(current, sizeof(Node), 1, file);
            current = current->nxt;
        }
    }

    fclose(file);
    printf("Hash table saved to file: %s\n", filename);
}


void loadFromFile(Node* hashTable[], const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        // File does not exist, create a new empty file
        printf("No previous hash table file '%s' found. Creating a new one.\n", filename);
        file = fopen(filename, "wb"); 
        if (file == NULL) {
            perror("Error creating file");
            return;
        }
        fclose(file); 

        file = fopen(filename, "rb");
        if (file == NULL) {
            printf("Error: Could not open newly created file '%s' for reading.\n", filename);
            return;
        }
        return;
    }

    while (1) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        size_t bytesRead = fread(newNode, sizeof(Node), 1, file);
        if (bytesRead == 0) {  // No more data to read
            free(newNode);
            break;
        }

        // Check for duplicate key in the hash table
        unsigned int index = hash(newNode->key);
        Node* current = hashTable[index];
        while (current) {
            if (strcmp(current->key, newNode->key) == 0) {
                // Key already exists, free the new node and stop processing
                free(newNode);
                break;
            }
            current = current->nxt;
        }

        if (current == NULL) {
            // Insert the new node into the hash table
            newNode->nxt = hashTable[index];
            hashTable[index] = newNode;
        }
    }

    fclose(file);
    printf("Hash table loaded from file: %s\n", filename);
}

