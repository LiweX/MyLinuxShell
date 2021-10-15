#include "myFuncs.h"

void externalCommand(StringArray *args,StringArray *paths,InternalFlags *flags){
    
    char path[200];
    
    int ret = fork();
    switch (ret){
    case -1:
        perror("fork failed");
        exit(EXIT_FAILURE);
        break;
    case 0:
        if(flags->absoluto){
            strcpy(path,args->elements[0]);
            execv(path,args->elements);
        }else if(flags->relativo){
            strcpy(path,getenv("PWD"));
            strcat(path,"/");
            strtok(args->elements[0],"/");
            strcat(path,strtok(NULL,"\n"));
            execv(path,args->elements);
        }else{
            for(int i=0;i<paths->size;i++){
                strcpy(path,paths->elements[i]);
                strcat(path,"/");
                strcat(path,args->elements[0]);
                execv(path,args->elements);
            }
        }
        exit(EXIT_SUCCESS);
        break;
    default:
        if(flags->background){
            printf("Background\n");
        } 
        else{
            wait(NULL);
        }
        break;
    } 
}