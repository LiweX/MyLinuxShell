Laboratorio N4/5
# MyShell basic & advanced
### SOI - FCEFyN - UNC - 2021


## Desarrollo
Para desarrolo de esta shell se utilizan dos estructuras.
La primera para facilitar el manejo de las cadenas ingresadas por teclado.
```
typedef struct StringArray
{
    int size;
    char ** elements;
} StringArray;
```
La funcion `StringArray tokenizar(char * string, char * delimitador)`  se encarga de crear un arreglo dinamico con las cadenas separadas por el caracter delimitador. Se guarda la direccion del arreglo y la cantidad de elementos del arreglo en la estructura. De esta forma es mas facil recorrer con un `for` las palabras de las cadenas ingresadas por el usuario.
La otra estructura se utiliza como flag
```
typedef struct InternalFlags
{
    int cd;
    int echo;
    int clr;
    int echo_env;
    int cd_direct;
    int cd_guion;
    int quit;
    int externo;
    int absoluto;
    int relativo;
    int background;
    int pipe;
    int IOredirection;

} InternalFlags;
```
La funcion `resetFlags(InternalFlags *flags)` se encarga de poner estas flags en 0.
La funcion `parseCommands(InternalFlags * flags,StringArray * cmds)` recorre la cadena ingresada y si encuentra una palabra clave o un simbolo especifico levanta la flag correspondiente a dicho evento seteando su valor a 1. Luego estas flags seran analizadas para saber que accion tomar.
### Funcionamiento de la shell.
```
...
while(read(0,buffer,400)){   //leer la entrada del usuario
            cmdArray = tokenizar(strcpy(aux,buffer)," ");                   //separar la cadena por espacios
            parseCommands(&flags,&cmdArray);                                //analizar la cadena en busqueda de palabras o simbolos clave.
            if(flags.pipe) usePipes(strcpy(aux,buffer));                    //accion a tomar si hay pipe
            else if(flags.externo) externalCommand(&cmdArray,&pathArray,&flags);       //accion para ejecutar comando externo.
            else executeInternalCommands(&flags,&cmdArray);                            //accion para ejecutar comando externo.
            resetFlags(&flags);                                                        //poner las flags en cero.
            sprintf(prompt,"\n%s%s@%s:%s%s%s$ ",COLOR_GREEN,user,hostname,COLOR_BLUE,getcwd(NULL, 0),COLOR_YELLOW); //volver a armar el prompt
            write(1,prompt,strlen(prompt));                                                                         // impirimr el prompt
        }
...
```

### Comandos internos.
Para los comandos internos: `cd`, `echo`, `clr` y `quit`, la estructura de las flags facilita la toma de deciciones.
```
void executeInternalCommands(InternalFlags * flags,StringArray * cmds){
    if(flags->cd){
        char dir[200];
        if(flags->cd_guion){
            if(chdir(getenv("OLDPWD")) != 0) perror("change to oldpwd failed");
            else{
                setenv("OLDPWD",getenv("PWD"),1);
                setenv("PWD",getcwd(NULL, 0),1);
            }return;
        }

        if(flags->cd_direct){
            if(chdir(cmds->elements[1]) != 0) perror("change direct directory failed");
            else{
                setenv("OLDPWD",getenv("PWD"),1);
                setenv("PWD",cmds->elements[1],1);
            }return;
        }

        strcpy(dir,getcwd(NULL, 0));
        strcat(dir,"/");
        strcat(dir,cmds->elements[1]);
        if(chdir(dir) != 0) perror("change directory failed");
        else{
                setenv("OLDPWD",getenv("PWD"),1);
                setenv("PWD",getcwd(NULL, 0),1);
        }return;
    }

    if(flags->echo){
        char string[300]="";
        for(int i=1;i<cmds->size;i++){
            if(strncmp(cmds->elements[i],"$",1)==0) strcat(string,getenv((cmds->elements[i]+1)));
            else strcat(string,cmds->elements[i]);
            strcat(string," ");    
        }
        write(1,string,strlen(string));
        return;
    }

    if(flags->clr){
        system("clear");
        return;
    }

    if(flags->quit){
        write(1,"Bye bye!\n",10);
        exit(EXIT_SUCCESS);
    }
}
```

