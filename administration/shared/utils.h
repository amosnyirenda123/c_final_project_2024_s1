#ifndef UTILS_H
#define UTILS_H

#define MAX_RETRIES 3


int get_current_year();
long generate_unique_code();
void string_to_lowercase(char *str);
void string_to_uppercase(char *str);
void pause_execution();
void safe_remove(const char* path);
void delay_operation();
// void create_directory(char name_dir[]);

#endif