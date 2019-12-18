all: test start clean

main.o:main.cpp
	gcc -c -o main.o main.cpp
test: main.o
	gcc -o test main.o
start:
	./test
clean: main.o
	rm -rf main.o test
