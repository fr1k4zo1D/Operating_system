all:
	touch shared_memory	
	gcc writing_process.c -o wr
	gcc reading_process.c -o rd
	./wr & 
	./rd
	rm -rf rd rw shared_memory

