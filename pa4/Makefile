#file: Makefile
#Ari Iramanesh
#id: 1628897
#class: 12B
#assignment 3

#desc: compiles the BSTClient file for testing the implementation of a
#  binary search tree, which requires BST.c, BSTClient.h, and BST.h
#------------------------------------------------------------------------------
# Makefile for Blockchain ADT and its test client
#------------------------------------------------------------------------------

STRUCT_NAME  =  BST
SOURCES   = $(STRUCT_NAME).c  $(STRUCT_NAME)Client.c
OBJECTS   = $(STRUCT_NAME).o  $(STRUCT_NAME)Client.o
HEADERS   = $(STRUCT_NAME).h 
EXEBIN    = $(STRUCT_NAME)Client
FLAGS     = -std=c99 -Wall

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS) $(HEADERS)
	gcc -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES) $(HEADERS)
	gcc -c $(FLAGS) $(SOURCES)

clean :
	rm -f $(EXEBIN) $(OBJECTS)

check:
	valgrind --leak-check=full $(EXEBIN) 
