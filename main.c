#include "myFuncs.h"
#include "internalCmds.h"
#include "externalCmds.h"

int main (int argc, char *argv[]){

    char buffer[200];
    char motd[] = "\x1b[35m#########################\n\n       LIWEX SHELL       \n\n#########################\n";
    write(1,motd,strlen(motd));
    char *user = getenv("USER");
    char *hostname = getHostname();
    char *pwd = getenv("PWD");
    //char *path = getenv("PATH");
    char prompt[200];
    sprintf(prompt,"%s%s@%s:%s%s%s$ ",COLOR_GREEN,user,hostname,COLOR_BLUE,pwd,COLOR_YELLOW);
    write(1,prompt,strlen(prompt));
    StringArray cmdArray;
    InternalFlags iflags;
    resetFlags(&iflags);
    while(read(0,buffer,200)){

        cmdArray = tokenizar(buffer," ");
        //for(int i=0;i<cmdArray.size;i++) printf("%d.%s\n",i,cmdArray.elements[i]);

        parseInternalCommands(&iflags,&cmdArray);

        executeInternalCommands(&iflags,&cmdArray);
        
        resetFlags(&iflags);

        sprintf(prompt,"\n%s%s@%s:%s%s%s$ ",COLOR_GREEN,user,hostname,COLOR_BLUE,getcwd(NULL, 0),COLOR_YELLOW);
        write(1,prompt,strlen(prompt));
        fflush(stdin);
    }
}