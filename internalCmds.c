#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "myFuncs.h"

int parseInternalCommands(char* cmd){

    char *token = strtok(cmd," ");
    fflush(stdout);

    if(strstr(token,"cd")){

        char dir[200];
        token=strtok(NULL,"\n");
        fprintf(stdout,"%s\n",token);
        strcpy(dir,getenv("PWD"));

        if(strstr(token,"..")){
            for(int i=strlen(dir);i>0;i--){
                if(dir[i]=='/'){
                    dir[i]='\0';
                    break;
                } 
            }
            if(chdir(dir) != 0) perror("change to up dir failed");
            else{
                setenv("OLDPWD",getenv("PWD"),1);
                setenv("PWD",dir,1);
            }
        }else
        if(strstr(token,"-")){
            if(chdir(getenv("OLDPWD")) != 0) perror("change to oldpwd failed");
            else{
                setenv("OLDPWD",getenv("PWD"),1);
                setenv("PWD",getenv("OLDPWD"),1);
            } 
        }else
        if(token[0]=='/'){
            if(chdir(token) != 0) perror("change direct directory failed");
            else{
                setenv("OLDPWD",getenv("PWD"),1);
                setenv("PWD",token,1);
            }
        }else{
            strcat(dir,"/");
            strcat(dir,token);
            if(chdir(dir) != 0) perror("change directory failed");
            else{
                setenv("OLDPWD",getenv("PWD"),1);
                setenv("PWD",dir,1);
            }
        }return 0;
    }
    if(strstr(token,"echo")){

        token=strtok(NULL,"\n");
        if(token==NULL) return 0;
        if(token[0]=='$'){
            char *env = (token+1);
            if(getenv(env)==NULL) return 0;
            write(1,getenv(env),strlen(getenv(env)));
        }else{
            write(1,token,strlen(token));
        }
        return 0;
    }
    if(strstr(token,"quit")){
        write(1,"\nBye bye!\n",10);
        exit(EXIT_SUCCESS);
    }
    return 1;
}