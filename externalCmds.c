#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int externalCommand(char* buffer){
    char cmd[200];
    strcpy(cmd,buffer);
    char *token = strtok(cmd," ");
    char **args = (char**)malloc(sizeof(char*));
    int n_args=0;
    
    while(token!=NULL){
    if(n_args!=0) args = (char**)realloc(args,sizeof(char*)*(n_args+1)); 
    args[n_args]=token;
    n_args++;
    token=strtok(NULL," ");
    }
    //for(int j=0;j<n_args;j++) printf("%s\n",args[j]);   //debugging commands
    char binaryPath[20] = "/bin/";
    strcat(binaryPath,args[0]);
    int ret = fork();
    switch (ret)
    {
    case -1:
        perror("fork failed");
        exit(EXIT_FAILURE);
        break;
    case 0:
        //printf("%s\n",binaryPath);
        //for(int j=0;j<n_args;j++) printf("%s\n",args[j]);
        execv(binaryPath,args);
        break;    
    default:
        wait(NULL);
        break;
    } 
    free(args);
    return 0;
}