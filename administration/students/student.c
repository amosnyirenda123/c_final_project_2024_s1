#include "student.h"
#include "../Shared/utils.h"
#include "../majors/module.h"
#include "../maps/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>


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
    Node* student_lookup_table[TABLE_SIZE] = {0};
    char student_lookup_path[100], student_full_name[100];
    const char* dir = "data";

    snprintf(student_lookup_path, sizeof(student_lookup_path), "%s/student_lookup.dat", dir);

    printf("Enter student Last Name: ");
    scanf(" %[^\n]", s_details.l_name);
    printf("Enter student First Name: ");
    scanf(" %[^\n]", s_details.f_name);
    printf("Enter student sex (M/F): ");
    scanf(" %c", &s_details.gender);
    printf("Enter Student Date of Birth (YYYY/MM/DD): ");
    scanf("%d %d %d", &s_details.s_date_of_birth.year, &s_details.s_date_of_birth.month, &s_details.s_date_of_birth.day);
    printf("Enter the code of the major (CS/CE/ME/EE): ");
    scanf("%s", s_details.major.major_code);

    // setting module count to zero
    for(int i = 0; i < MAX_SEMESTERS + 1; i++){
        s_details.major.semester[i].module_count = 0;

    }
    // Assign Modules based on Major
    populate_modules_for_student(&s_details, s_details.major.major_code, 1);


    char first_name_cpy[MAX_LENGTH], last_name_cpy[MAX_LENGTH];
    strcpy(first_name_cpy, s_details.f_name);
    strcpy(last_name_cpy, s_details.l_name);
    string_to_lowercase(first_name_cpy);
    string_to_lowercase(last_name_cpy);
    generate_student_email(s_details.institutional_email, first_name_cpy, last_name_cpy);
    sprintf(s_details.code, "%d-%ld", get_current_year(), generate_unique_code());

    // Load and insert into lookup table
    loadFromFile(student_lookup_table, student_lookup_path);
    sprintf(student_full_name,"%s %s", s_details.l_name, s_details.f_name);
    insert(student_lookup_table, s_details.code, student_full_name);
    saveToFile(student_lookup_table, student_lookup_path);

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

void delete_student(FILE* student_file, const char student_code[CODE_LENGTH], const char major_code[CODE_LENGTH]) {
    if (student_file == NULL) {
        printf("\033[1;31m[ERROR] Student file could not be opened.\033[0m\n");
        return;
    }

    const char* dir = "data";
    char tempfile_path[100];
    char students_path[100];

    snprintf(tempfile_path, sizeof(tempfile_path), "%s/temp.dat", dir);
    snprintf(students_path, sizeof(students_path), "%s/student.dat", dir);

    Student* student_to_delete = find_student(student_file, student_code, major_code);
    if (student_to_delete == NULL) {
        printf("\033[1;31m[INFO] No student with code %s found in major %s.\033[0m\n", student_code, major_code);
        return;
    }

    FILE* temp_file = fopen(tempfile_path, "wb");
    if (temp_file == NULL) {
        printf("\033[1;31m[ERROR] Could not open temporary file for writing.\033[0m\n");
        return;
    }

    Student student;
    int found = 0;

    rewind(student_file);
    while (fread(&student, sizeof(Student), 1, student_file) == 1) {
        if (strcmp(student.code, student_to_delete->code) == 0) {
            printf("\033[1;32m[INFO] Student with code %s successfully deleted.\033[0m\n", student_to_delete->code);
            found = 1;
        } else {
            fwrite(&student, sizeof(Student), 1, temp_file);
        }
    }

    fclose(student_file);
    fclose(temp_file);

    if (found) {
        if (remove(students_path) != 0) {
            printf("\033[1;31m[ERROR] Failed to remove the original file.\033[0m\n");
        } else if (rename(tempfile_path, students_path) != 0) {
            printf("\033[1;31m[ERROR] Failed to rename the temporary file.\033[0m\n");
        } else {
            printf("\033[1;32m[INFO] Student record updated successfully.\033[0m\n");
        }
    } else {
        printf("\033[1;31m[INFO] No matching student found to delete.\033[0m\n");
        remove(tempfile_path);
    }

    free(student_to_delete);
}



