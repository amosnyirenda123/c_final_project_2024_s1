#include "../students/student.h"
#include "major.h"
#include "../maps/map.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* add_major(FILE* file){
    Major major;
    Node* lookup_table_major[TABLE_SIZE] = {0};
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

void print_majors(FILE* file) {
    if (file == NULL) {
        printf("\033[1;31m[ERROR] File could not be opened.\033[0m\n");
        return;
    }

    Major major;
    while (fread(&major, sizeof(Major), 1, file)) {
        printf("\n\033[1;34m----------------------------------------\033[0m\n"); 
        printf("\033[1;32mMajor Code: \033[0m%s\n", major.major_code);  
        printf("\033[1;32mMajor Name: \033[0m%s\n", major.major_name);  
        printf("\033[1;34m----------------------------------------\033[0m\n"); 
    }
    fclose(file);

}


