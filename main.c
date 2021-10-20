#include "myFuncs.h"
#include "internalCmds.h"
#include "externalCmds.h"
#include "batchFile.h"
#include "pipes.h"
#include "signals.h"

int main (int argc, char *argv[]){

    char prompt[400];
    char path[400];
    char motd[] = "\x1b[35m#########################\n\n       LIWEX SHELL       \n\n##########################\n";
    write(1,motd,strlen(motd));
    char *user = getenv("USER");
    char *hostname = getHostname();
    char *pwd = getenv("PWD");
    strcpy(path,getenv("PATH"));
    sprintf(prompt,"%s%s@%s:%s%s%s$ ",COLOR_GREEN,user,hostname,COLOR_BLUE,pwd,COLOR_YELLOW);
    StringArray cmdArray;
    StringArray pathArray;
    pathArray=tokenizar(path,":");
    InternalFlags flags;
    resetFlags(&flags);
    switchOffSignals();

    if(argc==2){

        batchFile(&flags,&pathArray,argv[1]);

    }else if(argc<2){
        char buffer[400];
        write(1,prompt,strlen(prompt));

        while(read(0,buffer,200)){
            cmdArray = tokenizar(buffer," ");
            parseCommands(&flags,&cmdArray);
            if(flags.pipe) usePipes(buffer);
            executeInternalCommands(&flags,&cmdArray);
            if(flags.externo) externalCommand(&cmdArray,&pathArray,&flags);
            resetFlags(&flags);
            sprintf(prompt,"\n%s%s@%s:%s%s%s$ ",COLOR_GREEN,user,hostname,COLOR_BLUE,getcwd(NULL, 0),COLOR_YELLOW);
            write(1,prompt,strlen(prompt));
        }
    }else{
          write(1,"invalid entry\n",18);
          exit(EXIT_FAILURE);
    }
  
}