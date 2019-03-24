CFLAG = -std=c99

main: main.o
	gcc $(CFLAG) main.o -o main

main.o: main.c Makefile
	gcc $(CFLAG) main.c -c

clean: 
	rm -rf *o

run: 
	sudo ./main "Say something to the kernel from the user space."