#include "myFuncs.h"

void externalCommand(StringArray *args){

    int ret = fork();
    switch (ret){
    case -1:
        perror("fork failed");
        exit(EXIT_FAILURE);
        break;
    case 0:
        exit(EXIT_SUCCESS);
        break;    
    default:
        wait(NULL);
        break;
    } 

    // char *token = strtok(cmd," ");
    // char **args = (char**)malloc(sizeof(char*));
    // char **paths = (char**)malloc(sizeof(char*));
    // int n_args=0;
    // int n_paths=0;
    
    // while(token!=NULL){
    //     if(n_args!=0) args = (char**)realloc(args,sizeof(char*)*(n_args+1)); 
    //     args[n_args]=token;
    //     n_args++;
    //     token=strtok(NULL," ");
    // }
    // for(int j=0;j<n_args;j++) printf("%s\n",args[j]);
    // token = strtok(args[n_args-1],"\n");
    // args[n_args-1] = token;

    // token=strtok(getenv("PATH"),":");
    // while(token!=NULL){
    //     if(n_paths!=0) paths = (char**)realloc(paths,sizeof(char*)*(n_paths+1));
    //     paths[n_paths]=token;
    //     n_paths++;
    //     token=strtok(NULL,":");
    // }
    // for(int j=0;j<n_paths;j++) printf("%s\n",paths[j]);
    // token = strtok(paths[n_paths-1],"\n");
    // paths[n_paths-1] = token;
    // char path[200];

    //for(int j=0;j<n_args;j++) printf("%s\n",args[j]);   //debugging commands
    //for(int j=0;j<n_paths;j++) printf("%s\n",paths[j]);
    

    // free(args);
    // free(paths);
}