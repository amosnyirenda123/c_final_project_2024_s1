#include "toast.h"


void printMessage(MessageType type, const char *message) {
    switch (type) {
        case SUCCESS:
            printf(GREEN "[SUCCESS]: %s" RESET, message);
            break;
        case ERROR:
            printf(RED "[ERROR]: %s" RESET, message);
            break;
        case NOT_FOUND:
            printf(YELLOW "[NOT_FOUND]: %s\n" RESET, message);
            break;
        case WARNING:
            printf(PINK "[WARNING]: %s\n" RESET, message);
            break;
        case INFO:
            printf("[INFO]: %s", message); 
            break;
        case RES:
            printf(BLUE "[RES]: %s" RESET, message);
            break;
        default:
            printf("[UNKNOWN]: %s", message);
            break;
    }
}