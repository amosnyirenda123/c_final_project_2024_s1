#include "config.h"
#include "administration/students/student.h"
#include "administration/majors/major.h"
#include "administration/majors/module.h"
#include "administration/maps/map.h"
#include "administration/shared/utils.h"
#include "toast.h"


void to_uppercase(char *str) {
    while (*str) {
        *str = toupper((unsigned char)*str);  
        str++; 
    }
}


void clear_screen() {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls"); 
    #else
        system("clear"); 
    #endif
}

void initialize_paths(Config* config){
    config->dir = "data";

    snprintf(config->modules_path, sizeof(config->modules_path), "%s/modules.dat", config->dir);
    snprintf(config->students_path, sizeof(config->students_path), "%s/student.dat", config->dir);
    snprintf(config->major_path, sizeof(config->major_path), "%s/majors.dat", config->dir);

    // lookup paths
    snprintf(config->student_lookup_path, sizeof(config->student_lookup_path), "%s/student_lookup.dat", config->dir);
    snprintf(config->dpt_lookup_path, sizeof(config->dpt_lookup_path), "%s/dpt_lookup.dat", config->dir);
    snprintf(config->prf_lookup_path, sizeof(config->prf_lookup_path), "%s/prf_lookup.dat", config->dir);
    snprintf(config->major_lookup_path, sizeof(config->major_lookup_path), "%s/major_lookup.dat", config->dir);
    snprintf(config->module_lookup_path, sizeof(config->module_lookup_path), "%s/module_lookup.dat", config->dir);
}

void about_app() {
    clear_screen();
    printf("\n*****************************************************\n");
    printf("**                 \033[1;36mABOUT THE APP\033[0m                  **\n");
    printf("*****************************************************\n");
    printf("\033[1;32mThis is a student management system\033[0m designed to help\n");
    printf("with tracking students, modules, majors, and other\n");
    printf("academic-related data. It includes functionalities\n");
    printf("such as adding students, displaying results, and more.\n");
    
    printf("\n\033[1;33mDeveloped by:\033[0m\n");
    printf("   1. \033[1;35mMAGNE TSAFACK LYDIVINE MERVEILLE\033[0m\n");
    printf("   2. \033[1;35mOUEDRAOGO WENDINKONTE LUTHER ARTHUR\033[0m\n");
    printf("   3. \033[1;35mNYIRENDA AMOS\033[0m\n");

    // Adding open-source information
    printf("\n\033[1;32mThis project is open source!\033[0m\n");
    printf("You can find the source code and contribute to the project at:\n");
    printf("\033[1;36mhttps://github.com/YourUsername/StudentManagementSystem\033[0m\n");
    
    printf("\n\033[1;32mPress Enter to return to the menu...\033[0m\n");
    getchar(); 
    getchar(); 
}

void wait_press_enter(){
    printf("\n\033[1;32mPress Enter to return to the menu...\033[0m\n");
    pause_execution(); 
}

void print_menu() {
    clear_screen();
    printf(YELLOW);
    printf("\n*****************************************************\n");
    printf("**      WELCOME TO OUR STUDENT MANAGEMENT         **\n");
    printf("*****************************************************\n");
    printf("**                MAIN MENU                       **\n");
    printf("*****************************************************\n");
    
    
    printf(RESET);

    // Add Commands Section
    printf("\n\033[1;32m[1-3] Add Commands:\033[0m\n");
    printf("   1. Add New Student\n");
    printf("   2. Add New Module\n");
    printf("   3. Add New Major\n");

    // Display Commands Section
    printf("\n\033[1;34m[4-7] Display Commands:\033[0m\n");
    printf("   4. Display All Students\n");
    printf("   5. Display Students by Major\n");
    printf("   6. Display Modules by Major & Semester\n");
    printf("   7. Display All Majors\n");

    // Search Commands Section
    printf("\n\033[1;35m[8-9] Search Commands:\033[0m\n");
    printf("   8. Search for Student\n");
    printf("   9. Quick Search for Student\n");

    // Print Commands Section
    printf("\n\033[1;36m[10-12] Print Commands:\033[0m\n");
    printf("   10. Print Student Semester Results\n");
    printf("   11. Print Student Yearly Transcript\n");
    printf("   12. Print Student Semester Modules\n");

    // Delete Commands Section
    printf("\n\033[1;31m[13] Delete Command:\033[0m\n");
    printf("   13. Delete Student\n");

    // Other Commands Section
    printf("\n\033[1;33m[14-17] Other Commands:\033[0m\n");
    printf("   14. Update Student Info\n");
    printf("   15. Update Module Info\n");
    printf("   16. Allocate and Modify Student Marks\n");
    printf("   17. Assign Student Semester Modules\n");

    // Miscellaneous
    printf("\n\033[1;37m[18-19] Miscellaneous:\033[0m\n");
    printf("   18. About App\n");
    printf("    0. Exit\n");

    printf(YELLOW"\n*****************************************************\n"RESET);
    printf(YELLOW"Select an option (1-20): "RESET);

}

