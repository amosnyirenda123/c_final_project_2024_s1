#include "config.h"
#include "administration/students/student.h"
#include "administration/majors/major.h"
#include "administration/majors/module.h"
#include "administration/maps/map.h"




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
    getchar(); 
    getchar(); 
}

void print_menu() {
    clear_screen();
    printf("\n*****************************************************\n");
    printf("**            WELCOME TO STUDENT MANAGEMENT       **\n");
    printf("*****************************************************\n");
    printf("**                MAIN MENU                       **\n");
    printf("*****************************************************\n");

    // Add Commands Section
    printf("\n\033[1;32m[1-3] Add Commands:\033[0m\n");
    printf("   1. Add New Student\n");
    printf("   2. Add New Module\n");
    printf("   3. Add New Major\n");

    // Display Commands Section
    printf("\n\033[1;34m[4-7] Display Commands:\033[0m\n");
    printf("   4. Display All Students\n");
    printf("   5. Display Students by Major\n");
    printf("   6. Display All Modules\n");
    printf("   7. Display All Majors\n");

    // Search Commands Section
    printf("\n\033[1;35m[8-9] Search Commands:\033[0m\n");
    printf("   8. Search for Student\n");
    printf("   9. Quick Search for Student\n");

    // Print Commands Section
    printf("\n\033[1;36m[10-12] Print Commands:\033[0m\n");
    printf("   10. Print Semester Results\n");
    printf("   11. Print Yearly Transcript\n");
    printf("   12. Print Semester Modules\n");

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

    printf("\n*****************************************************\n");
    printf("Select an option (1-20): ");

}

FILE* open_file(const char* filename, const char* mode){
    FILE *fptr;
    fptr = fopen(filename, mode);
    if (filename == NULL || mode == NULL) {
        printf("\n\033[1;31m[ERROR] Filename or mode is NULL.\033[0m\n");
        return NULL;
    }
    if(fptr == NULL){
        printf("\n\033[1;31m[ERROR] Could not open file in desired mode\033[0m\n");
        return NULL;
    }
    return fptr;
};

void close_file(FILE* fptr) {
    if (fptr != NULL) {
        fclose(fptr);
        printf("\n\033[1;32m[INFO] File closed successfully.\033[0m\n");
    } else {
        printf("\n\033[1;31m[ERROR] Invalid file pointer.\033[0m\n");
    }
}




void switch_option(int option){
    Config config;
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
        close_file(students_file);
        wait_press_enter();
    }
    else if(option == 6){
        clear_screen();
        FILE* modules_file = open_file(config.modules_path, "rb");
        print_modules(modules_file);
        close_file(modules_file);
        wait_press_enter();
    }
    else if(option == 5){
        clear_screen();
        // TODO: add implementation
        wait_press_enter();
    }
    else if(option == 7){
         clear_screen();
         FILE* majors_file = open_file(config.major_path, "rb");
         print_majors(majors_file);
         close_file(majors_file);
         wait_press_enter();
    }
    else if(option == 10){
        clear_screen();
        int semester;
        char code[MAX_CODE_LENGTH], major[10];
        FILE* students_file = open_file(config.students_path, "rb");
        printf("\nEnter student identification number: ");
        scanf("%s", code);
        printf("\nEnter student major: ");
        scanf("%s", major);
        printf("\nEnter semester: ");
        scanf("%d", &semester);
        Student* student = find_student(students_file, code, major);
        if(student == NULL){
            printf("\033[1;31m[ERROR] No student found.\033[0m\n");
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

        printf("\nEnter student identification number: ");
        scanf("%s", code);
        printf("\nEnter student major: ");
        scanf("%s", major);
        printf("\nEnter start semester: ");
        scanf("%d", &start_semester);

        FILE* students_file = open_file(config.students_path, "rb");

        Student* student = find_student(students_file, code, major);
        if(student == NULL){
            printf("\033[1;31m[ERROR] No student found.\033[0m\n");
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

        printf("\nEnter student identification number: ");
        scanf("%s", code);
        printf("\nEnter student major: ");
        scanf("%s", major);
        printf("\nEnter semester: ");
        scanf("%d", &semester);

        FILE* students_file = open_file(config.students_path, "rb");

        Student* student = find_student(students_file, code, major);

        if(student == NULL){
            printf("\033[1;31m[ERROR] No student found.\033[0m\n");
            return;
        }else{
            print_modules_for_semester(student, semester);
        }
        wait_press_enter();
    }
    else if(option == 13){
        clear_screen();
        char code[MAX_CODE_LENGTH], major[10];

        printf("\nEnter student identification number: ");
        scanf("%s", code);
        printf("\nEnter student major code: ");
        scanf("%s", major);
        FILE* students_file = open_file(config.students_path, "rb");
        delete_student(students_file, code, major);
        wait_press_enter();
    }
    else if(option == 14){
        clear_screen();
        char code[MAX_CODE_LENGTH], major[10];
        FILE* students_file = open_file(config.students_path, "r+b");

        printf("\nEnter student identification number: ");
        scanf("%s", code);
        printf("\nEnter student major: ");
        scanf("%s", major);
        update_student_details(students_file, code, major);
        wait_press_enter();
    }
    else if(option == 15){
        clear_screen();
        char code[MAX_CODE_LENGTH];
        FILE* modules_file = open_file(config.modules_path, "r+b");

        printf("\nEnter Module Code: ");
        scanf("%s", code);
        update_module(modules_file, code);
        fclose(modules_file);
        wait_press_enter();
    }
    else if (option == 16) {
        clear_screen();
        int semester;
        char code[MAX_CODE_LENGTH], major[10];

        printf("\nEnter student identification number: ");
        scanf("%s", code);
        printf("\nEnter student major: ");
        scanf("%s", major);
        printf("\nEnter semester: ");
        scanf("%d", &semester);

        FILE* students_file = open_file(config.students_path, "r+b");
        allocate_marks_to_student(students_file, code, major, semester);
        close_file(students_file);
        wait_press_enter();
    }

    else if (option == 17) {
        clear_screen();
        int semester;
        char code[MAX_CODE_LENGTH], major[10];

        printf("\nEnter student identification number: ");
        scanf("%s", code);
        printf("\nEnter student major: ");
        scanf("%s", major);
        printf("\nEnter semester: ");
        scanf("%d", &semester);

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
        printf("\033[1;32m[INFO] You are exiting the application. Goodbye!\033[0m\n");
    }
    else {
        clear_screen();
        printf("Invalid option! Please try again.\n");
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

