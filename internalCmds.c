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
    if(strstr(token,"echo")){
        
        if(token!=NULL){
            fflush(stdout);
            token=strtok(NULL,"\n");
            write(1,token,strlen(token));
        }
        return 0;
    }
    return 1;
}