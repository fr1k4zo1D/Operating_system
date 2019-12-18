all: test start clean
test: test
	gcc main.o -o test 
main.o:
	gcc -c main.cpp
start:
	./test
clean: main.o
	rm -rf  test
