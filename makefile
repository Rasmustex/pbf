installdir = ~/.local/bin
cc = gcc
builddir = build

output: main.o filehandling.o | builddirec
	$(cc) $(builddir)/main.o $(builddir)/filehandling.o -o $(builddir)/pbf

main.o: src/main.c include/pbf.h | builddirec
	$(cc) -c src/main.c -o $(builddir)/main.o

filehandling.o: src/filehandling.c include/pbf.h
	$(cc) -c src/filehandling.c -o $(builddir)/filehandling.o

builddirec: 
	mkdir -p $(builddir) 

clean: | builddirec
	rm -r $(builddir)

install: output 
	cp $(builddir)/pbf $(installdir)