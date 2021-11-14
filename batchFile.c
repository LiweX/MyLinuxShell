#include "myFuncs.h"
#include "externalCmds.h"
#include "internalCmds.h"


void batchFile(InternalFlags *flags,StringArray *paths,char* fileName){

    char filePath[400];
    char buffer[400];
    char aux[400];
    char prompt[500];
    strcpy(filePath,getcwd(NULL,0));
    strcat(filePath,"/");
    strcat(filePath,fileName);
    FILE *file = openFile(filePath);
    StringArray cmdArray;

    while(fgets(buffer,400,file)!=NULL){
        sprintf(prompt,"\n%s%s@%s:%s%s%s$ %s",COLOR_GREEN,getenv("USER"),getHostname(),COLOR_BLUE,getcwd(NULL, 0),COLOR_YELLOW,buffer);
        write(1,prompt,strlen(prompt));
        cmdArray = tokenizar(strcpy(aux,buffer)," ");
        parseCommands(&flags,&cmdArray);
        if(flags->pipe) usePipes(strcpy(aux,buffer));
        else if(flags->externo) externalCommand(&cmdArray,&paths,&flags);
        else executeInternalCommands(&flags,&cmdArray);
        resetFlags(&flags);
        
    }
    exit(EXIT_SUCCESS);
}