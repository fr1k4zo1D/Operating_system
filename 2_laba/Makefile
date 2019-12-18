all:test start clean
test: main.o
		gcc -o test main.cpp
start:
	./test
clean: main.o
	rm -rf main.o test
