#include "module.h"
#include "../maps/map.h"
#include "../students/student.h"
#include <ctype.h>
// #include <hpdf.h>



// Major Modules for GI and CE

Module GI_modules[MAX_SEMESTERS][MAX_MODULES_PER_SEMESTER] = {
    // Semester 1
   {
        {"GI201", "Object-Oriented Programming"},
        {"GI202", "Linear Algebra"},
        {"GI203", "Digital Logic Design"},
        {"GI204", "Data Structures and Algorithms II"},
        {"GI205", "Calculus II"},
        {"GI206", "Statistics and Probability"}
    },
    // Semester 2
    {
        {"GI301", "Operating Systems"},
        {"GI302", "Database Systems"},
        {"GI303", "Computer Networks"},
        {"GI304", "Software Engineering"},
        {"GI305", "Theory of Computation"},
        {"GI306", "Graph Theory"}
    },
    // Semester 3
    {
        {"GI401", "Artificial Intelligence"},
        {"GI402", "Machine Learning"},
        {"GI403", "Computer Graphics"},
        {"GI404", "Data Mining"},
        {"GI405", "Optimization Techniques"},
        {"GI406", "Compiler Design"}
    },
    // Semester 4
    {
        {"GI501", "Cyber Security"},
        {"GI502", "Distributed Systems"},
        {"GI503", "Advanced Algorithms"},
        {"GI504", "Big Data Analytics"},
        {"GI505", "Human-Computer Interaction"},
        {"GI506", "Research Methods"}
    },
    // Semester 5
    {
        {"GI601", "Cloud Computing"},
        {"GI602", "Internet of Things"},
        {"GI603", "Blockchain Technology"},
        {"GI604", "Robotics"},
        {"GI605", "Natural Language Processing"},
        {"GI606", "Capstone Project"}
    },
    // Semester 6
    {
        {"CE701", "Fluid Mechanics"},
        {"CE702", "Statics"},
        {"CE703", "Concrete Technology"},
        {"CE704", "Surveying"},
        {"CE705", "Linear Algebra"},
        {"CE706", "Engineering Geology"}
    }
};

Module CE_modules[MAX_SEMESTERS][MAX_MODULES_PER_SEMESTER] = {
    // Semester 1
    {
        {"CE201", "Fluid Mechanics"},
        {"CE202", "Statics"},
        {"CE203", "Concrete Technology"},
        {"CE204", "Surveying"},
        {"CE205", "Linear Algebra"},
        {"CE206", "Engineering Geology"}
    },
    // Semester 2
    {
        {"CE301", "Structural Analysis"},
        {"CE302", "Soil Mechanics"},
        {"CE303", "Concrete Structures"},
        {"CE304", "Building Materials"},
        {"CE305", "Transportation Engineering"},
        {"CE306", "Hydraulics"}
    },
    // Semester 3
    {
        {"CE401", "Structural Design"},
        {"CE402", "Water Resources Engineering"},
        {"CE403", "Geotechnical Engineering"},
        {"CE404", "Environmental Engineering"},
        {"CE405", "Surveying II"},
        {"CE406", "Advanced Surveying"}
    },
    // Semester 4
    {
        {"CE501", "Project Management"},
        {"CE502", "Reinforced Concrete Design"},
        {"CE503", "Highway Engineering"},
        {"CE504", "Foundation Engineering"},
        {"CE505", "Advanced Fluid Mechanics"},
        {"CE506", "Research Methods"}
    },
    // Semester 5
    {
        {"CE601", "Construction Technology"},
        {"CE602", "Geotechnical Design"},
        {"CE603", "Bridge Engineering"},
        {"CE604", "Transportation Planning"},
        {"CE605", "Water Resources Management"},
        {"CE606", "Capstone Project"}
    },
    // Semester 6
    {
        {"CE701", "Advanced Structural Design"},
        {"CE702", "Water Treatment Engineering"},
        {"CE703", "Urban Planning and Design"},
        {"CE704", "Sustainable Construction"},
        {"CE705", "Coastal Engineering"},
        {"CE706", "Disaster Management"}
    }
};