### Program invocation
Si no hay comandos internos en la cadena ingresada por el usuario se usa la funcion `externalCommand(StringArray *args,StringArray *paths,InternalFlags *flags)`
Dicha funcion tiene un arreglo con las rutas en la variable de entorno `PATH` separadas por `:` ya que si no se proporciona la direccion absoluta del programa a ejectuar se debe buscar en este arreglo.
```
void externalCommand(StringArray *args,StringArray *paths,InternalFlags *flags){
    
    char path[200];
    int ret = fork();
    switch (ret){
    case -1:
        perror("fork failed");
        exit(EXIT_FAILURE);
        break;
    case 0:
        switchOnSignals();
        if(flags->absoluto){
            strcpy(path,args->elements[0]);
            execv(path,args->elements);
        }else if(flags->relativo){
            strcpy(path,getenv("PWD"));
            strcat(path,"/");
            strtok(args->elements[0],"/");
            strcat(path,strtok(NULL,"\n"));
            execv(path,args->elements);
        }else{
            if(flags->background) args->elements[args->size-1] = NULL;
            for(int i=0;i<paths->size;i++){
                strcpy(path,paths->elements[i]);
                strcat(path,"/");
                strcat(path,args->elements[0]);
                execv(path,args->elements);
            }
        }
        exit(EXIT_SUCCESS);
        break;
    default:
        if(flags->background){
            char bg[20]="";
            sprintf(bg,"%d",ret);
            write(1,bg,20);
        } 
        else{
            wait(NULL);
        }
        break;
    }
}
```

### Batch file
Si myshell se ejecuta con un argumento, dicho argumento sera el nombre del batchfile a ejecutar, el cual debe estar en el mismo directorio en el que se encuentra el ejecutable. Las instrucciones del archivo deben estan separadas por enters.
```
if(argc==2){

        batchFile(&flags,&pathArray,argv[1]);
```
La funcion batchFile tiene una funcionalidad parecida al main de la shell. La diferencia es que en vez de leer las instrucciones por el teclado, las toma linea por linea del batchfile.
```
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
```

### Background execution
Si se usa `&` al final de la linea el programa se ejecuta en segundo plano
```
...
default:
        if(flags->background){
            char bg[20]="";
            sprintf(bg,"%d",ret);
            write(1,bg,20);
        } 
        else{
            wait(NULL);
        }
        break;
...
```
La flag ayuda a determinar si se encuentra el `&` y lo unico que cambia es que el programa padre no espera al hijo para volver a la shell.

### Signal Handling
Para el manejo de señales existen las siguientes funciones.
```
void switchOffSignals(void){
    signal(SIGINT,SIG_IGN);
    signal(SIGTSTP,SIG_IGN);
    signal(SIGQUIT,SIG_IGN);
}
void switchOnSignals(void){
    signal(SIGINT,SIG_DFL);
    signal(SIGTSTP,SIG_DFL);
    signal(SIGQUIT,SIG_DFL); 
}
```
Estas funciones "prenden y apagan" las señales dependiendo si el proceso es hijo o padre. De esta forma un proceso hijo puede recibir una señal para terminar con la ejecucion y volver al shell, mientras que el proceso padre las ignora.

### Pipes
Solo se permiten pipes simples.
Si se detecta el simbolo `|` se levanta la flag de pipes y el main llamara la funcion `usePipes(char * commands)`
La funcion separa la cadena ingresada con el caracter `|`, se crea el pipe y asignan los comandos de entrada y salida correspondientes.
```
void usePipes(char * commands){
    char aux[400];
    StringArray pipeArray;
    pipeArray = tokenizar(strcpy(aux,commands),"|");
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
```
¿Dónde se encuentran los pipes en el filesystem, qué atributos tienen?
Rta here.
### I/O redirection
