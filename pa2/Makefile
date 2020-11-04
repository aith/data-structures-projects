#Owner: Ari Iramanesh
#cruzID: 1628897
#class: 12B, Bhatti
#assignment 2
#creates object files for compiling listTest. Ingredients are list.c  and list.h
#  and listUtil.c, listUtil.h, main.c.
listTest: list.o main.o listUtil.o
	gcc -o listTest list.o main.o listUtil.o
list.o: list.c list.h
	gcc -c -std=c99 -Wall list.c
main.o: main.c list.h listUtil.h
	gcc -c -std=c99 -Wall main.c
listUtil.o: listUtil.c list.h
	gcc -c -std=c99 -Wall listUtil.c
clean:
	rm -f listTest list.o main.o listUtil.o
