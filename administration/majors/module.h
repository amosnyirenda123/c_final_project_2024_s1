#ifndef MODULE_H
#define MODULE_H

#include <stdio.h>
#include <string.h>
#include "../students/student.h"

#define MAX_MODULES_PER_SEMESTER 6
#define MAX_SEMESTERS 6
#define MAX_MODULE_CODE_LENGTH 10
#define MAX_MODULE_NAME_LENGTH 50
#define MAX_LENGTH 50


extern Module GI_modules[MAX_SEMESTERS][MAX_MODULES_PER_SEMESTER];
extern Module CE_modules[MAX_SEMESTERS][MAX_MODULES_PER_SEMESTER];
extern Module EE_modules[MAX_SEMESTERS][MAX_MODULES_PER_SEMESTER];
extern Module ME_modules[MAX_SEMESTERS][MAX_MODULES_PER_SEMESTER];
extern Module ChE_modules[MAX_SEMESTERS][MAX_MODULES_PER_SEMESTER];
extern Module CoE_modules[MAX_SEMESTERS][MAX_MODULES_PER_SEMESTER];

//populate modules for a given student
void populate_modules_for_student(Student *student, const char *major_code);

//display all modules for a student
void print_modules_for_student(Student *student);

#endif
