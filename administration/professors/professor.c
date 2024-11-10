#include "professor.h"

#define MAX_WORD_LENGTH 80

typedef struct DateOfBirth{
    int month;
    int year;
    int day;
}DateOfBirth;

typedef struct Professor{
    char l_name[MAX_LENGTH];
    char f_name[MAX_LENGTH];
    DateOfBirth s_date_of_birth;
    char gender;
    long code;
    char department[MAX_LENGTH];
    char institutional_email[MAX_LENGTH];
}Professor;