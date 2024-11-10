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
#define MODULE_PASS_MARK 12



extern Module GI_modules[MAX_SEMESTERS][MAX_MODULES_PER_SEMESTER];
extern Module CE_modules[MAX_SEMESTERS][MAX_MODULES_PER_SEMESTER];
extern Module EE_modules[MAX_SEMESTERS][MAX_MODULES_PER_SEMESTER];
extern Module ME_modules[MAX_SEMESTERS][MAX_MODULES_PER_SEMESTER];
extern Module ChE_modules[MAX_SEMESTERS][MAX_MODULES_PER_SEMESTER];
extern Module CoE_modules[MAX_SEMESTERS][MAX_MODULES_PER_SEMESTER];

//populate modules for a given student
float sum_of_marks(Module *modules, int n);
float get_semester_average(Student *student, int semester);
int deduce_year_of_study(int semester);
void print_student_yearly_results(Student *student, int start_semester);
void populate_modules_for_student(Student *student, const char *major_code);
void print_student_semester_results(Student *student, int semester);
void allocate_marks_to_student(FILE *student_file, const char student_code[CODE_LENGTH],const char major_code[CODE_LENGTH], int semester);
//display all modules for a student
void print_modules_for_student(Student *student);
void print_student_transcript(FILE *student_file, const char student_code[CODE_LENGTH], const char major_code[CODE_LENGTH], int start_semester);

#endif
