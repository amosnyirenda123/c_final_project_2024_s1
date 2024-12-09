#include "module.h"
#include "../../toast.h"
#include "../maps/map.h"
#include "../students/student.h"
#include <ctype.h>
#include "../shared/utils.h"


const char* get_grade(float marks) {
    if (marks >= 16 && marks <= 20) {
        return "A+";
    } else if (marks >= 14 && marks < 16) {
        return "A";
    } else if (marks >= 12 && marks < 14) {
        return "B";
    } else if (marks >= 10 && marks < 12) {
        return "C";
    } else {
        return "F";
    }
}

float sum_of_marks(Module *modules, int n){
    if(n <= 0){
        return 0.0f;
    }
    return sum_of_marks(modules, n - 1) + modules[n - 1].mark;
}

int deduce_year_of_study(int semester){
   switch (semester) {
        case 1:
        case 2:
            return 1;
        case 3:
        case 4:
            return 2;
        case 5:
        case 6:
            return 3;
        default:
            return 1;  
    }
}

float get_semester_average(Student *student, int semester){
    if(semester > 0 && semester < 7){
        float semester_average = student->major.semester[semester - 1].average_mark;
        return semester_average;
    }
    return 0.0f;
}

void print_student_yearly_results(Student *student, int start_semester){

    if(start_semester == 1 || start_semester == 3 || start_semester == 5){
        printf(BLUE"********************************************************************************************************\n"RESET);
        printf(YELLOW"\t\t\t\t%d YEAR STATEMENT OF RESULTS (TRANSCRIPT)\n"RESET, deduce_year_of_study(start_semester));
        printf(BLUE"--------------------------------------------------------------------------------------------------------\n"RESET);
        print_student_semester_results(student, start_semester);
        print_student_semester_results(student, start_semester + 1);
        
        float s1_average = get_semester_average(student, start_semester);
        float s2_average = get_semester_average(student, start_semester + 1);
        float year_average = (s1_average + s2_average) / 2;
        printf(YELLOW"\t\t\t\t\tYEAR AVERAGE: %.2f(%s)\n"RESET, year_average, get_grade(year_average));
        printf(BLUE"********************************************************************************************************\n"RESET);
    }else{
        printMessage(ERROR, "Start semester should be one of these values [1,3,5]");
    }
    
}

void print_student_semester_results(Student *student, int semester){
        if(semester > 0 && semester <= MAX_SEMESTERS){
            Semester *current_semester = &student->major.semester[semester - 1];
            int start_year = current_semester->academic_year.start_year;
            int end_year = current_semester->academic_year.end_year;
        int year_of_study = deduce_year_of_study(semester);

        int student_rank_module, student_rank_semester;
        const char* dir = "data";
        char student_file_path[100];
        FILE *sfp;
        snprintf(student_file_path, sizeof(student_file_path), "%s/student.dat", dir);

        printf("\n");
        printf(YELLOW"\t\t\t\t\t  SEMESTER %d (%d/%d)\n"RESET, semester, start_year,end_year);
        printf(YELLOW"\t\tFULL NAME: %s %s   MAJOR: %s(%d)   STD CODE: %s\n"RESET, student->l_name, student->f_name, student->major.major_code,year_of_study, student->code);
        printf(BLUE"--------------------------------------------------------------------------------------------------------\n"RESET);
        printf(BLUE"%-50s | %-10s | %-10s | %-18s | %-8s\n"RESET, "MODULE", "CODE", "MARK", "STATUS", "RANK");
        printf(BLUE"--------------------------------------------------------------------------------------------------------\n"RESET);
       
        sfp = fopen(student_file_path, "rb");
        if(sfp == NULL){
            student_rank_module = -1;
        }
        
        for (int i = 0; i < current_semester->module_count; i++) {
            student_rank_module = compute_student_rank_module(sfp, student, semester - 1, i);
            printf("%-50s | %-10s | %-10.2f | %-18s | %-8d\n", current_semester->modules[i].module_name, current_semester->modules[i].module_code, current_semester->modules[i].mark, current_semester->modules[i].pass_status, student_rank_module);
        }
        current_semester->average_mark = sum_of_marks(current_semester->modules, current_semester->module_count) / current_semester->module_count;;
        char grade[10];
        student_rank_semester = compute_student_rank(sfp, student, semester - 1);
        strcpy(grade, get_grade(current_semester->average_mark));
        printf(BLUE"--------------------------------------------------------------------------------------------------------\n"RESET);
        printf(YELLOW"%-50s | %-10s | %.2f(%s)  | RANK: %d\n", "################################################", "AVERAGE", current_semester->average_mark,grade, student_rank_semester);
        printf(BLUE"--------------------------------------------------------------------------------------------------------\n"RESET);
        }

}


