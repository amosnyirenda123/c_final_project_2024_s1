#ifndef STUDENT_H
#define STUDENT_H
#include <stdlib.h>
#include <stdio.h>
#include "../majors/major.h"


#define MAX_WORD_LENGTH 80
#define MAX_STUDENTS 1000
#define CODE_LENGTH 20
#define STUDENT_CODE_LENGTH 14
#define MAJOR_CODE_LENGTH 10
#define MAX_DURATION 3


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
void find_student_and_print_details(FILE *student_file, const char code[CODE_LENGTH]);
Student* find_student(FILE *student_file, const char student_code[STUDENT_CODE_LENGTH], const char major_code[MAJOR_CODE_LENGTH]);
void update_student_details(FILE *student_file, const char student_code[STUDENT_CODE_LENGTH], const char major_code[MAJOR_CODE_LENGTH]);
void display_all_students(FILE *student_file);
void delete_student(FILE* student_file, const char student_code[STUDENT_CODE_LENGTH], const char major_code[MAJOR_CODE_LENGTH]);

// Student studentList[MAX_STUDENTS];

#endif