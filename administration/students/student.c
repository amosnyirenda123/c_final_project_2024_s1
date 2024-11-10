#include "student.h"
#include "../Shared/utils.h"
#include "../majors/module.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


static void generate_student_email(char *email, const char f_name[MAX_LENGTH], const char l_name[MAX_LENGTH])
{
    strcpy(email, f_name);
    strcat(email, ".");
    strcat(email, l_name);
    strcat(email, "@etu.uae.ac.ma");
}


void add_student(FILE *student_file)
{
    Student s_details;
    printf("Enter student Last Name: ");
    scanf("%s", s_details.l_name);
    printf("Enter student First Name: ");
    scanf("%s", s_details.f_name);
    printf("Enter student sex (M/F): ");
    scanf(" %c", &s_details.gender);
    printf("Enter Student Date of Birth (YYYY/MM/DD): ");
    scanf("%d %d %d", &s_details.s_date_of_birth.year, &s_details.s_date_of_birth.month, &s_details.s_date_of_birth.day);
    printf("Enter the code of the major (GI/GSTR/GCSE/GM/SCM/2AP1/2AP2): ");
    scanf("%s", s_details.major.major_code);

    // Assign Modules based on Major
    populate_modules_for_student(&s_details, s_details.major.major_code);


    char first_name_cpy[MAX_LENGTH], last_name_cpy[MAX_LENGTH];
    strcpy(first_name_cpy, s_details.f_name);
    strcpy(last_name_cpy, s_details.l_name);
    string_to_lowercase(first_name_cpy);
    string_to_lowercase(last_name_cpy);
    generate_student_email(s_details.institutional_email, first_name_cpy, last_name_cpy);
    sprintf(s_details.code, "%d-%ld", get_current_year(), generate_unique_code());

    fseek(student_file, 0, SEEK_END); 
    fwrite(&s_details, sizeof(Student), 1, student_file);
    printf("Student added successfully with email %s and code %s!\n", s_details.institutional_email, s_details.code);
}

Student* find_student(FILE *student_file, const char student_code[CODE_LENGTH], const char major_code[CODE_LENGTH]){
    Student *student = malloc(sizeof(Student));
    if (student == NULL) {
        perror("Failed to allocate memory for student\n");
        return NULL;
    }
    fseek(student_file, 0, SEEK_SET);

     while (fread(student, sizeof(Student), 1, student_file) == 1){
        if (strcmp(student->code, student_code) == 0 && strcmp(student->major.major_code, major_code) == 0) {
            return student;
        }
     }
     free(student);
     return NULL;
}

void find_student_and_print_details(FILE *student_file, const char code[CODE_LENGTH])
{
    Student student;
    int found = 0;
    fseek(student_file, 0, SEEK_SET);

    while (fread(&student, sizeof(Student), 1, student_file) == 1) {
        if (strcmp(student.code, code) == 0) {
            printf("Found the following student.\n");
            printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("%-15s | %-15s | %-15s | %-20s | %-30s\n", "Last Name", "First Name", "Major","Code", "Email");
            printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");

            printf("%-15s | %-15s | %-15s | %-20s | %-30s\n",
               student.l_name, student.f_name, student.major,student.code, student.institutional_email);
            print_modules_for_student(&student);

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with code %s not found!\n", code);
    }
}


void display_all_students(FILE *student_file)
{
    Student student;
    fseek(student_file, 0, SEEK_SET);
    int count = 1;

    printf("List of Students\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%s|\t%-15s | %-15s | %-15s | %-20s | %-30s\n", "#", "Last Name", "First Name", "Major", "Code", "Email");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");

    while (fread(&student, sizeof(Student), 1, student_file) == 1) {
        printf("%d|\t%-15s | %-15s | %-15s | %-20s | %-30s\n", count,
            student.l_name, student.f_name, student.major.major_code, student.code, student.institutional_email);
        count++;
    }

    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
}