void add_module(FILE* file) {
    Module module;
    Node* lookup_table_module[TABLE_SIZE] = {0};
    Node* lookup_table_prf[TABLE_SIZE] = {0};
    Node* lookup_table_dpt[TABLE_SIZE] = {0};
    Node* lookup_table_major[TABLE_SIZE] = {0};
    int sem_temp;
    char opt;
    const char* dir = "data";
    char code[MAX_CODE_LENGTH];
    FILE* majors;

    char module_lookup_path[100], pfr_lookup_path[100], dpt_lookup_path[100], major_lookup_path[100], char_majors_path[100];

    // Generating paths 
    snprintf(module_lookup_path, sizeof(module_lookup_path), "%s/module_lookup.dat", dir);
    snprintf(pfr_lookup_path, sizeof(pfr_lookup_path), "%s/pfr_lookup.dat", dir);
    snprintf(dpt_lookup_path, sizeof(dpt_lookup_path), "%s/dpt_lookup.dat", dir);
    snprintf(major_lookup_path, sizeof(major_lookup_path), "%s/major_lookup.dat", dir);
    
   
    snprintf(char_majors_path, sizeof(char_majors_path), "%s/majors.dat", dir);

    majors = fopen(char_majors_path, "ab+");

    printMessage(INFO, "Enter module code: ");
    scanf("%s", module.module_code);

    printMessage(INFO, "Enter module name: ");
    scanf(" %[^\n]", module.module_name); 

    printMessage(INFO, "Enter professor code: ");
    scanf("%s", module.prof_code);

    printMessage(INFO, "Enter professor name: ");
    scanf(" %[^\n]", module.prof_name);

    printMessage(INFO, "Enter department code: ");
    scanf("%s", module.dept_code);

    printMessage(INFO, "Enter department name: ");
    scanf(" %[^\n]", module.dept_name);

    printMessage(INFO, "Enter major code: ");
    scanf("%s", code);
    string_to_uppercase(code);
    

    loadFromFile(lookup_table_major, major_lookup_path);
    if (search(lookup_table_major, code) == NULL) {
        printMessage(NOT_FOUND, "Major does not exist. Would you like to enter a new entry in Major? (y/n): ");
        scanf(" %c", &opt);
        if (tolower(opt) == 'y') {
            char* m_code = add_major(majors);
            strcpy(module.major_code, m_code);
            free(m_code);
        } else {
            printMessage(ERROR, "Major code not added. Aborting operation.\n");
            return;
        }
    } else {
        strcpy(module.major_code, code);
    }

    printMessage(INFO, "Enter semester (1-6): ");
    scanf("%d", &sem_temp);
    module.semester = (sem_temp > 0 && sem_temp <= MAX_SEMESTERS) ? sem_temp : 1;

    printMessage(INFO, "Enter pass mark: ");
    scanf("%f", &module.pass_mark);

    // Load and insert into lookup tables
    loadFromFile(lookup_table_module, module_lookup_path);
    loadFromFile(lookup_table_dpt, dpt_lookup_path);
    loadFromFile(lookup_table_prf, pfr_lookup_path);

    insert(lookup_table_module, module.module_code, module.module_name);
    insert(lookup_table_prf, module.prof_code, module.prof_name);
    insert(lookup_table_dpt, module.dept_code, module.dept_name);

    saveToFile(lookup_table_module, module_lookup_path);
    saveToFile(lookup_table_dpt, dpt_lookup_path);
    saveToFile(lookup_table_prf, pfr_lookup_path);

    
    fseek(file, 0, SEEK_END);
    fwrite(&module, sizeof(Module), 1, file);

    
    fclose(file);
}