Module EE_modules[MAX_SEMESTERS][MAX_MODULES_PER_SEMESTER] = {
   // Semester 1
    {
        {"EE201", "Circuit Theory"},
        {"EE202", "Mathematics for Engineers I"},
        {"EE203", "Introduction to Electrical Engineering"},
        {"EE204", "Physics for Engineers"},
        {"EE205", "Computer Programming"},
        {"EE206", "Electrical Measurements"}
    },
    // Semester 2
    {
        {"EE301", "Signals and Systems"},
        {"EE302", "Electromagnetic Fields"},
        {"EE303", "Digital Electronics"},
        {"EE304", "Engineering Mathematics II"},
        {"EE305", "Microelectronics"},
        {"EE306", "Electronics Laboratory"}
    },
    // Semester 3
    {
        {"EE401", "Control Systems"},
        {"EE402", "Power Systems"},
        {"EE403", "Electrical Machines"},
        {"EE404", "Analog Electronics"},
        {"EE405", "Communication Systems"},
        {"EE406", "Electrical Power Lab"}
    },
    // Semester 4
    {
        {"EE501", "Digital Signal Processing"},
        {"EE502", "Power Electronics"},
        {"EE503", "Renewable Energy Systems"},
        {"EE504", "Microprocessors"},
        {"EE505", "VLSI Design"},
        {"EE506", "Electrical Engineering Project"}
    },
    // Semester 5
    {
        {"EE601", "Industrial Automation"},
        {"EE602", "Smart Grids"},
        {"EE603", "Optical Communications"},
        {"EE604", "Electrical Safety and Protection"},
        {"EE605", "Electric Vehicles"},
        {"EE606", "Advanced Power Systems"}
    },
    // Semester 6
    {
        {"EE701", "Advanced Control Systems"},
        {"EE702", "Machine Learning for Electrical Engineers"},
        {"EE703", "Power Distribution"},
        {"EE704", "Microgrid Systems"},
        {"EE705", "Embedded Systems"},
        {"EE706", "Capstone Project"}
    } 
};

Module ME_modules[MAX_SEMESTERS][MAX_MODULES_PER_SEMESTER] = {
     // Semester 1
    {
        {"ME201", "Mechanics of Solids"},
        {"ME202", "Engineering Drawing"},
        {"ME203", "Materials Science"},
        {"ME204", "Mathematics for Engineers I"},
        {"ME205", "Physics for Engineers"},
        {"ME206", "Engineering Workshop"}
    },
    // Semester 2
    {
        {"ME301", "Fluid Mechanics"},
        {"ME302", "Thermodynamics"},
        {"ME303", "Strength of Materials"},
        {"ME304", "Engineering Mathematics II"},
        {"ME305", "Mechanical Measurements"},
        {"ME306", "Manufacturing Processes"}
    },
    // Semester 3
    {
        {"ME401", "Dynamics of Machinery"},
        {"ME402", "Machine Design"},
        {"ME403", "Heat Transfer"},
        {"ME404", "Kinematics of Mechanisms"},
        {"ME405", "Control Systems"},
        {"ME406", "Mechanical Engineering Lab"}
    },
    // Semester 4
    {
        {"ME501", "Finite Element Analysis"},
        {"ME502", "Refrigeration and Air Conditioning"},
        {"ME503", "Internal Combustion Engines"},
        {"ME504", "Engineering Mechanics of Solids"},
        {"ME505", "Manufacturing Systems"},
        {"ME506", "Project Work"}
    },
    // Semester 5
    {
        {"ME601", "Robotics"},
        {"ME602", "Advanced Materials"},
        {"ME603", "Mechatronics"},
        {"ME604", "Renewable Energy Systems"},
        {"ME605", "Computational Fluid Dynamics"},
        {"ME606", "Advanced Manufacturing Techniques"}
    },
    // Semester 6
    {
        {"ME701", "Machine Tool Technology"},
        {"ME702", "Structural Vibration"},
        {"ME703", "Nanotechnology"},
        {"ME704", "Automotive Engineering"},
        {"ME705", "Aerospace Engineering"},
        {"ME706", "Capstone Project"}
    }
};

