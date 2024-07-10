all: main clean

main: main.c avl.o bst.o fileio.o stack.o queue.o
	@gcc -g main.c avl.o bst.o fileio.o stack.o queue.o -o main -lm
	@echo "main is build with debug flag"

avl.o: avl.c
	gcc -c avl.c

bst.o: bst.c
	gcc -c bst.c

fileio.o: fileio.c
	gcc -c fileio.c

stack.o: stack.c
	gcc -c stack.c

queue.o: queue.c
	gcc -c queue.c

clean:
	rm *.o