void print_student_transcript(FILE *student_file, const char student_code[STUDENT_CODE_LENGTH], const char major_code[MAJOR_CODE_LENGTH], int start_semester){
    Student *student;
    char message[MESSAGE_LENGTH];
    student = find_student(student_file, student_code, major_code);
    print_student_yearly_results(student, start_semester);
}
void allocate_marks_to_student(FILE *student_file, const char student_code[STUDENT_CODE_LENGTH], const char major_code[MAJOR_CODE_LENGTH], int semester) {
    Student *student;
    student = find_student(student_file, student_code, major_code);
    char message[MESSAGE_LENGTH];
    char message2[MESSAGE_LENGTH];
    if (student != NULL) {
        if (semester < 1 || semester > 6) {  
            printMessage(ERROR, "Invalid semester number. Please enter a value between 1 and 6.\n");
            free(student);
            return;
        }

        
        Semester *current_semester = &student->major.semester[semester - 1];  
        for (int i = 0; i < current_semester->module_count; i++) {
            snprintf(message, MESSAGE_LENGTH, "Enter Mark for %s (%s): ", current_semester->modules[i].module_name, current_semester->modules[i].module_code);
            float mark;
            printMessage(INFO, message);
            scanf("%f", &mark);
            if(mark > MAX_MODULE_MARK){
                snprintf(message2, MESSAGE_LENGTH, "Mark cannot be greater than %d", MAX_MODULE_MARK);
                printMessage(WARNING, message2);
                snprintf(message, MESSAGE_LENGTH, "Enter Mark for %s (%s): ", current_semester->modules[i].module_name, current_semester->modules[i].module_code);
                printMessage(INFO, message);
                scanf("%f", &mark);
                if(mark > MAX_MODULE_MARK){
                    return;
                }else{
                    current_semester->modules[i].mark = mark;
                }

            }else{
                current_semester->modules[i].mark = mark;
            }
            if(current_semester->modules[i].mark >= current_semester->modules[i].pass_mark){
                strcpy(current_semester->modules[i].pass_status, "VALIDATED");
            }else{
                strcpy(current_semester->modules[i].pass_status, "NOT VALIDATED");
            }
        }
        fseek(student_file, -(long)sizeof(Student), SEEK_CUR);  
        if (ferror(student_file)) {
            printMessage(ERROR, "Location not found.\n");
            free(student);
            return;
        }

        if (fwrite(student, sizeof(Student), 1, student_file) != 1) {
            printMessage(ERROR, "Error writing the updated student record to the file.\n");
            free(student);
            return;
        }
       
        snprintf(message, MESSAGE_LENGTH, "Successfully added marks for student with code %s and major %s\n", student_code, major_code);
        printMessage(SUCCESS, message);
        print_student_semester_results(student, semester);
        free(student);
    } else {
        snprintf(message, MESSAGE_LENGTH, "Student with code %s and major %s not found.\n", student_code, major_code);
        printMessage(NOT_FOUND, message);
    }
}

void assign_semester_modules(FILE* student_file, char *student_code, const char *major_code, int semester) {
    Student *student = find_student(student_file, student_code, major_code);
    char message[MESSAGE_LENGTH];
    if (student == NULL) {
        printMessage(ERROR, "Student does not exist.\n");
        return;
    }

    
    if (student->major.semester[semester - 1].module_count > 0) {
        snprintf(message, MESSAGE_LENGTH, "Modules already assigned for semester %d.\n", semester);
        printMessage(WARNING, message);
        return;
    }

    
    populate_modules_for_student(student, major_code, semester);


    fseek(student_file, -(long)sizeof(Student), SEEK_CUR); 
    if (fwrite(student, sizeof(Student), 1, student_file) != 1) {
        printMessage(ERROR, "Error writing student data to file.\n");
        return;
    }

    fclose(student_file);
    printMessage(SUCCESS, "Modules assigned and student record updated.\n");
}

