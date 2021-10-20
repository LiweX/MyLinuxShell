CFLAGS=-Wall -Werror -pedantic

myshell: main.o myFuncs.o internalCmds.o externalCmds.o batchFile.o signals.o pipes.o
	gcc $(CFLAGS) -o myshell myFuncs.o internalCmds.o externalCmds.o batchFile.o signals.o pipes.o main.o

main.o:	main.c
	gcc $(CFLAGS) -c main.c

myFuncs.o: myFuncs.c myFuncs.h
	gcc $(CFLAGS) -c myFuncs.c

internalCmds.o: internalCmds.c internalCmds.h
	gcc $(CFLAGS) -c internalCmds.c

externalCmds.o: externalCmds.c externalCmds.h
	gcc $(CFLAGS) -c externalCmds.c

batchFile.o: batchFile.c batchFile.h
	gcc $(CFLAGS) -c batchFile.c

signals.o: signals.c signals.h
	gcc $(CFLAGS) -c signals.c

pipes.o: pipes.c pipes.h
	gcc $(CFLAGS) -c pipes.c

clean:
	rm -f *.o myshell