Module ChE_modules[MAX_SEMESTERS][MAX_MODULES_PER_SEMESTER] = {
      // Semester 1
    {
        {"ChE201", "Chemical Engineering Principles"},
        {"ChE202", "Mathematics for Engineers I"},
        {"ChE203", "Chemistry for Engineers"},
        {"ChE204", "Fluid Mechanics"},
        {"ChE205", "Engineering Drawing"},
        {"ChE206", "Process Instrumentation"}
    },
    // Semester 2
    {
        {"ChE301", "Material and Energy Balances"},
        {"ChE302", "Thermodynamics"},
        {"ChE303", "Transport Phenomena"},
        {"ChE304", "Chemical Reaction Engineering"},
        {"ChE305", "Chemical Process Control"},
        {"ChE306", "Laboratory Techniques"}
    },
    // Semester 3
    {
        {"ChE401", "Separation Processes"},
        {"ChE402", "Process Dynamics and Control"},
        {"ChE403", "Environmental Engineering"},
        {"ChE404", "Heat Transfer"},
        {"ChE405", "Process Design"},
        {"ChE406", "Process Simulation Lab"}
    },
    // Semester 4
    {
        {"ChE501", "Mass Transfer"},
        {"ChE502", "Fluidization Engineering"},
        {"ChE503", "Biochemical Engineering"},
        {"ChE504", "Process Optimization"},
        {"ChE505", "Petroleum Engineering"},
        {"ChE506", "Project Work"}
    },
    // Semester 5
    {
        {"ChE601", "Energy Systems Engineering"},
        {"ChE602", "Process Safety and Hazard Analysis"},
        {"ChE603", "Industrial Waste Treatment"},
        {"ChE604", "Process Modeling"},
        {"ChE605", "Advanced Chemical Engineering"},
        {"ChE606", "Design and Simulation"}
    },
    // Semester 6
    {
        {"ChE701", "Nanotechnology in Chemical Engineering"},
        {"ChE702", "Pharmaceutical Engineering"},
        {"ChE703", "Renewable Energy Systems"},
        {"ChE704", "Food Engineering"},
        {"ChE705", "Catalysis and Reactor Design"},
        {"ChE706", "Capstone Project"}
    }
};