void populate_modules_for_student(Student *student, const char *major_code, int semester) {
    Module *module = (Module*)malloc(sizeof(Module));
    Node* lookup_table_major[TABLE_SIZE] = {0}; 
    char message[MESSAGE_LENGTH]; 
    char major_lookup_path[100], modules_path[100];
    FILE *modules;
    const char* dir = "data";
    int start_year, end_year;
    snprintf(major_lookup_path, sizeof(major_lookup_path), "%s/major_lookup.dat", dir);
    snprintf(modules_path, sizeof(modules_path), "%s/modules.dat", dir);

    printMessage(INFO, "Enter start academic year (YYYY YYYY): ");
    scanf("%d %d", &start_year, &end_year);

    loadFromFile(lookup_table_major, major_lookup_path);
    if (search(lookup_table_major, major_code) == NULL) {
        snprintf(message, MESSAGE_LENGTH, "Could not find major '%s'.\n", major_code);
        printMessage(NOT_FOUND, message);
        free(module);
        return;
    }

    
    modules = fopen(modules_path, "rb");
    if (modules == NULL) {
        snprintf(message, MESSAGE_LENGTH, "Could not open file '%s' for reading.\n", modules_path);
        printMessage(ERROR, message);
        free(module);
        return;
    }

    int module_count = 0; 
    while (module_count < MAX_MODULES_PER_SEMESTER && fread(module, sizeof(Module), 1, modules) == 1) {
        if (strcmp(module->major_code, major_code) == 0 && module->semester == semester) {
            // Populate the student's modules
            strcpy(student->major.semester[semester - 1].modules[module_count].module_code, module->module_code);
            strcpy(student->major.semester[semester - 1].modules[module_count].module_name, module->module_name);
            strcpy(student->major.semester[semester - 1].modules[module_count].dept_code, module->dept_code);
            strcpy(student->major.semester[semester - 1].modules[module_count].dept_name, module->dept_name);
            strcpy(student->major.semester[semester - 1].modules[module_count].prof_code, module->prof_code);
            strcpy(student->major.semester[semester - 1].modules[module_count].prof_name, module->prof_name);
            strcpy(student->major.semester[semester - 1].modules[module_count].major_code, major_code);
            strncpy(student->major.semester[semester - 1].modules[module_count].pass_status, "UNASSIGNED", 20);
            student->major.semester[semester - 1].modules[module_count].pass_mark = module->pass_mark;
            student->major.semester[semester - 1].modules[module_count].semester = module->semester;
            student->major.semester[semester - 1].academic_year.start_year = start_year;
            student->major.semester[semester - 1].academic_year.end_year = end_year;

            module_count++;  
        }
    }
    student->major.semester[semester -1].module_count = module_count;
    fclose(modules);  
    free(module);     

    if (module_count == 0) {
        snprintf(message, MESSAGE_LENGTH, "No modules found for major '%s' in semester %d.\n", major_code, semester);
        printMessage(NOT_FOUND, message);
    } else {
        snprintf(message, MESSAGE_LENGTH, "Populated %d module(s) for major '%s' in semester %d.\n", module_count, major_code, semester);
        printMessage(SUCCESS, message);
    }
}



