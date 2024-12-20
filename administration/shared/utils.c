#include "utils.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <direct.h>
#include "../../toast.h"

#ifdef _WIN32
#include <windows.h>
#define sleep(x) Sleep(1000 * (x)) 
#else
#include <unistd.h>
#endif

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

void pause_execution(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
    getchar();
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

void delay_operation(){
    for(int i = 0; i < 20000; i++){
    }
}
void safe_remove(const char* path) {
    int retries = 0;
    while (retries < MAX_RETRIES) {
        if (remove(path) == 0) {
            printMessage(SUCCESS, "Delete Successful");
            return; // Success
        }
        retries++;
        printMessage(RES, "Retrying with safe delete...\n");
        sleep(5);
    }
    printMessage(ERROR, "Failed to remove file after multiple attempts.\n");
}




