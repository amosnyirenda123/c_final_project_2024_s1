#include <stdlib.h>
#include "administration/students/student.h"
#include "administration/majors/major.h"
#include "administration/majors/module.h"


int main(void)
{
    FILE *student_file;
    student_file = fopen("students.bin", "rb+");

    if(student_file == NULL) {
        printf("Failed to open file in write mode");
        return 1;
    }
    // display_all_students(student_file); 
    // add_student(student_file);
    // find_student_and_print_details(student_file, "2024-10011529");
    // update_student_details(student_file, "2024-10022609", "GI");
    // allocate_marks_to_student(student_file, "2024-10022609", "GI", 1);
    print_student_transcript(student_file,"2024-10022609","GI", 1);
    // fclose(student_file);
    return 0;
}