#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include "administration/students/student.h"
#include "administration/majors/major.h"
#include "administration/majors/module.h"
#include "administration/maps/map.h"


typedef struct {
    char modules_path[100];
    char students_path[100];
    char major_path[100];
    const char* dir;
} Config;

void print_menu();
void about_app();
void start_application();
void switch_option(int option);
FILE* open_file(const char* filename, const char* mode);
void close_file(FILE* fptr);
void initialize_paths(Config* config);
void wait_press_enter();


#endif