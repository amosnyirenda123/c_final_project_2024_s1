#include <stdlib.h>
#include "administration/students/student.h"
#include "administration/majors/major.h"
#include "administration/majors/module.h"
#include "administration/maps/map.h"
// #include <hpdf.h>


int main(void)
{
    FILE *file;
    file = fopen("data/student.dat", "r+b");

    if(file == NULL) {
        printf("Failed to open file in write mode");
        return 1;
    }
    // display_all_students(file); 
    // add_student(file);
    // find_student_and_print_details(file, "2024-10029622");
    // update_student_details(student_file, "2024-10022609", "GI");
    // allocate_marks_to_student(file, "2024-10006960", "CS", 2);
    print_student_transcript(file,"2024-10006960","CS", 1);
    // fclose(student_file);

    // assign_semester_modules(file, "2024-10006960","CS",2);

    Node* hashTable[TABLE_SIZE] = {0};
    Node* hashTable1[TABLE_SIZE] = {0};
    Node* hashTable2[TABLE_SIZE] = {0};
    Node* hashTable3[TABLE_SIZE] = {0};

    // add_module(file, hashTable, hashTable1, hashTable2, hashTable3);
    // add_major(file, hashTable);
    
    




    



    


    // loadFromFile(hashTable,"data/module_lookup.dat");
    // display(hashTable);
    // printf("%s", search(hashTable, "CS"));
    // saveToFile(hashTable,"math_modules.dat");
    // delete(hashTable, "AE");
    // saveToFile(hashTable, "data/major_lookup.dat");
    // loadFromFile(hashTable,"data/major_lookup.dat");
    //printf("%s", search(hashTable, "AE"));
    // display(hashTable);
    // saveToFile(hashTable,"data/major_lookup.dat");
    // printf("%s", search(hashTable, "CS105"));
    // fclose(file);
    // return 0;






    // FILE *file = fopen("data/modules.dat", "rb");
    // if (file == NULL) {
    //     printf("Could not open file.\n");
    // }

    // Module module;
    // int module_count = 0;

    // printf("Contents of :\n");
    // while (fread(&module, sizeof(Module), 1, file) == 1) {
    //     printf("Module %d:\n", ++module_count);
    //     printf("  Module Code   : %s\n", module.module_code);
    //     printf("  Module Name   : %s\n", module.module_name);
    //     printf("  Department Code: %s\n", module.dept_code);
    //     printf("  Department Name: %s\n", module.dept_name);
    //     printf("  Professor Code : %s\n", module.prof_code);
    //     printf("  Professor Name : %s\n", module.prof_name);
    //     printf("  Major Code     : %s\n", module.major_code);
    //     printf("  Semester       : %d\n", module.semester);
    //     printf("  Pass Mark      : %.2f\n", module.pass_mark);
    //     printf("\n");
    // }

    return 0;
    fclose(file);
}