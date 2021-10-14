#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "myFuncs.h"

FILE* openFile(char* path){
    FILE *file;
    file = fopen(path,"r");
    if(file==NULL){
        fprintf(stdout,"Error al abrir el archivo: %s",path);
        exit(EXIT_FAILURE);
    }
    return file;
}

char* getHostname(){
    FILE *file = openFile("/proc/sys/kernel/hostname");
    char *buffer = malloc(100*sizeof(char));
    fgets(buffer,100,file);
    buffer = strtok(buffer,"\n");
    return buffer;
}

char* toUpperCase(char* word){

    for(int i=0; word[i]!='\0'; i++)
    {
        if(word[i]>='a' && word[i]<='z')
        {
            word[i] = word[i] - 32;
        }
    }
    return word;
}

StringArray tokenizar(char * string, char * delimitador){

    char **tokens = (char**)malloc(sizeof(char*));
    char *token = strtok(string,delimitador);
    int n_tokens=0;
    while(token!=NULL){
        if(tokens!=0) tokens = (char**)realloc(tokens,sizeof(char*)*(n_tokens+1)); 
        tokens[n_tokens]=token;
        n_tokens++;
        token=strtok(NULL,delimitador);
    }
    token = strtok(tokens[n_tokens-1],"\n");
    tokens[n_tokens-1] = token;
    StringArray array;
    array.elements=tokens;
    array.size=n_tokens;
    return array;
}

void resetFlags(InternalFlags *flags){
    flags->cd=0;
    flags->cd_direct=0;
    flags->cd_guion=0;
    flags->clr=0;
    flags->echo=0;
    flags->echo_env=0;
    flags->quit=0;
}