#include "student.h"
#include "../Shared/utils.h"
#include "../majors/module.h"
#include "../maps/map.h"
#include "../../toast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#ifdef _WIN32
#include <windows.h>
#define sleep(x) Sleep(1000 * (x)) 
#else
#include <unistd.h>
#endif


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
    char message[MAX_WORD_LENGTH];
    char student_major_code[CODE_LENGTH];
    const char* dir = "data";

    snprintf(student_lookup_path, sizeof(student_lookup_path), "%s/student_lookup.dat", dir);

    printMessage(INFO, "Enter student Last Name: ");
    scanf(" %[^\n]", s_details.l_name);
    printMessage(INFO, "Enter student First Name: ");
    scanf(" %[^\n]", s_details.f_name);
    printMessage(INFO, "Enter student sex (M/F): ");
    scanf(" %c", &s_details.gender);
    printMessage(INFO, "Enter Student Date of Birth (YYYY MM DD): ");
    scanf("%d %d %d", &s_details.s_date_of_birth.year, &s_details.s_date_of_birth.month, &s_details.s_date_of_birth.day);
    printMessage(INFO, "Enter the code of the major (CS/CE/ME/EE): ");
    scanf("%s", student_major_code);
    string_to_uppercase(student_major_code);
    strncpy(s_details.major.major_code, student_major_code, CODE_LENGTH);
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
    snprintf(message, MESSAGE_LENGTH , "Student added successfully with email %s and code %s.\n", s_details.institutional_email, s_details.code);
    printf("\n");
    printMessage(RES, message);
}

