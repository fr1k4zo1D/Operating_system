all: main.o test start clean
main.o:main.c
	gcc -c -o main.o main.c
test: main.o
	gcc -o test main.o
start:
	./test
clean:
	rm -rf test main.o
