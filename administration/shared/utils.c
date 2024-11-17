#include "utils.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <direct.h>

int get_current_year() {
    time_t t = time(NULL);  
    struct tm *tm_info = localtime(&t);  
    return tm_info->tm_year + 1900;  
}

long generate_unique_code() {
    srand(time(NULL));
    // Generate an 8-digit number between 10000000 and 99999999
    long code = (rand() % 90000000) + 10000000;

    return code;
}

void string_to_lowercase(char *str) {
    while (*str) {
        *str = tolower((unsigned char)*str);  
        str++;  
    }
}

void string_to_uppercase(char *str) {
    while (*str) {
        *str = toupper((unsigned char)*str);  
        str++; 
    }
}

// char* create_directory(char name_dir[]){
//    #ifdef _WIN32
//         if (_mkdir(name_dir) != 0) {
//             printf("Failed to create directory: %s\n", name_dir);
//         }
//     #else
        
//         if (mkdir(dir, 0777) != 0) { 
//             printf("Failed to create directory: %s\n", dir);
//         }
//     #endif 
// }

