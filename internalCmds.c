#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "myFuncs.h"

int parseInternalCommands(char* cmd){

    char *token = strtok(cmd," ");

    if(strstr(token,"quit")){
        write(0,"\nBye bye!\n",10);
        exit(EXIT_SUCCESS);
    }
    if(strstr(token,"cd")){
        token = strtok(NULL," ");
        if(token!=NULL){
        }
    }
    return 1;
}