Module CoE_modules[MAX_SEMESTERS][MAX_MODULES_PER_SEMESTER] = {
    // Semester 1
    {
        {"CoE201", "Digital Logic Design"},
        {"CoE202", "Mathematics for Engineers I"},
        {"CoE203", "Introduction to Computer Engineering"},
        {"CoE204", "Physics for Engineers"},
        {"CoE205", "Computer Programming"},
        {"CoE206", "Electrical Circuits"}
    },
    // Semester 2
    {
        {"CoE301", "Data Structures and Algorithms"},
        {"CoE302", "Microprocessors"},
        {"CoE303", "Discrete Mathematics"},
        {"CoE304", "Signals and Systems"},
        {"CoE305", "Computer Organization"},
        {"CoE306", "Computer Networks"}
    },
    // Semester 3
    {
        {"CoE401", "Digital Signal Processing"},
        {"CoE402", "Operating Systems"},
        {"CoE403", "Database Systems"},
        {"CoE404", "Computer Architecture"},
        {"CoE405", "Software Engineering"},
        {"CoE406", "Embedded Systems"}
    },
    // Semester 4
    {
        {"CoE501", "Computer Graphics"},
        {"CoE502", "Artificial Intelligence"},
        {"CoE503", "Machine Learning"},
        {"CoE504", "Network Security"},
        {"CoE505", "Cloud Computing"},
        {"CoE506", "Capstone Project"}
    },
    // Semester 5
    {
        {"CoE601", "Data Mining"},
        {"CoE602", "Blockchain Technology"},
        {"CoE603", "Big Data Analytics"},
        {"CoE604", "Internet of Things"},
        {"CoE605", "Distributed Systems"},
        {"CoE606", "Human-Computer Interaction"}
    },
    // Semester 6
    {
        {"CoE701", "Cyber Security"},
        {"CoE702", "Advanced Algorithms"},
        {"CoE703", "Advanced Networking"},
        {"CoE704", "Embedded Systems Design"},
        {"CoE705", "Mobile Computing"},
        {"CoE706", "Capstone Project"}
    }
};

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
    // HPDF_Doc pdf = HPDF_New(NULL, NULL);

    // if (!pdf) {
        // printf("Failed to create PDF document\n");
    // }

    // Set up the page
    // HPDF_Page page = HPDF_AddPage(pdf);
    // HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
    // HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", NULL);
    // HPDF_Page_SetFontAndSize(page, font, 12);

    if(start_semester == 1 || start_semester == 3 || start_semester == 5){
        printf("********************************************************************************************************\n");
        printf("\t\t\t\t%d YEAR STATEMENT OF RESULTS (TRANSCRIPT)\n", deduce_year_of_study(start_semester));
        printf("--------------------------------------------------------------------------------------------------------\n");
        print_student_semester_results(student, start_semester);
        print_student_semester_results(student, start_semester + 1);
        // print_student_semester_results_pdf(pdf, page, student, start_semester);
        // print_student_semester_results_pdf(pdf, page, student, start_semester + 1);
        
        float s1_average = get_semester_average(student, start_semester);
        float s2_average = get_semester_average(student, start_semester + 1);
        float year_average = (s1_average + s2_average) / 2;
        printf("\t\t\t\t\tYEAR AVERAGE: %.2f(%s)\n", year_average, get_grade(year_average));
        printf("********************************************************************************************************\n");
        // HPDF_SaveToFile(pdf, "transcript.pdf");
        // HPDF_Free(pdf);
        printf("PDF created successfully!\n");
    }else{
        printf("Start semester should be one of these values [1,3,5]\n");
        // HPDF_Free(pdf);
    }
    
}

void print_student_semester_results(Student *student, int semester){
        if(semester > 0 && semester <= MAX_SEMESTERS){
            Semester *current_semester = &student->major.semester[semester - 1];
            int start_year = current_semester->academic_year.start_year;
            int end_year = current_semester->academic_year.end_year;
        int year_of_study = deduce_year_of_study(semester);
        printf("\n");
        printf("\t\t\t\t\t  SEMESTER %d (%d/%d)\n", semester, start_year,end_year);
        printf("\t\tFULL NAME: %s %s   MAJOR: %s(%d)   STD CODE: %s\n", student->l_name, student->f_name, student->major.major_code,year_of_study, student->code);
        printf("--------------------------------------------------------------------------------------------------------\n");
        printf("%-50s | %-10s | %-10s | %-18s\n", "MODULE", "CODE", "MARK", "STATUS");
        printf("--------------------------------------------------------------------------------------------------------\n");
        // Display marks for the current semester
        
        for (int i = 0; i < current_semester->module_count; i++) {
            printf("%-50s | %-10s | %-10.2f | %-18s\n", current_semester->modules[i].module_name, current_semester->modules[i].module_code, current_semester->modules[i].mark, current_semester->modules[i].pass_status);
        }
        current_semester->average_mark = sum_of_marks(current_semester->modules, current_semester->module_count) / current_semester->module_count;;
        char grade[10];
        strcpy(grade, get_grade(current_semester->average_mark));
        printf("--------------------------------------------------------------------------------------------------------\n");
        printf("%-50s | %-10s | %.2f(%s)\n", "################################################", "AVERAGE", current_semester->average_mark,grade);
        printf("--------------------------------------------------------------------------------------------------------\n");
        }

}

// void print_student_semester_results_pdf(HPDF_Doc pdf, HPDF_Page page, Student *student, int semester) {
//     if (semester > 0 && semester <= MAX_SEMESTERS) {
//         Semester *current_semester = &student->major.semester[semester - 1];
        
