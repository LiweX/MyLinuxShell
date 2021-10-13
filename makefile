CFLAGS=-Wall -Werror -pedantic

myshell: main.o myFuncs.o internalCmds.o
	gcc $(CFLAGS) -o myshell myFuncs.o internalCmds.o main.o

main.o:	main.c
	gcc $(CFLAGS) -c main.c

myFuncs.o: myFuncs.c myFuncs.h
	gcc $(CFLAGS) -c myFuncs.c

internalCmds.o: internalCmds.c internalCmds.h
	gcc $(CFLAGS) -c internalCmds.c

clean:
	rm -f *.o myshell