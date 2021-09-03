output: main.o filehandling.o | builddir
	gcc build/main.o build/filehandling.o -o build/pbf

main.o: src/main.c include/filehandling.h | builddir
	gcc -c src/main.c -o build/main.o

filehandling.o: src/filehandling.c include/filehandling.h
	gcc -c src/filehandling.c -o build/filehandling.o

builddir: 
	mkdir -p build 

clean: | builddir
	rm -r build/