//         char buffer[256];
        
//         // Semester title
//         sprintf(buffer, "SEMESTER %d (%d/%d)", semester, current_semester->academic_year.start_year, current_semester->academic_year.end_year);
//         HPDF_Page_BeginText(page);
//         HPDF_Page_TextOut(page, 50, 750, buffer);
//         HPDF_Page_EndText(page);

//         // Header
//         HPDF_Page_BeginText(page);
//         sprintf(buffer, "FULL NAME: %s %s | MAJOR: %s | STD CODE: %s", student->l_name, student->f_name, student->major.major_code, student->code);
//         HPDF_Page_TextOut(page, 50, 730, buffer);
//         HPDF_Page_EndText(page);

//         // Table header
//         HPDF_Page_BeginText(page);
//         HPDF_Page_TextOut(page, 50, 700, "MODULE                               | CODE       | MARK     | STATUS");
//         HPDF_Page_EndText(page);
        
//         // Module data
//         for (int i = 0; i < current_semester->module_count; i++) {
//             Module *mod = &current_semester->modules[i];
//             sprintf(buffer, "%-50s | %-10s | %-10.2f | %-18s", mod->module_name, mod->module_code, mod->mark, mod->pass_status);
//             HPDF_Page_BeginText(page);
//             HPDF_Page_TextOut(page, 50, 680 - i * 15, buffer);
//             HPDF_Page_EndText(page);
//         }

//         // Semester average
//         current_semester->average_mark = sum_of_marks(current_semester->modules, current_semester->module_count) / current_semester->module_count;
//         char grade[10];
//         strcpy(grade, get_grade(current_semester->average_mark));
//         sprintf(buffer, "AVERAGE: %.2f (%s)", current_semester->average_mark, grade);
//         HPDF_Page_BeginText(page);
//         HPDF_Page_TextOut(page, 50, 500, buffer);
//         HPDF_Page_EndText(page);
//     }
// }

// void add_module(){
//     Module module_details;
//     int sem;
//     char pf_code[MAX_LENGTH], dpt_code[MAX_LENGTH], mjr_code[MAX_LENGTH];
//     printf("Enter module name: ");
//     scanf("%s", module_details.module_name);
//     printf("Enter module code: ");
//     scanf("%s", module_details.module_code);
//     printf("Enter pass mark ");
//     scanf("%f", &module_details.pass_mark);
//     printf("Enter semester: ");
//     scanf("%d", &sem);
//     if(sem > 0 && sem < MAX_SEMESTERS + 1){
//         module_details.semester = sem - 1;
//     }
//     printf("Enter Department code: ");
//     scanf("%s", dpt_code);

//     printf("Enter Professor code: ");
//     scanf("%s", pf_code);

//     printf("Enter Major code: ");
//     scanf("%s", mjr_code);

// }

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

    printf("Enter module code: ");
    scanf("%s", module.module_code);

    printf("Enter module name: ");
    scanf(" %[^\n]", module.module_name); 

    printf("Enter professor code: ");
    scanf("%s", module.prof_code);

    printf("Enter professor name: ");
    scanf(" %[^\n]", module.prof_name);

    printf("Enter department code: ");
    scanf("%s", module.dept_code);

    printf("Enter department name: ");
    scanf(" %[^\n]", module.dept_name);

    printf("Enter major code: ");
    scanf("%s", code);

    loadFromFile(lookup_table_major, major_lookup_path);
    if (search(lookup_table_major, code) == NULL) {
        printf("Major does not exist. Would you like to enter a new entry in Major? (y/n): ");
        scanf(" %c", &opt);
        if (tolower(opt) == 'y') {
            char* m_code = add_major(majors);
            strcpy(module.major_code, m_code);
            free(m_code);
        } else {
            printf("Major code not added. Aborting operation.\n");
            return;
        }
    } else {
        strcpy(module.major_code, code);
    }

    printf("Enter semester (1-6): ");
    scanf("%d", &sem_temp);
    module.semester = (sem_temp > 0 && sem_temp <= MAX_SEMESTERS) ? sem_temp : 1;

    printf("Enter pass mark: ");
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




