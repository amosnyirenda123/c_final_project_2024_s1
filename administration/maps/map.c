#include "map.h"
#include "../../toast.h"


unsigned int hash(const char *key) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % TABLE_SIZE;
} 


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

void update_hash(Node* hashTable[], const char* key, const char* new_value){
    int index = hash(key);  
    Node* current = hashTable[index];


    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {  
            strcpy(current->value, new_value); 
            printf("Updated key '%s' with new value '%s'.\n", key, new_value);
            return;
        }
        current = current->nxt;
    }

    printf("Key '%s' not found. Inserting new entry.\n", key);
    // Fallback
    insert(hashTable, key, new_value);
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
    char message[MESSAGE_LENGTH];
    if (file == NULL) {
        printMessage(ERROR, "Error opening file for writing.\n");
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
    snprintf(message, MESSAGE_LENGTH, "Hash table saved to file: %s\n", filename);
    printMessage(SUCCESS, message);
}


void loadFromFile(Node* hashTable[], const char* filename) {
    FILE* file = fopen(filename, "rb");
    char message[MESSAGE_LENGTH];
    if (file == NULL) {
        
        snprintf(message, MESSAGE_LENGTH, "No previous hash table file '%s' found. Creating a new one.\n", filename);
        printMessage(NOT_FOUND, message);
        file = fopen(filename, "wb"); 
        if (file == NULL) {
            printMessage(ERROR, "Error creating file\n");
            return;
        }
        fclose(file); 

        file = fopen(filename, "rb");
        if (file == NULL) {
            snprintf(message, MESSAGE_LENGTH, "Error: Could not open newly created file '%s' for reading.\n", filename);
            printMessage(ERROR, message);
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
    snprintf(message, MESSAGE_LENGTH, "Hash table loaded from file: %s\n", filename);
    printMessage(SUCCESS, message);
}

