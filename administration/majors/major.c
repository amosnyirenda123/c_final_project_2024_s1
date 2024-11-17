#include "../students/student.h"
#include "major.h"
#include "../maps/map.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* add_major(FILE* file, Node* lookup_table_major[]){
    Major major;
    char major_lookup_path[100];
    char* rcode = (char*)malloc(sizeof(char));
    const char* dir = "data";

    snprintf(major_lookup_path, sizeof(major_lookup_path), "%s/major_lookup.dat", dir);

  
    printf("Enter major code: ");
    scanf("%s", major.major_code);

    printf("Enter major name: ");
    scanf(" %[^\n]", major.major_name); 

    loadFromFile(lookup_table_major, major_lookup_path);
    insert(lookup_table_major, major.major_code, major.major_name);
    saveToFile(lookup_table_major, major_lookup_path);

    fseek(file, 0, SEEK_END);
    if (fwrite(&major, sizeof(Major), 1, file) != 1) {
        printf("Error writing to file.\n");
        return NULL;
    }

    fclose(file);
   
    strcpy(rcode, major.major_code);
    return rcode;
}



