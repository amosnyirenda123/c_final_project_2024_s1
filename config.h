#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include "administration/students/student.h"
#include "administration/majors/major.h"
#include "administration/majors/module.h"
#include "administration/maps/map.h"
#include <ctype.h>

#define PATH_LENGTH 100


typedef struct {
    char modules_path[PATH_LENGTH];
    char students_path[PATH_LENGTH];
    char major_path[PATH_LENGTH];
    char student_lookup_path[PATH_LENGTH];
    char module_lookup_path[PATH_LENGTH];
    char prf_lookup_path[PATH_LENGTH];
    char dpt_lookup_path[PATH_LENGTH];
    char major_lookup_path[PATH_LENGTH];
    const char* dir;
} Config;

typedef struct {
    char *code;
    char *major;
    int semester;
} StudentInfo;


StudentInfo* getStudentDetails(const char *student_lookup_path, const char *major_lookup_path, int ctr);
void freeStudentInfo(StudentInfo *student);

void print_menu();
void about_app();
void start_application();
void switch_option(int option);
FILE* open_file(const char* filename, const char* mode);
void close_file(FILE* fptr);
void initialize_paths(Config* config);
void wait_press_enter();
void to_uppercase(char *str);

#endif