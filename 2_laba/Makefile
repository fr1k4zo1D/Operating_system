all:test clean
test: main.o
		gcc -o test main.o
main.o:	main.cpp
		gcc -c -o main.o main.cpp
clean: main.o
	rm -rf main.o 
