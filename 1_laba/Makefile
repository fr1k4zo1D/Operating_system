all: main.o test start clean
main.o:main.cpp
	gcc -c -o main.o main.cpp
test: test
	gcc -o test main.o 
start:
	./test
clean: main.o
	rm -rf  main.o test
