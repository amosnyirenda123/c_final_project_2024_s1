#ifndef TOAST_H
#define TOAST_H


#include <stdio.h>

#define MESSAGE_LENGTH 300
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define PINK "\033[1;35m"

typedef enum {
    SUCCESS,
    ERROR,
    NOT_FOUND,
    WARNING,
    INFO,
    RES
} MessageType;

void printMessage(MessageType type, const char *message);


#endif