void print_modules_for_semester(Student* student, int semester) {

    Node* lookup_table_major[TABLE_SIZE] = {NULL}; 
    char major_lookup_path[100];
    const char* dir = "data";
    snprintf(major_lookup_path, sizeof(major_lookup_path), "%s/major_lookup.dat", dir);
    loadFromFile(lookup_table_major, major_lookup_path);

    char* major_name = search(lookup_table_major, student->major.major_code);
    
    if (semester < 1 || semester > MAX_SEMESTERS) {
        printf("\033[1;31m[ERROR]: Invalid semester number. Valid range is 1 to %d.\033[0m\n", MAX_SEMESTERS);
        return;
    }

    if(student->major.semester[semester - 1].module_count == 0){
        printf("\033[1;31m[NOTFOUND] No modules found for semester %d \033[0m\n", semester);
    } else {
        if(major_name != NULL){
            printf("\nStudent Major: %s(%s)\n", major_name, student->major.major_code);
        }else{
            printf("\nStudent Major: %s\n", student->major.major_code);
        }
        
        printf("Semester %d:\n", semester);
        printf("Full Name: %s %s\n", student->l_name, student->f_name);
        printf("\033[1;34m\033[1m**************************************************************************************************************************************************\n\033[0m");

       
        printf("\033[1;34m\033[1m%-12s | %-40s | %-40s | %-30s | %-12s\n\033[0m", 
            "Code", "Module Name", "Department Name", "Professor Name", "Pass Status");
        printf("\033[1;34m\033[1m**************************************************************************************************************************************************\n\033[0m");

        
        for (int i = 0; i < student->major.semester[semester - 1].module_count; i++) {
            printf("%-12s | %-40s | %-40s | %-30s | %-12s\n", 
                student->major.semester[semester - 1].modules[i].module_code, 
                student->major.semester[semester - 1].modules[i].module_name,
                student->major.semester[semester - 1].modules[i].dept_name, 
                student->major.semester[semester - 1].modules[i].prof_name,
                student->major.semester[semester - 1].modules[i].pass_status);
        }
    }
}







void print_modules(FILE* file, const char major_code[MAJOR_CODE_LENGTH], int semester) {
    if (file == NULL) {
        printMessage(ERROR, "File could not be opened.\n");
        return;
    }

    if (semester < 1 || semester > MAX_SEMESTERS) {
        printf("\033[1;31m[ERROR]Error: Invalid semester number. Valid range is 1 to %d.\033[0m\n", MAX_SEMESTERS);
        return;
    }

    Module module;
    int module_count = 0;
    while (fread(&module, sizeof(Module), 1, file) == 1) {

        if(strcmp(module.major_code, major_code) == 0 && module.semester == semester){
            printf("\033[1;34m\n------------------------------------------------------------------\033[0m\n");
            printf("\033[1;32mModule %d\033[0m\n", ++module_count);
            printf("\033[1;33m  Module Code    :\033[0m %-15s\n", module.module_code);
            printf("\033[1;33m  Module Name    :\033[0m %-15s\n", module.module_name);
            printf("\033[1;33m  Department Code:\033[0m %-15s\n", module.dept_code);
            printf("\033[1;33m  Department Name:\033[0m %-15s\n", module.dept_name);
            printf("\033[1;33m  Professor Code :\033[0m %-15s\n", module.prof_code);
            printf("\033[1;33m  Professor Name :\033[0m %-15s\n", module.prof_name);
            printf("\033[1;33m  Major Code     :\033[0m %-15s\n", module.major_code);
            printf("\033[1;33m  Semester       :\033[0m %-15d\n", module.semester);
            printf("\033[1;33m  Pass Mark      :\033[0m %-15.2f\n", module.pass_mark);
            printf("\033[1;34m\n------------------------------------------------------------------\033[0m\n");
        }
        
    }

    if (module_count == 0) {
        printMessage(NOT_FOUND, "No modules found in the file.\n");
    }

    printf("\033[1;36m\n******************** END OF LIST **************************\033[0m\n");

    fclose(file);
}



