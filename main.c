#include "myFuncs.h"
#include "internalCmds.h"
#include "externalCmds.h"

int main (int argc, char *argv[]){

    char prompt[400];
    char path[400];
    char buffer[400];
    char motd[] = "\x1b[35m#########################\n\n       LIWEX SHELL       \n\n#########################\n";
    write(1,motd,strlen(motd));
    char *user = getenv("USER");
    char *hostname = getHostname();
    char *pwd = getenv("PWD");
    strcpy(path,getenv("PATH"));
    sprintf(prompt,"%s%s@%s:%s%s%s$ ",COLOR_GREEN,user,hostname,COLOR_BLUE,pwd,COLOR_YELLOW);
    write(1,prompt,strlen(prompt));
    StringArray cmdArray;
    StringArray pathArray;
    pathArray=tokenizar(path,":");
    InternalFlags flags;
    resetFlags(&flags);
    
    while(read(0,buffer,200)){

        cmdArray = tokenizar(buffer," ");

        parseInternalCommands(&flags,&cmdArray);

        executeInternalCommands(&flags,&cmdArray);

        if(flags.externo){
            externalCommand(&cmdArray,&pathArray,&flags);
        }

        resetFlags(&flags);

        sprintf(prompt,"\n%s%s@%s:%s%s%s$ ",COLOR_GREEN,user,hostname,COLOR_BLUE,getcwd(NULL, 0),COLOR_YELLOW);
        write(1,prompt,strlen(prompt));
        fflush(stdin);
    }
}