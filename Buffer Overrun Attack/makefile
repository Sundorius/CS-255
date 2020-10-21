CFLAGS=-ansi -Wall -pedantic

make all: createdata3.c createdata6.c
	gcc  $(CFLAGS) -o createdata3 createdata3.c
	gcc  $(CFLAGS) -o createdata6 createdata6.c

make3: createdata3.c
	gcc  $(CFLAGS) -o createdata3 createdata3.c
	
make6: createdata6.c
	gcc  $(CFLAGS) -o createdata6 createdata6.c



make clean:
	rm -f createdata3 createdata6 data3 data6

