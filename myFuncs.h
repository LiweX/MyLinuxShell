#ifndef MYFUNCS_H
#define MYFUNCS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN "\x1b[36m"
#define COLOR_RESET "\x1b[0m"
typedef struct StringArray
{
    int size;
    char ** elements;
} StringArray;
typedef struct InternalFlags
{
    int cd;
    int echo;
    int clr;
    int echo_env;
    int cd_direct;
    int cd_guion;
    int quit;
    int externo;
    int absoluto;
    int relativo;
    int background;

} InternalFlags;

FILE* openFile(char*);
char* getHostname();
char* toUpperCase(char* word);
StringArray tokenizar(char * string, char * delimitador);
void resetFlags(InternalFlags *flags);
#endif