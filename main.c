#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "myFuncs.h"
#include "internalCmds.h"

int main (int argc, char *argv[]){

    char buffer[200];
    char motd[] = "#########################\n\n       LIWEX SHELL       \n\n#########################\n";
    write(1,motd,strlen(motd));
    char *user = getenv("USER");
    char *hostname = getHostname();
    char *pwd = getenv("PWD");
    char prompt[200];
    sprintf(prompt,"\n%s@%s:%s$ ",user,hostname,pwd);
    write(1,prompt,strlen(prompt));

    while(read(0,buffer,200)){

        parseInternalCommands(buffer);

        write(1,prompt,strlen(prompt));
    }

}