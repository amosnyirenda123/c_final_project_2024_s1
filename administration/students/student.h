#ifndef STUDENT_H
#define STUDENT_H
#include <stdlib.h>
#include <stdio.h>
#include "../majors/major.h"


#define MAX_WORD_LENGTH 80
#define MAX_STUDENTS 1000
#define CODE_LENGTH 20


typedef struct DateOfBirth{
    int month;
    int year;
    int day;
}DateOfBirth;

typedef struct Student {
    char l_name[MAX_WORD_LENGTH];
    char f_name[MAX_WORD_LENGTH];
    DateOfBirth s_date_of_birth;
    char gender;
    char code[CODE_LENGTH];
    Major major;
    char institutional_email[MAX_WORD_LENGTH];
}Student;

void add_student(FILE *student_file);
void find_student(FILE *student_file, const char code[CODE_LENGTH]);
void display_all_students(FILE *student_file);

// Student studentList[MAX_STUDENTS];

#endif