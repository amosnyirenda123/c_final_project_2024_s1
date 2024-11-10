#ifndef MAJOR_H
#define MAJOR_H

#define MAX_CODE_LENGTH 20
#define MAX_LENGTH 50
#define MAX_MODULE 6
#define MAX_SEM 6

typedef struct Module {
    char module_code[MAX_CODE_LENGTH];
    char module_name[MAX_LENGTH];
    float mark;
} Module;

typedef struct Semester {
    // int semester;  
    Module modules[MAX_MODULE];
    int module_count;
} Semester;

typedef struct Major {
    char major_code[MAX_LENGTH];
    Semester semester[MAX_SEM];
} Major;



#endif