#file: Makefile
#Ari Iramanesh
#id: 1628897
#class: 12M
#lab4

#desc: compiles the BlockchainClient file for testing the implementation of the
# Blockchain system, which requires Block.h, Block.c, Blockchain.h, Blockchain.c,
# and BlockchainClient.c
#------------------------------------------------------------------------------
# Makefile for Blockchain ADT and its test client
#------------------------------------------------------------------------------

ADT_NAME  =  Blockchain
ADT_DEPENDENCIES = Block
SOURCES   = $(ADT_NAME).c  $(ADT_DEPENDENCIES).c $(ADT_NAME)Client.c
OBJECTS   = $(ADT_NAME).o  $(ADT_DEPENDENCIES).o  $(ADT_NAME)Client.o
HEADERS   = $(ADT_NAME).h  $(ADT_DEPENDENCIES).h
EXEBIN    = $(ADT_NAME)Client
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
