#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int externalCommand(char* cmd){

    char *token = strtok(cmd," ");
    char **args = (char**)malloc(sizeof(char*));
    int n_args=0;
    fprintf(stdout,"%d diks",n_args);

    while(token!=NULL){
    if(n_args!=0) args = (char**)realloc(args,sizeof(char*)*(n_args+1)); 
    args[n_args]=token;
    n_args++;
    token=strtok(NULL," ");
    }
    args = (char**)realloc(args,sizeof(char*)*(n_args+1));
    args[n_args]=NULL;
    
    char *binaryPath = "/bin/";
    strcat(binaryPath,args[0]);
    fprintf(stdout,"%s",binaryPath);

     
    if(fork()==0){

        execv(binaryPath,args);
        exit(EXIT_SUCCESS);

    }else{
        wait(NULL);
        return 0;
    }
    return 0;
}