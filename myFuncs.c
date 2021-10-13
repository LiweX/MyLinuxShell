#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>



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