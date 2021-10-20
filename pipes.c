#include "myFuncs.h"

void usePipes(char * commands){
    char aux[400];
    StringArray pipeArray;
    pipeArray = tokenizar(strcpy(aux,commands),"|");
    // write(1,"Las instrucciones a pipear son:\n",31);
    // write(1,commands,strlen(commands));
    // for(int i=0;i<pipeArray.size;i++){
    //     write(1,pipeArray.elements[i],strlen(pipeArray.elements[i]));
    //     write(1,"\n",1);
    // }
    pid_t pid;
    int fd[2];
    StringArray entrada = tokenizar(pipeArray.elements[0]," ");
    StringArray salida = tokenizar(pipeArray.elements[1]," ");

    pipe(fd);
    pid = fork();

    if(pid==0)
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execvp(entrada.elements[0], entrada.elements);
        fprintf(stderr, "Failed to execute '%s'\n", entrada.elements[0]);
        exit(1);
    }
    else
    { 
        pid=fork();

        if(pid==0)
        {
            dup2(fd[0], STDIN_FILENO);
            close(fd[1]);
            close(fd[0]);
            execvp(salida.elements[0], salida.elements);
            fprintf(stderr, "Failed to execute '%s'\n", salida.elements[0]);
            exit(1);
        }
        else
        {
            int status;
            close(fd[0]);
            close(fd[1]);
            waitpid(pid, &status, 0);
        }
    }

}