FILE* open_file(const char* filename, const char* mode){
    FILE *fptr;
    fptr = fopen(filename, mode);
    if (filename == NULL || mode == NULL) {
        printMessage(ERROR, "Filename or mode is NULL.");
        return NULL;
    }
    if(fptr == NULL){
        printMessage(ERROR, "Could not open file in desired mode.");
        return NULL;
    }
    return fptr;
};

void close_file(FILE* fptr) {
    if (fptr != NULL) {
        fclose(fptr);
    } else {
        printMessage(ERROR, "Couldn't close file.");
    }
}


StudentInfo* getStudentDetails(const char *student_lookup_path, const char *major_lookup_path, int ctr) {
    StudentInfo *student = (StudentInfo *)malloc(sizeof(StudentInfo));
    if (!student) {
        perror("Failed to allocate memory for student");
        exit(EXIT_FAILURE);
    }
    

    student->code = NULL;
    student->major = NULL;
    student->semester = -1;

    student->code = (char *)malloc(MAX_CODE_LENGTH * sizeof(char));
    student->major = (char *)malloc(MAX_CODE_LENGTH * sizeof(char));
    if (!student->code || !student->major) {
        perror("Failed to allocate memory for student fields");
        free(student);
        exit(EXIT_FAILURE);
    }

    Node *buffer_table[TABLE_SIZE] = {0};
    clear_screen();

    
    printf("\nEnter student identification number: ");
    scanf("%49s", student->code); 

    loadFromFile(buffer_table, student_lookup_path);
    if (search(buffer_table, student->code) == NULL) {
        printMessage(1, "Student ID not found. Terminating process.");
        pause_execution();
        free(student->code);
        free(student->major);
        free(student);
        return NULL; 
    }

    
    printf("\nEnter student major code: ");
    scanf("%9s", student->major); 

    loadFromFile(buffer_table, major_lookup_path);
    if (search(buffer_table, student->major) == NULL) {
        printMessage(1, "Major does not exist. Terminating process.");
        pause_execution();
        free(student->code);
        free(student->major);
        free(student);
        return NULL; 
    }

    
    if (ctr == 1) {
        printf("\nEnter semester: ");
        scanf("%d", &student->semester);
    } else {
        student->semester = 1;
    }

    return student; 
}


void freeStudentInfo(StudentInfo *student) {
    if (student) {
        free(student->code);
        free(student->major);
        free(student);
    }
}



