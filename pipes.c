#include "myFuncs.h"

void usePipes(char * commands){
    char aux[400];
    StringArray pipeArray;
    pipeArray = tokenizar(strcpy(aux,commands),"|");
    write(1,"Las instrucciones a pipear son:\n",31);
    write(1,commands,strlen(commands));
    for(int i=0;i<pipeArray.size;i++){
        write(1,pipeArray.elements[i],strlen(pipeArray.elements[i]));
        write(1,"\n",1);
    }
}