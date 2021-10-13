#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int externalCommand(char* cmd){

    if(fork()==0){
        
    }
    wait(NULL);
    return 0;
}