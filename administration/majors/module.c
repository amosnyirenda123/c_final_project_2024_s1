#include "module.h"
#include "../students/student.h"



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

void print_student_semester_results(Student *student, int semester){
        Semester *current_semester = &student->major.semester[semester - 1];
        int year_of_study = deduce_year_of_study(semester);
        printf("\n");
        printf("\t\t\t\t\tSEMESTER %d\n", semester);
        printf("\t\tFULL NAME: %s %s   MAJOR: %s(%d)   STD CODE: %s\n", student->l_name, student->f_name, student->major.major_code,year_of_study, student->code);
        printf("--------------------------------------------------------------------------------------------------------\n");
        printf("%-50s | %-10s | %-10s\n", "MODULE", "CODE", "MARK");
        printf("--------------------------------------------------------------------------------------------------------\n");
        // Display marks for the current semester
        
        for (int i = 0; i < current_semester->module_count; i++) {
            printf("%-50s | %-10s | %.2f\n", current_semester->modules[i].module_name, current_semester->modules[i].module_code, current_semester->modules[i].mark);
        }
        float semester_average = sum_of_marks(current_semester->modules, current_semester->module_count) / current_semester->module_count;
        char grade[10];
        strcpy(grade, get_grade(semester_average));
        printf("--------------------------------------------------------------------------------------------------------\n");
        printf("%-50s | %-10s | %.2f(%s)\n", "################################################", "AVERAGE", semester_average,grade);

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
        }

        // Display marks added
        printf("Successfully added marks for student with code %s and major %s\n", student_code, major_code);
        print_student_semester_results(student, semester);
        free(student);
    } else {
        printf("Student with code %s and major %s not found.\n", student_code, major_code);
    }
}

void populate_modules_for_student(Student *student, const char *major_code) {
    int major_index = -1;
    
    
    if (strcmp(major_code, "GI") == 0) {
        major_index = 0; 
    } else if (strcmp(major_code, "CE") == 0) {
        major_index = 1; 
    }

   
    if (major_index == -1) {
        printf("Error: Invalid major code.\n");
        return;
    }

    for (int sem = 0; sem < MAX_SEMESTERS; sem++) {
        student->major.semester[sem].module_count = MAX_MODULES_PER_SEMESTER;
        for (int i = 0; i < MAX_MODULES_PER_SEMESTER; i++) {
            if (major_index == 0) {
                // Populate GI Modules
                strcpy(student->major.semester[sem].modules[i].module_code, GI_modules[sem][i].module_code);
                strcpy(student->major.semester[sem].modules[i].module_name, GI_modules[sem][i].module_name);
            } else if (major_index == 1) {
                // Populate CE Modules
                strcpy(student->major.semester[sem].modules[i].module_code, CE_modules[sem][i].module_code);
                strcpy(student->major.semester[sem].modules[i].module_name, CE_modules[sem][i].module_name);
            }
        }
    }
}

void print_modules_for_student(Student *student) {
    printf("Modules for Major: %s\n", student->major.major_code);
    for (int sem = 0; sem < MAX_SEMESTERS; sem++) {
        printf("\nSemester %d:\n", sem + 1);
        for (int i = 0; i < student->major.semester[sem].module_count; i++) {
            printf("%s - %s\n", student->major.semester[sem].modules[i].module_code, student->major.semester[sem].modules[i].module_name);
        }
    }
}