void update_student_details(FILE *student_file, const char student_code[CODE_LENGTH], const char major_code[CODE_LENGTH]) {
    Student *student;
    Node* student_lookup_table[TABLE_SIZE] = {0};
    char student_lookup_path[100], student_full_name[100];
    const char* dir = "data";

    snprintf(student_lookup_path, sizeof(student_lookup_path), "%s/student_lookup.dat", dir);
    student = find_student(student_file, student_code, major_code);
    char response[5];

    if (student == NULL) {
        printf("\033[1;31m[ERROR] Student not found!\033[0m\n");
        return;
    }

    // Modify last name
    printf("Would you like to modify the student's last name? (y/n): ");
    scanf("%s", response);
    if (tolower(response[0]) == 'y') {
        printf("Enter student Last Name: ");
        scanf("%s", student->l_name);  
    }

    // Modify first name
    printf("Would you like to modify the student's first name? (y/n): ");
    scanf("%s", response);
    if (tolower(response[0]) == 'y') {
        printf("Enter student First Name: ");
        scanf("%s", student->f_name);  
    }

    // Modify institutional email
    printf("Would you like to modify the student's institutional email? (y/n): ");
    scanf("%s", response);
    if (tolower(response[0]) == 'y') {
        char first_name_cpy[MAX_LENGTH], last_name_cpy[MAX_LENGTH];
        strcpy(first_name_cpy, student->f_name);
        strcpy(last_name_cpy, student->l_name);
        string_to_lowercase(first_name_cpy);
        string_to_lowercase(last_name_cpy);
        generate_student_email(student->institutional_email, first_name_cpy, last_name_cpy);  
    }

    // Modify gender
    printf("Would you like to modify the student's sex? (y/n): ");
    scanf("%s", response);
    if (tolower(response[0]) == 'y') {
        printf("Enter student sex (M/F): ");
        scanf(" %c", &student->gender);  
    }

    // Modify date of birth
    printf("Would you like to modify the student's date of birth? (y/n): ");
    scanf("%s", response);
    if (tolower(response[0]) == 'y') {
        printf("Enter Student Date of Birth (YYYY/MM/DD): ");
        scanf("%d %d %d", &student->s_date_of_birth.year, &student->s_date_of_birth.month, &student->s_date_of_birth.day);
    }

    // Modify academic year
    printf("Would you like to modify the student's academic year for a particular semester? (y/n): ");
    scanf("%s", response);
    if (tolower(response[0]) == 'y') {
        int start_year, end_year, semester;
        
        printf("Please enter semester number: ");
        scanf("%d", &semester);

        if (semester < 0 || semester > MAX_SEMESTERS) {
            printf("\033[1;31m[ERROR] Semester out of range.\033[0m\n");
        } else {
            printf("Enter student new Academic Year (start[SPACE]end): ");
            scanf("%d %d", &start_year, &end_year);
            student->major.semester[semester - 1].academic_year.start_year = start_year;
            student->major.semester[semester - 1].academic_year.end_year = end_year;
        }
    }

    // Modify major
    printf("Would you like to modify the student's major? \033[1;31m[WARNING] This operation deletes all the existing data about the major. It is advised that you delete specific entries and not the entire major. (y/n):\033[0m ");
    scanf("%s", response);
    if (tolower(response[0]) == 'y') {
        int semester;
        printf("Enter the code of the major (CS, CE, EE, ME): ");
        scanf("%s", student->major.major_code);  
        printf("Enter student semester number(1-6): ");
        scanf("%d", &semester);
        // Assign Modules based on Major
        populate_modules_for_student(student, student->major.major_code, semester);
    }

    // Modify lookup table
    loadFromFile(student_lookup_table, student_lookup_path);
    sprintf(student_full_name, "%s %s", student->l_name, student->f_name);
    update_hash(student_lookup_table, student->code, student_full_name);
    saveToFile(student_lookup_table, student_lookup_path);

    fseek(student_file, -(long)sizeof(Student), SEEK_CUR); // Moving back
    fwrite(student, sizeof(Student), 1, student_file);
    fclose(student_file);
    printf("\033[1;34m[INFO] Student details updated successfully!.\033[0m\n");
}


void find_student_and_print_details(FILE *student_file, const char code[CODE_LENGTH]){
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
    fclose(student_file);
}

