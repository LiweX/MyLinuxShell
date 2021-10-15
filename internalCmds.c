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
        return;
    }
    if(strcmp(cmds->elements[0],"echo")==0){
        flags->echo=1;
        return;    
    }
    if(strcmp(cmds->elements[0],"clr")==0) {
        flags->clr=1;
        return;
    }
    if(strcmp(cmds->elements[0],"quit")==0) {
        flags->quit=1;
        return;
    }
    flags->externo=1;
    if(strncmp(cmds->elements[0],"/",1)==0) flags->absoluto=1;
    if(strncmp(cmds->elements[0],".",1)==0) flags->relativo=1;
    if(strcmp(cmds->elements[(cmds->size-1)],"&")==0){
      cmds->size-=1; 
      flags->background=1; 
    } 
}

void executeInternalCommands(InternalFlags * flags,StringArray * cmds){
    if(flags->cd){
        char dir[200];
        if(flags->cd_guion){
            if(chdir(getenv("OLDPWD")) != 0) perror("change to oldpwd failed");
            else{
                setenv("OLDPWD",getenv("PWD"),1);
                setenv("PWD",getcwd(NULL, 0),1);
            }return;
        }

        if(flags->cd_direct){
            if(chdir(cmds->elements[1]) != 0) perror("change direct directory failed");
            else{
                setenv("OLDPWD",getenv("PWD"),1);
                setenv("PWD",cmds->elements[1],1);
            }return;
        }

        strcpy(dir,getcwd(NULL, 0));
        strcat(dir,"/");
        strcat(dir,cmds->elements[1]);
        if(chdir(dir) != 0) perror("change directory failed");
        else{
                setenv("OLDPWD",getenv("PWD"),1);
                setenv("PWD",getcwd(NULL, 0),1);
        }return;
    }

    if(flags->echo){
        char string[300]="";
        for(int i=1;i<cmds->size;i++){
            if(strncmp(cmds->elements[i],"$",1)==0) strcat(string,getenv((cmds->elements[i]+1)));
            else strcat(string,cmds->elements[i]);
            strcat(string," ");    
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
