#Owner: Ari Iramanesh
#cruzID: 1628897
#class: 12B
#creates object files for compiling listTest. Ingredients are list_funcs.c and list.h

listTest: list_funcs.o main.o
	gcc -o listTest list_funcs.o
list_funcs.o: list_funcs.c list.h
	gcc -c -std=c99 -Wall list_funcs.c
main.o: main.c list.h
	gcc -c -std=c99 -Wall main.c
clean:
	rm -f listTest list_funcs.o main.o