Student* find_student(FILE *student_file, const char student_code[STUDENT_CODE_LENGTH], const char major_code[MAJOR_CODE_LENGTH]){
    Student *student = malloc(sizeof(Student));
    if (student == NULL) {
        printMessage(ERROR, "Failed to allocate memory for student\n");
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

void delete_student(FILE* student_file, const char student_code[STUDENT_CODE_LENGTH], const char major_code[MAJOR_CODE_LENGTH]) {
    if (student_file == NULL) {
        printMessage(ERROR, "Student file could not be opened.\n");
        return;
    }

    
    const char* dir = "data";
    char tempfile_path[100];
    char students_path[100];
    char student_lookup[100];
    Node* student_buffer[TABLE_SIZE] = {0};
    char message[MESSAGE_LENGTH];

    snprintf(tempfile_path, sizeof(tempfile_path), "%s/temp.dat", dir);
    snprintf(students_path, sizeof(students_path), "%s/student.dat", dir);
    snprintf(student_lookup, sizeof(student_lookup), "%s/student_lookup.dat", dir);

    Student* student_to_delete = find_student(student_file, student_code, major_code);
    if (student_to_delete == NULL) {
        snprintf(message, MESSAGE_LENGTH, "No student with code %s found in major %s.\n", student_code, major_code);
        printMessage(NOT_FOUND, message);
        return;
    }

    FILE* temp_file = fopen(tempfile_path, "wb");
    if (temp_file == NULL) {
        printMessage(ERROR, "Could not open temporary file for writing.\n");
        return;
    }

    Student student;
    int found = 0;

    rewind(student_file);
    while (fread(&student, sizeof(Student), 1, student_file) == 1) {
        if (strcmp(student.code, student_to_delete->code) == 0) {
            loadFromFile(student_buffer, student_lookup);
            delete(student_buffer, student_to_delete->code);
            saveToFile(student_buffer, student_lookup);
            snprintf(message, MESSAGE_LENGTH, "Student with code %s successfully deleted.\n", student_to_delete->code);
            printMessage(SUCCESS, message);
            found = 1;
        } else {
            fwrite(&student, sizeof(Student), 1, temp_file);
        }
    }

    fclose(student_file);
    fclose(temp_file);
    sleep(5);
    
    if (found) {
        if (remove(students_path) != 0) {
            printMessage(ERROR, "Failed to remove original file.\n");
            safe_remove(students_path);
        } else if (rename(tempfile_path, students_path) != 0) {
            printMessage(ERROR, "Failed to rename the temporary file.\n");
        } else {
            printMessage(SUCCESS, "Process terminated successfully.\n");
        }
    } else {
        printMessage(NOT_FOUND, "No matching student found to delete.\n");
        remove(tempfile_path);
    }

    free(student_to_delete);
}



void update_student_details(FILE *student_file, const char student_code[STUDENT_CODE_LENGTH], const char major_code[MAJOR_CODE_LENGTH]) {
    Student *student;
    Node* student_lookup_table[TABLE_SIZE] = {0};
    char student_lookup_path[100], student_full_name[100];
    const char* dir = "data";

    snprintf(student_lookup_path, sizeof(student_lookup_path), "%s/student_lookup.dat", dir);
    student = find_student(student_file, student_code, major_code);
    char response[5];

    if (student == NULL) {
        printMessage(NOT_FOUND, "Student not found!");
        return;
    }

    // Modify last name
    printMessage(INFO,"Would you like to modify the student's last name? (y/n):");
    scanf("%s", response);
    if (tolower(response[0]) == 'y') {
        printMessage(INFO, "Enter student Last Name: ");
        scanf("%s", student->l_name);  
    }

    // Modify first name
    printMessage(INFO, "Would you like to modify the student's first name? (y/n):");
    scanf("%s", response);
    if (tolower(response[0]) == 'y') {
        printMessage(INFO, "Enter student First Name: ");
        scanf("%s", student->f_name);  
    }

    // Modify institutional email
    printMessage(INFO, "Would you like to modify the student's institutional email? (y/n):");
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
    printMessage(INFO, "Would you like to modify the student's sex? (y/n):");
    scanf("%s", response);
    if (tolower(response[0]) == 'y') {
        printMessage(INFO, "Enter student sex (M/F) ");
        scanf(" %c", &student->gender);  
    }

    // Modify date of birth
    printMessage(INFO, "Would you like to modify the student's date of birth? (y/n):");
    scanf("%s", response);
    if (tolower(response[0]) == 'y') {
        printMessage(INFO, "Enter student date of birth (YYYY MM DD): ");
        scanf("%d %d %d", &student->s_date_of_birth.year, &student->s_date_of_birth.month, &student->s_date_of_birth.day);
    }

    // Modify academic year
    printMessage(INFO, "Would you like to modify the student's academic year for a particular semester? (y/n):");
    scanf("%s", response);
    if (tolower(response[0]) == 'y') {
        int start_year, end_year, semester;
        
        printMessage(INFO, "Please enter semester number: ");
        scanf("%d", &semester);

        if (semester < 0 || semester > MAX_SEMESTERS) {
            printMessage(ERROR, "Semester out of range.");
        } else {
            printMessage(INFO, "Enter student new Academic Year (start[SPACE]end): ");
            scanf("%d %d", &start_year, &end_year);
            student->major.semester[semester - 1].academic_year.start_year = start_year;
            student->major.semester[semester - 1].academic_year.end_year = end_year;
        }
    }

    // Modify major
    printMessage(INFO, "Would you like to modify the student's major?");
    printMessage(WARNING, "This operation deletes all the existing data about the major. It is advised that you delete specific entries and not the entire major. (y/n):");
    scanf("%s", response);
    if (tolower(response[0]) == 'y') {
        int semester;
        printMessage(INFO, "Enter the code of the major (CS, CE, EE, ME): ");
        scanf("%s", student->major.major_code);
        printMessage(INFO, "Enter student semester number(1-6):  ");  
        scanf("%d", &semester);
        // Assign Modules based on Major
        populate_modules_for_student(student, student->major.major_code, semester);
    }

    // Modify lookup table
    loadFromFile(student_lookup_table, student_lookup_path);
    sprintf(student_full_name, "%s %s", student->l_name, student->f_name);
    update_hash(student_lookup_table, student->code, student_full_name);
    saveToFile(student_lookup_table, student_lookup_path);

    fseek(student_file, -(long)sizeof(Student), SEEK_CUR); 
    fwrite(student, sizeof(Student), 1, student_file);
    fclose(student_file);

    printMessage(SUCCESS, "Student details updated successfully!");
}


void find_student_and_print_details(FILE *student_file, const char code[CODE_LENGTH]){
    Student student;
    int found = 0;
    fseek(student_file, 0, SEEK_SET);

    while (fread(&student, sizeof(Student), 1, student_file) == 1) {
        if (strcmp(student.code, code) == 0) {
            
            printMessage(SUCCESS, "Found the following student.");
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


void display_students_by_major(FILE *student_file, const char major_code[MAJOR_CODE_LENGTH])
{
    Student student;
    fseek(student_file, 0, SEEK_SET);
    int count = 0;

    // printf("List of Students\n");
    printMessage(INFO, "List of Students\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%s|\t%-15s | %-15s | %-15s | %-20s | %-30s\n", "#", "Last Name", "First Name", "Major", "Code", "Email");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");

    while (fread(&student, sizeof(Student), 1, student_file) == 1) {
        if(strcmp(student.major.major_code, major_code) == 0){
            printf("%d|\t%-15s | %-15s | %-15s | %-20s | %-30s\n", count + 1,
            student.l_name, student.f_name, student.major.major_code, student.code, student.institutional_email);
            count++;
        }
        
    }

    if(count == 0){
        printMessage(RES, "No students in requested major.");
    }
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    fclose(student_file);
}

void display_all_students(FILE* student_file){
    Student student;
    fseek(student_file, 0, SEEK_SET);
    int count = 0;

    printMessage(INFO, "List of Students\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("%s|\t%-15s | %-15s | %-15s | %-20s | %-30s\n", "#", "Last Name", "First Name", "Major", "Code", "Email");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");

    while (fread(&student, sizeof(Student), 1, student_file) == 1) {
        printf("%d|\t%-15s | %-15s | %-15s | %-20s | %-30s\n", count + 1,
        student.l_name, student.f_name, student.major.major_code, student.code, student.institutional_email);
        count++;
    }

    if(count == 0){
        printMessage(NOT_FOUND, "No students found.");
    }
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    fclose(student_file);
}

int compute_student_rank(FILE *sfp, Student *current_student, int semester_index){
    Student *temp_student = malloc(sizeof(Student));
    int rank = 1;

    rewind(sfp); 
    while (fread(temp_student, sizeof(Student), 1, sfp) == 1) {
        if (strcmp(temp_student->major.major_code, current_student->major.major_code) == 0 &&
            strcmp(temp_student->code, current_student->code) != 0 && temp_student->major.semester[semester_index].academic_year.start_year == current_student->major.semester[semester_index].academic_year.start_year && temp_student->major.semester[semester_index].academic_year.end_year == current_student->major.semester[semester_index].academic_year.end_year) {
            float avg_other = sum_of_marks(temp_student->major.semester[semester_index].modules,
                                            temp_student->major.semester[semester_index].module_count) /
                               temp_student->major.semester[semester_index].module_count;
            if (avg_other > current_student->major.semester[semester_index].average_mark) {
                rank++;
            }
        }
    }

    free(temp_student);
    return rank;
}

int compute_student_rank_module(FILE *sfp, Student *current_student, int semester,int module_index){
    Student *temp_student = malloc(sizeof(Student));
    int rank = 1;

    rewind(sfp); 
    while (fread(temp_student, sizeof(Student), 1, sfp) == 1) {
        if (strcmp(temp_student->major.major_code, current_student->major.major_code) == 0 &&
            strcmp(temp_student->code, current_student->code) != 0 && temp_student->major.semester[semester].academic_year.start_year == current_student->major.semester[semester].academic_year.start_year && temp_student->major.semester[semester].academic_year.end_year == current_student->major.semester[semester].academic_year.end_year) {
            if (temp_student->major.semester[semester].modules[module_index].mark > current_student->major.semester[semester].modules[module_index].mark) {
                rank++;
            }
        }
    }

    free(temp_student);
    return rank;
}


void print_student_summary(Student *student) {
    Node* lookup_table_major[TABLE_SIZE] = {0};
    char major_lookup_path[100], student_file_path[100];
    FILE *sfp;
    int student_rank;
    const char* dir = "data";
    snprintf(major_lookup_path, sizeof(major_lookup_path), "%s/major_lookup.dat", dir);
    snprintf(student_file_path, sizeof(student_file_path), "%s/student.dat", dir);
    loadFromFile(lookup_table_major, major_lookup_path);
    printf(BLUE"----------------------------------------------------------------------------------------\n");
    printf("                        Student Summary\n");
    printf("----------------------------------------------------------------------------------------\n"RESET);
    printf(YELLOW"Full Name:\t\t%s %s\n", student->f_name, student->l_name);
    printf("Date of Birth:\t\t%02d-%02d-%d\n", student->s_date_of_birth.day,
           student->s_date_of_birth.month, student->s_date_of_birth.year);
    printf("Gender:\t\t\t%c\n", student->gender);
    printf("Student Code:\t\t%s\n", student->code);
    printf("Institutional Email:\t%s\n", student->institutional_email);
    if(search(lookup_table_major, student->major.major_code) != NULL){
        printf("Major:\t\t\t%s (%s)\n"RESET, search(lookup_table_major, student->major.major_code), student->major.major_code);
    }else{
        printf("Major:\t\t\t%s (%s)\n"RESET, student->major.major_name, student->major.major_code);
    }
    
    sfp = fopen(student_file_path, "rb");
    if(sfp == NULL){
        student_rank = -1;
        return;
    }
    

    printf(BLUE"----------------------------------------------------------------------------------------\n"RESET);
    printf(BLUE"%-10s | %-10s | %-10s | %-18s | %-20s \n"RESET, "SEMESTER", "N_MOD" ,"AVERAGE", "RANK", "ACADEMIC YEAR");
    printf(BLUE"----------------------------------------------------------------------------------------\n"RESET);

    for (int i = 0; i < MAX_SEM; i++) {
        Semester *sem = &student->major.semester[i];
        if (sem->module_count > 0) {
            sem->average_mark = sum_of_marks(sem->modules, sem->module_count) / sem->module_count;
        }
        student_rank = compute_student_rank(sfp, student, i);
        if (sem->module_count > 0) {
            printf("%-10d | %-10d | %-10.2f | %-18d | %d / %d \n", i + 1, sem->module_count, sem->average_mark, student_rank, sem->academic_year.start_year, sem->academic_year.end_year);
        }
    }

    printf("----------------------------------------------------------------------------------------\n");
    fclose(sfp);
}