void update_module(FILE* file, const char* module_code) {
    Module module;

    Node* lookup_table_module[TABLE_SIZE] = {0};
    Node* lookup_table_prf[TABLE_SIZE] = {0};
    Node* lookup_table_dpt[TABLE_SIZE] = {0};
    char message[MESSAGE_LENGTH];
    const char* dir = "data";
    char module_lookup_path[100], pfr_lookup_path[100], dpt_lookup_path[100];

    snprintf(module_lookup_path, sizeof(module_lookup_path), "%s/module_lookup.dat", dir);
    snprintf(pfr_lookup_path, sizeof(pfr_lookup_path), "%s/pfr_lookup.dat", dir);
    snprintf(dpt_lookup_path, sizeof(dpt_lookup_path), "%s/dpt_lookup.dat", dir);

    loadFromFile(lookup_table_module, module_lookup_path);
    loadFromFile(lookup_table_prf, pfr_lookup_path);
    loadFromFile(lookup_table_dpt, dpt_lookup_path);

    int found = 0;

    if (file == NULL) {
        printMessage(ERROR, "File could not be opened.");
        return;
    }

    while (fread(&module, sizeof(Module), 1, file)) {
        if (strcmp(module.module_code, module_code) == 0) {
            found = 1;

           
            printf("\033[1;34mCurrent Module Name: \033[0m%s\n", module.module_name);
            printMessage(INFO, "Would you like to change the module name? (y/n): ");
            char change_name;
            scanf(" %c", &change_name); 
            if (change_name == 'y') {
                printMessage(INFO, "Enter new module name: ");
                scanf(" %[^\n]", module.module_name);
            }

            printf("\033[1;34mCurrent Professor Code: \033[0m%s\n", module.prof_code);
            printf("\033[1;34mCurrent Professor Name: \033[0m%s\n", search(lookup_table_prf, module.prof_code));
            printMessage(INFO, "Would you like to change the professor details? (y/n): ");
            char change_prof;
            scanf(" %c", &change_prof);
            if (change_prof == 'y') {
                printMessage(INFO, "Enter new professor code: ");
                scanf("%s", module.prof_code);
                printMessage(INFO, "Enter new professor name: ");
                scanf(" %[^\n]", module.prof_name);
            }

            
            printf("\033[1;34mCurrent Department Code: \033[0m%s\n", module.dept_code);
            printf("\033[1;34mCurrent Department Name: \033[0m%s\n", module.dept_name); 
            printMessage(INFO, "Would you like to change the department details? (y/n): ");
            char change_dept;
            scanf(" %c", &change_dept);
            if (change_dept == 'y') {
                printMessage(INFO, "Enter new department code: ");
                scanf("%s", module.dept_code);
                printMessage(INFO, "Enter new department name: " );
                scanf(" %[^\n]", module.dept_name);
            }

            printf("\033[1;34mCurrent Semester: \033[0m%d\n", module.semester);
            printMessage(INFO, "Would you like to change the semester? (y/n): " );
            char change_semester;
            scanf(" %c", &change_semester);
            if (change_semester == 'y') {
                printMessage(INFO, "Enter new semester: " );
                scanf("%d", &module.semester); 
            }

            printf("\033[1;34mCurrent Pass Mark: \033[0m%.2f\n", module.pass_mark);
            printMessage(INFO, "Would you like to change the pass mark? (y/n): " );
            char change_passmark;
            scanf(" %c", &change_passmark);
            if (change_passmark == 'y') {
                printMessage(INFO, "Enter new pass mark:" );
                scanf("%f", &module.pass_mark);
            }

            // Update hash table and file
            update_hash(lookup_table_module, module.module_code, module.module_name);
            insert(lookup_table_prf, module.prof_code, module.prof_name);
            insert(lookup_table_dpt, module.dept_code, module.dept_name);
            saveToFile(lookup_table_prf, pfr_lookup_path);
            saveToFile(lookup_table_dpt, dpt_lookup_path);
            saveToFile(lookup_table_module, module_lookup_path);

            fseek(file, -(long)sizeof(Module), SEEK_CUR);
            fwrite(&module, sizeof(Module), 1, file);
            fflush(file);

            printMessage(SUCCESS, "Module updated successfully.\n");
            break;
        }
    }

    if (!found) {
        snprintf(message, MESSAGE_LENGTH, "Module with code %s not found.\n", module_code);
        printMessage(NOT_FOUND, message);
    }
}



