CFLAGS=-Wall -Werror -pedantic

myshell: main.o myFuncs.o
	gcc $(CFLAGS) -o myshell myFuncs.o main.o

main.o:	main.c
	gcc $(CFLAGS) -c main.c

myFuncs.o: myFuncs.c myFuncs.h
	gcc $(CFLAGS) -c myFuncs.c
	
clean:
	rm -f *.o myshell