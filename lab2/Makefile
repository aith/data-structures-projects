FLAGS = -std=c99 -Wall
SOURCES = FileReverse.c
OBJECTS = FileReverse.o
EXEC = FileReverse

all : $(EXEC)

$(EXEC) : $(OBJECTS)
	gcc -o $(EXEC) $(OBJECTS)

$(OBJECTS) : $(SOURCES)
	gcc -c $(FLAGS) $(SOURCES)

clean:
	rm -f $(OBJECTS) $(EXEC)
