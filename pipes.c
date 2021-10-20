#include "myFuncs.h"

void usePipes(char * commands){
    StringArray pipeArray;
    pipeArray = tokenizar(commands,"|");
    write(1,"Las instrucciones a pipear son:\n",50);
    for(int i=0;i<pipeArray.size;i++){
        write(1,pipeArray.elements[i],strlen(pipeArray.elements[i]));
        write(1,"\n",1);
    }
}