void switch_option(int option){
    Config config;
    Node* buffer_table[TABLE_SIZE] = {0};
    initialize_paths(&config);
    if (option == 1) {
        clear_screen();
        FILE* student_file = open_file(config.students_path, "ab");
        add_student(student_file);
        close_file(student_file);
        wait_press_enter();
    }
    else if (option == 2) {
        clear_screen();
        FILE* module_file = open_file(config.modules_path, "ab");
        add_module(module_file);
        close_file(module_file);
        wait_press_enter();
    }
    else if (option == 3) {
        clear_screen();
        FILE* majors_file = open_file(config.major_path, "ab");
        add_major(majors_file);
        close_file(majors_file);
        wait_press_enter();
    }
    else if(option == 4){
        clear_screen();
        FILE* students_file = open_file(config.students_path, "rb");
        display_all_students(students_file);
        wait_press_enter();
    }
    else if(option == 5){
        clear_screen();
        char code[MAX_CODE_LENGTH];
        printMessage(INFO, "Enter Major Code: ");
        scanf("%s", code);
        loadFromFile(buffer_table, config.major_lookup_path);
        to_uppercase(code);
        if(search(buffer_table, code ) == NULL){
            printMessage(NOT_FOUND, "Major code does not exist. Terminating Process.....");
            pause_execution();
            return;
        }


        FILE* students_file = open_file(config.students_path, "rb");
        display_students_by_major(students_file, code);
        close_file(students_file);
        wait_press_enter();
    }
    else if(option == 6){
        clear_screen();
        int semester;
        char code[MAX_CODE_LENGTH];
        

        printMessage(INFO, "Enter Major Code: ");
        scanf("%s", code);
        to_uppercase(code);
        loadFromFile(buffer_table, config.major_lookup_path);
        

        if(search(buffer_table, code) == NULL){
            printMessage(NOT_FOUND, "Major code does not exist. Terminating Process.....");
            pause_execution();
            return;
        }else{
            printMessage(INFO, "Enter Semester Number: ");
            scanf("%d", &semester);
        }


        FILE* modules_file = open_file(config.modules_path, "rb");
        print_modules(modules_file, code, semester);
        close_file(modules_file);
        wait_press_enter();
    }
    else if(option == 7){
         clear_screen();
         FILE* majors_file = open_file(config.major_path, "rb");
         print_majors(majors_file);
         close_file(majors_file);
         wait_press_enter();
    }
    else if(option == 8){
        clear_screen();
        int semester;
        char code[MAX_CODE_LENGTH], major[10];
        
        Student* student;

        printMessage(INFO, "Enter student identification number: ");
        scanf("%s", code);
        loadFromFile(buffer_table, config.student_lookup_path);
        if(search(buffer_table, code) == NULL){
            printMessage(NOT_FOUND, "Student ID not found terminating process.........");
            pause_execution();
            return;
        }else{
            printMessage(INFO, "Enter student major: ");
            scanf("%s", major);
            to_uppercase(major);
            loadFromFile(buffer_table, config.major_lookup_path);
            if(search(buffer_table, major) == NULL){
                printMessage(NOT_FOUND, "Major does not exist terminating process.......");
                pause_execution();
                return;
            }
            
        }

        FILE* student_file = open_file(config.students_path, "rb");
        student = find_student(student_file, code, major);

        if(student != NULL){
            print_student_summary(student);
            wait_press_enter();
        }else{
            printMessage(ERROR, "Something went wrong. Terminating Process.....");
            wait_press_enter();
        }
    }
    else if(option == 9){
        clear_screen();
        char student_id[CODE_LENGTH], message[MESSAGE_LENGTH];
        loadFromFile(buffer_table, config.student_lookup_path);
        printMessage(INFO, "Enter student ID: ");
        scanf("%s", student_id);
        char* found = search(buffer_table, student_id);
        if(found == NULL){
            snprintf(message, MESSAGE_LENGTH,"Student with ID %s Not Found.", student_id);
            printMessage(NOT_FOUND, message);
            pause_execution();
        }else{
            snprintf(message, MESSAGE_LENGTH,"Full Name: %s", found);
            printMessage(RES, message);
            wait_press_enter();
        }
    }
    else if(option == 10){
        clear_screen();
        int semester;
        char code[MAX_CODE_LENGTH], major[10];

        printMessage(INFO, "Enter student identification number: ");
        scanf("%s", code);
        loadFromFile(buffer_table, config.student_lookup_path);
        if(search(buffer_table, code) == NULL){
            printMessage(NOT_FOUND, "Student ID not found terminating process.........");
            pause_execution();
            return;
        }else{
            printMessage(INFO, "Enter student major: ");
            scanf("%s", major);
            to_uppercase(major);
            loadFromFile(buffer_table, config.major_lookup_path);
            if(search(buffer_table, major) == NULL){
                printMessage(NOT_FOUND, "Major does not exist terminating process.......");
                pause_execution();
                return;
            }else{
                printMessage(INFO, "Enter semester: ");
                scanf("%d", &semester);
            }
            
        }


        FILE* students_file = open_file(config.students_path, "rb");
        Student* student = find_student(students_file, code, major);
        if(student == NULL){
            printMessage(NOT_FOUND, "No student found.");
            return;
        }else{
            print_student_semester_results(student, semester);
        }
        close_file(students_file);
        wait_press_enter();
    }
    else if(option == 11){
        clear_screen();
        int start_semester;
        char code[MAX_CODE_LENGTH], major[10];

        printMessage(INFO, "Enter student identification number: ");
        scanf("%s", code);
        loadFromFile(buffer_table, config.student_lookup_path);
        if(search(buffer_table, code) == NULL){
            printMessage(NOT_FOUND, "Student ID not found terminating process........");
            pause_execution();
            return;
        }else{
            printMessage(INFO, "Enter student major: ");
            scanf("%s", major);
            to_uppercase(major);
            loadFromFile(buffer_table, config.major_lookup_path);
            if(search(buffer_table, major) == NULL){
                printMessage(NOT_FOUND, "Major does not exist terminating process........");
                pause_execution();
                return;
            }else{
                printMessage(INFO, "Enter start semester: ");
                scanf("%d", &start_semester);
            }
            
        }

        FILE* students_file = open_file(config.students_path, "rb");

        Student* student = find_student(students_file, code, major);
        if(student == NULL){
            printMessage(NOT_FOUND, "No student found.");
            return;
        }else{
            print_student_yearly_results(student, start_semester);
        }

        close_file(students_file);
        wait_press_enter();
    }
    else if(option == 12){
        clear_screen();
        int semester;
        char code[MAX_CODE_LENGTH], major[10];

        printMessage(INFO, "Enter student identification number: ");
        scanf("%s", code);
        loadFromFile(buffer_table, config.student_lookup_path);
        if(search(buffer_table, code) == NULL){
            printMessage(NOT_FOUND, "Student ID not found terminating process......");
            pause_execution();
            return;
        }else{
            printMessage(INFO, "Enter student major: ");
            scanf("%s", major);
            to_uppercase(major);
            loadFromFile(buffer_table, config.major_lookup_path);
            if(search(buffer_table, major) == NULL){
                printMessage(NOT_FOUND, "Major does not exist terminating process........");
                pause_execution();
                return;
            }else{
                printMessage(INFO, "Enter semester: ");
                scanf("%d", &semester);
            }
            
        }
        

        FILE* students_file = open_file(config.students_path, "rb");

        Student* student = find_student(students_file, code, major);

        if(student == NULL){
            printMessage(NOT_FOUND, "No student found.");
            return;
        }else{
            print_modules_for_semester(student, semester);
        }
        wait_press_enter();
    }
    else if(option == 13){
        clear_screen();
        char code[MAX_CODE_LENGTH], major[10];

        char warning_input;

        printMessage(WARNING, "Deleting will permanently erase all related information. This action cannot be undone. Are you sure you want to proceed? (y/n): ");
        scanf(" %c", &warning_input);

        if(warning_input == 'n'){
            return;
        }

        printMessage(INFO, "Enter student identification number: ");
        scanf("%s", code);
        loadFromFile(buffer_table, config.student_lookup_path);
        if(search(buffer_table, code) == NULL){
            printMessage(NOT_FOUND, "Student ID not found terminating process.......");
            pause_execution();
            return;
        }else{
            printMessage(INFO, "Enter student major: ");
            scanf("%s", major);
            to_uppercase(major);
            loadFromFile(buffer_table, config.major_lookup_path);
            if(search(buffer_table, major) == NULL){
                printMessage(NOT_FOUND, "Major does not exist terminating process......");
                pause_execution();
                return;
            }
            
        }



        FILE* students_file = open_file(config.students_path, "rb");
        delete_student(students_file, code, major);
        wait_press_enter();
    }
    else if(option == 14){
        clear_screen();
        char code[MAX_CODE_LENGTH], major[10];
        FILE* students_file = open_file(config.students_path, "r+b");

        printMessage(INFO, "Enter student identification number: ");
        scanf("%s", code);
        loadFromFile(buffer_table, config.student_lookup_path);
        if(search(buffer_table, code) == NULL){
            printMessage(NOT_FOUND, "Student ID not found terminating process.");
            pause_execution();
            return;
        }else{
            printMessage(INFO, "Enter student major: ");
            scanf("%s", major);
            to_uppercase(major);
            loadFromFile(buffer_table, config.major_lookup_path);
            if(search(buffer_table, major) == NULL){
                printMessage(NOT_FOUND, "Major does not exist terminating process.");
                pause_execution();
                return;
            }
        }

        update_student_details(students_file, code, major);
        wait_press_enter();
    }
    else if(option == 15){
        clear_screen();
        char code[MAX_CODE_LENGTH];
        

        printMessage(INFO, "Enter Module code: ");
        scanf("%s", code);
        loadFromFile(buffer_table, config.module_lookup_path);

        if(search(buffer_table, code) == NULL){
            printMessage(NOT_FOUND, "Module code does not exist. Terminating Process.....");
            pause_execution();
            return;
        }

        FILE* modules_file = open_file(config.modules_path, "r+b");
        update_module(modules_file, code);
        fclose(modules_file);
        wait_press_enter();
    }
    else if (option == 16) {
        clear_screen();
        int semester;
        char code[MAX_CODE_LENGTH], major[10];

        printMessage(INFO, "Enter student identification number: ");
        scanf("%s", code);
        loadFromFile(buffer_table, config.student_lookup_path);
        if(search(buffer_table, code) == NULL){
            printMessage(NOT_FOUND, "Student ID not found terminating process.");
            pause_execution();
            return;
        }else{
            printMessage(INFO, "Enter student major: ");
            scanf("%s", major);
            to_uppercase(major);
            loadFromFile(buffer_table, config.major_lookup_path);
            if(search(buffer_table, major) == NULL){
                printMessage(NOT_FOUND, "Major does not exist terminating process.");
                pause_execution();
                return;
            }else{
                printMessage(INFO, "Enter semester: ");
                scanf("%d", &semester);
            }
            
        }

        FILE* students_file = open_file(config.students_path, "r+b");
        allocate_marks_to_student(students_file, code, major, semester);
        close_file(students_file);
        wait_press_enter();
    }

    else if (option == 17) {
        clear_screen();
        int semester;
        char code[MAX_CODE_LENGTH], major[10];

        printMessage(INFO, "Enter student identification number: ");
        scanf("%s", code);
        loadFromFile(buffer_table, config.student_lookup_path);
        if(search(buffer_table, code) == NULL){
            printMessage(NOT_FOUND, "Student ID not found terminating process.");
            pause_execution();
            return;
        }else{
            printMessage(INFO, "Enter student major: ");
            scanf("%s", major);
            to_uppercase(major);
            loadFromFile(buffer_table, config.major_lookup_path);
            if(search(buffer_table, major) == NULL){
                printMessage(NOT_FOUND, "Major does not exist terminating process.");
                pause_execution();
                return;
            }else{
                printMessage(INFO, "Enter semester: ");
                scanf("%d", &semester);
            }
            
        }


        FILE* students_file = open_file(config.students_path, "r+b");
        assign_semester_modules(students_file, code, major, semester);
        close_file(students_file);
        wait_press_enter();
    }
    else if (option == 18) {
        about_app();
    }
    else if(option == 0){
        clear_screen();
        printf(GREEN"\nThank you for using our application! Your session has ended successfully. See you next time!\n"RESET);
    }
    else {
        clear_screen();
        printMessage(ERROR, "Invalid option. ");
    }
}

void start_application(){
    int option;
    do{
        print_menu();
        scanf("%d", &option);
        switch_option(option);
    }while(option != 0);
}

