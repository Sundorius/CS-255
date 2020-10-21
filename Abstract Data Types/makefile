CFLAGS=-ansi -Wall -pedantic

valgrindList:
	valgrind --tool=memcheck --leak-check=full ./listTest

valgrindHash:
	valgrind --tool=memcheck --leak-check=full ./hashTest

hash: testsymtab.o symtablehash.o
	gcc $(CFLAGS) -o hashTest testsymtab.o symtablehash.o

list: testsymtab.o symtablelist.o
	gcc  $(CFLAGS) -o listTest testsymtab.o symtablelist.o

testsymtab.o: testsymtab.c 
	gcc  $(CFLAGS) -c  testsymtab.c

symtablelist.o: symtablelist.c symtable.h
	gcc  $(CFLAGS)  -c symtablelist.c 

symtablehash.o: symtablehash.c symtable.h
	gcc $(CFLAGS) -c symtablehash.c

clean:
	rm -f *.o listTest hashTest