void print_student_transcript(FILE *student_file, const char student_code[CODE_LENGTH], const char major_code[CODE_LENGTH], int start_semester){
    Student *student;
    student = find_student(student_file, student_code, major_code);
    print_student_yearly_results(student, start_semester);
}
void allocate_marks_to_student(FILE *student_file, const char student_code[CODE_LENGTH], const char major_code[CODE_LENGTH], int semester) {
    Student *student;
    student = find_student(student_file, student_code, major_code);
    
    if (student != NULL) {
        if (semester < 1 || semester > 6) {  
            printf("Invalid semester number. Please enter a value between 1 and 6.\n");
            free(student);
            return;
        }

        // Updating marks for semester
        Semester *current_semester = &student->major.semester[semester - 1];  
        for (int i = 0; i < current_semester->module_count; i++) {
            printf("Enter Mark for %s (%s): ", current_semester->modules[i].module_name, current_semester->modules[i].module_code);
            scanf("%f", &current_semester->modules[i].mark);
            if(current_semester->modules[i].mark >= current_semester->modules[i].pass_mark){
                strcpy(current_semester->modules[i].pass_status, "VALIDATED");
            }else{
                strcpy(current_semester->modules[i].pass_status, "NOT VALIDATED");
            }
        }
        fseek(student_file, -(long)sizeof(Student), SEEK_CUR); //Moving back 
        if (ferror(student_file)) {
            perror("Error seeking to the correct position in the file");
            free(student);
            return;
        }

        if (fwrite(student, sizeof(Student), 1, student_file) != 1) {
            perror("Error writing the updated student record to the file");
            free(student);
            return;
        }
        // Display marks added
        printf("Successfully added marks for student with code %s and major %s\n", student_code, major_code);
        print_student_semester_results(student, semester);
        free(student);
    } else {
        printf("Student with code %s and major %s not found.\n", student_code, major_code);
    }
}

void assign_semester_modules(FILE* student_file, char *student_code, const char *major_code, int semester) {
    Student *student = find_student(student_file, student_code, major_code);
    if (student == NULL) {
        printf("Student does not exist.\n");
        return;
    }

    
    if (student->major.semester[semester - 1].module_count > 0) {
        printf("Modules already assigned for semester %d.\n", semester);
        return;
    }

    
    populate_modules_for_student(student, major_code, semester);


    fseek(student_file, -(long)sizeof(Student), SEEK_CUR); 
    if (fwrite(student, sizeof(Student), 1, student_file) != 1) {
        printf("Error writing student data to file.\n");
        return;
    }

    fclose(student_file);
    printf("Modules assigned and student record updated.\n");
}

