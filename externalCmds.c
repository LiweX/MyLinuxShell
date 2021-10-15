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
            executar(path,args);
        }else if(flags->cwd){
            strcpy(path,getenv("PWD"));
            strcat(path,"/");
            strtok(args->elements[0],"/");
            strcat(path,strtok(NULL,"\n"));
            executar(path,args);
        }else{
            for(int i=0;i<paths->size;i++){
                strcpy(path,paths->elements[i]);
                strcat(path,"/");
                strcat(path,args->elements[0]);
                executar(path,args);
            }
        }
        exit(EXIT_SUCCESS);
        break;
    default:
        wait(NULL);
        break;
    } 
}