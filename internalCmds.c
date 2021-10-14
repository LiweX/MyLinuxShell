#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "myFuncs.h"

void parseInternalCommands(InternalFlags * flags,StringArray * cmds){

    if(strcmp(cmds->elements[0],"cd")==0 && cmds->size==2){
        flags->cd=1;
        if(strncmp(cmds->elements[1],"/",1)==0) flags->cd_direct=1;
        if(strcmp(cmds->elements[1],"-")==0) flags->cd_guion=1;
    }
    if(strcmp(cmds->elements[0],"echo")==0){
        flags->echo=1;
        for(int i=1;i<cmds->size;i++){
            if(strncmp(cmds->elements[i],"$",1)==0){
                flags->echo_env=0;
                break;
            } 
        }
    }
    if(strcmp(cmds->elements[0],"clr")==0) flags->clr=1;
    if(strcmp(cmds->elements[0],"quit")==0) flags->quit=1;
}

void executeInternalCommands(InternalFlags * flags,StringArray * cmds){
    
    if(flags->cd){

        if(flags->cd_guion){
            if(chdir(getenv("OLDPWD")) != 0) perror("change to oldpwd failed");
            else{
                char *tmp = getenv("OLDPWD");
                setenv("OLDPWD",getenv("PWD"),1);
                setenv("PWD",tmp,1);
            }return;
        }

        if(flags->cd_direct){
            if(chdir(cmds->elements[1]) != 0) perror("change direct directory failed");
            else{
                setenv("OLDPWD",getenv("PWD"),1);
                setenv("PWD",cmds->elements[1],1);
            }return;
        }

        char* dir = getcwd(NULL, 0);
        strcat(dir,"/");
        strcat(dir,cmds->elements[1]);
        if(chdir(dir) != 0) perror("change directory failed");
        else{
                setenv("OLDPWD",getenv("PWD"),1);
                setenv("PWD",dir,1);
        }return;
    }

    if(flags->echo){
        char string[300];
        strcpy(string,cmds->elements[1]);
        for(int i=2;i<cmds->size;i++){
            if(strncmp(cmds->elements[i],"$",1)==0){
                char *env=getenv((cmds->elements[i]+1));
                cmds->elements[i]=env;
            }
            strcat(string," ");
            strcat(string,cmds->elements[i]);
        }
        write(1,string,strlen(string));
        return;
    }

    if(flags->clr){
        system("clear");
        return;
    }

    if(flags->quit){
        write(1,"Bye bye!\n",10);
        exit(EXIT_SUCCESS);
    }
}    