void populate_modules_for_student(Student *student, const char *major_code, int semester) {
    Module *module = (Module*)malloc(sizeof(Module));
    Node* lookup_table_major[TABLE_SIZE] = {NULL};  // Initialize hash table
    char major_lookup_path[100], modules_path[100];
    FILE *modules;
    const char* dir = "data";
    int start_year, end_year;
    snprintf(major_lookup_path, sizeof(major_lookup_path), "%s/major_lookup.dat", dir);
    snprintf(modules_path, sizeof(modules_path), "%s/modules.dat", dir);

    printf("Enter student Academic Year (start[SPACE]end): ");
    scanf("%d %d", &start_year, &end_year);

    loadFromFile(lookup_table_major, major_lookup_path);
    if (search(lookup_table_major, major_code) == NULL) {
        printf("Could not find major '%s'.\n", major_code);
        free(module);
        return;
    }

    
    modules = fopen(modules_path, "rb");
    if (modules == NULL) {
        printf("Could not open file '%s' for reading.\n", modules_path);
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
        printf("No modules found for major '%s' in semester %d.\n", major_code, semester);
    } else {
        printf("Populated %d module(s) for major '%s' in semester %d.\n", module_count, major_code, semester);
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
        printf("\033[1;31m[ERROR]Error: Invalid semester number. Valid range is 1 to %d.\033[0m\n", MAX_SEMESTERS);
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







void print_modules(FILE* file) {
    if (file == NULL) {
        printf("\033[1;31m[ERROR] File could not be opened.\033[0m\n");
        return;
    }

    Module module;
    int module_count = 0;

    printf("\033[1;36m\n************ MODULE LIST ************\033[0m\n");

    while (fread(&module, sizeof(Module), 1, file) == 1) {
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
        printf("\033[1;34m--------------------------------------------------------------------\033[0m\n");
    }

    if (module_count == 0) {
        printf("\033[1;31m[INFO] No modules found in the file.\033[0m\n");
    }

    printf("\033[1;36m\n************** END OF LIST **************\033[0m\n");

    fclose(file);
}



void update_module(FILE* file, const char* module_code) {
    Module module;

    Node* lookup_table_module[TABLE_SIZE] = {0};
    Node* lookup_table_prf[TABLE_SIZE] = {0};
    Node* lookup_table_dpt[TABLE_SIZE] = {0};
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
        printf("\033[1;31mError: File could not be opened.\033[0m\n");
        return;
    }

    while (fread(&module, sizeof(Module), 1, file)) {
        if (strcmp(module.module_code, module_code) == 0) {
            found = 1;

            // Ask if they want to change the module name
            printf("\033[1;34mCurrent Module Name: \033[0m%s\n", module.module_name);
            printf("Would you like to change the module name? (y/n): ");
            char change_name;
            scanf(" %c", &change_name); // Space before %c to consume any leftover newline
            if (change_name == 'y') {
                printf("Enter new module name: ");
                scanf(" %[^\n]", module.module_name);
            }

            // Ask if they want to change the professor details
            printf("\033[1;34mCurrent Professor Code: \033[0m%s\n", module.prof_code);
            printf("\033[1;34mCurrent Professor Name: \033[0m%s\n", search(lookup_table_prf, module.prof_code));
            printf("Would you like to change the professor details? (y/n): ");
            char change_prof;
            scanf(" %c", &change_prof);
            if (change_prof == 'y') {
                printf("Enter new professor code: ");
                scanf("%s", module.prof_code);
                printf("Enter new professor name: ");
                scanf(" %[^\n]", module.prof_name);
            }

            // Ask if they want to change department details
            printf("\033[1;34mCurrent Department Code: \033[0m%s\n", module.dept_code);
            printf("\033[1;34mCurrent Department Name: \033[0m%s\n", module.dept_name); 
            printf("Would you like to change the department details? (y/n): ");
            char change_dept;
            scanf(" %c", &change_dept);
            if (change_dept == 'y') {
                printf("Enter new department code: ");
                scanf("%s", module.dept_code);
                printf("Enter new department name: ");
                scanf(" %[^\n]", module.dept_name);
            }

            // Ask if they want to change the semester
            printf("\033[1;34mCurrent Semester: \033[0m%d\n", module.semester);
            printf("Would you like to change the semester? (y/n): ");
            char change_semester;
            scanf(" %c", &change_semester);
            if (change_semester == 'y') {
                printf("Enter new semester: ");
                scanf("%d", &module.semester); 
            }

            // Ask if they want to change the pass mark
            printf("\033[1;34mCurrent Pass Mark: \033[0m%.2f\n", module.pass_mark);
            printf("Would you like to change the pass mark? (y/n): ");
            char change_passmark;
            scanf(" %c", &change_passmark);
            if (change_passmark == 'y') {
                printf("\033[1;33mEnter new pass mark: \033[0m");
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

            printf("\033[1;32m[SUCCESS] Module updated successfully.\033[0m\n");
            break;
        }
    }

    if (!found) {
        printf("\033[1;31m[FAILED] Module with code %s not found.\033[0m\n", module_code);
    }
}



