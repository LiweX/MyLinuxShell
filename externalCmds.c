#include "myFuncs.h"

void externalCommand(StringArray *args,StringArray *paths,InternalFlags *flags){

    int ret = fork();
    char path[200];
    switch (ret){
    case -1:
        perror("fork failed");
        exit(EXIT_FAILURE);
        break;
    case 0:
        if(flags->absoluto){
            
        }
        if(args->size==1){
            for(int i=0;i<paths->size;i++){
                strcpy(path,paths->elements[i]);
                strcat(path,"/");
                strcat(path,args->elements[0]);
                execl(path,args->elements[0],NULL);
            }
        }
        if(args->size==2){
            printf("%s %s\n",args->elements[0],args->elements[1]);
            for(int i=0;i<paths->size;i++){
                strcpy(path,paths->elements[i]);
                strcat(path,"/");
                strcat(path,args->elements[0]);
                execl(path,args->elements[0],args->elements[1],NULL);
            }
        }
        if(args->size==3){
            for(int i=0;i<paths->size;i++){
                strcpy(path,paths->elements[i]);
                strcat(path,"/");
                strcat(path,args->elements[0]);
                execl(path,args->elements[0],args->elements[1],args->elements[2],NULL);
            }
        }
        if(args->size==4){
            for(int i=0;i<paths->size;i++){
                strcpy(path,paths->elements[i]);
                strcat(path,"/");
                strcat(path,args->elements[0]);
                execl(path,args->elements[0],args->elements[1],args->elements[2],args->elements[3],NULL);
            }
        }
        if(args->size==5){
            for(int i=0;i<paths->size;i++){
                strcpy(path,paths->elements[i]);
                strcat(path,"/");
                strcat(path,args->elements[0]);
                execl(path,args->elements[0],args->elements[1],args->elements[2],args->elements[3],args->elements[4],NULL);
            }
        }
        exit(EXIT_SUCCESS);
        break;    
    default:
        wait(NULL);
        break;
    } 

}