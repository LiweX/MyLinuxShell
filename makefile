CFLAGS=-Wall -Werror -pedantic

myshell: main.o myFuncs.o internalCmds.o externalCmds.o
	gcc $(CFLAGS) -o myshell myFuncs.o internalCmds.o externalCmds.o main.o

main.o:	main.c
	gcc $(CFLAGS) -c main.c

myFuncs.o: myFuncs.c myFuncs.h
	gcc $(CFLAGS) -c myFuncs.c

internalCmds.o: internalCmds.c internalCmds.h
	gcc $(CFLAGS) -c internalCmds.c

externalCmds.o: externalCmds.c externalCmds.h
	gcc $(CFLAGS) -c externalCmds.c

clean:
	rm -f *.o myshell