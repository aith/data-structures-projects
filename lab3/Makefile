HEADER = charType.c
OBJECTS = charType.o

default: charType

%.o: %.c $(HEADERS)
	gcc -c $< -o $@

charType: $(OBJECTS)
	gcc $(OBJECTS) -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f charType
