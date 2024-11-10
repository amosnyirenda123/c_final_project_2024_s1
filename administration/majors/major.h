#ifndef MAJOR_H
#define MAJOR_H

#define MAX_CODE_LENGTH 20
#define MAX_LENGTH 50
#define MAX_MODULE 6
#define MAX_SEM 6

typedef struct AcademicYear{
    int start_year;
    int end_year;
}AcademicYear;

typedef struct Module {
    char module_code[MAX_CODE_LENGTH];
    char module_name[MAX_LENGTH];
    char pass_status[MAX_CODE_LENGTH];
    float pass_mark;
    float mark;
} Module;

typedef struct Semester {
    // int semester;  
    Module modules[MAX_MODULE];
    AcademicYear academic_year;
    int module_count;
    float average_mark;
} Semester;

typedef struct Major {
    char major_code[MAX_LENGTH];
    Semester semester[MAX_SEM];
} Major;



#endif