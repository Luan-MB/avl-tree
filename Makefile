# GRR20190363 Luan Machado Bernardt

CC = gcc
CFLAGS = -Wall

OBJECTS= myavl

all: $(OBJECTS) clean

$(OBJECTS): $(OBJECTS).o avl.o
	$(CC) $(CFLAGS) $(OBJECTS).o avl.o -o $(OBJECTS)

$(OBJECTS).o: $(OBJECTS).c avl.h
	$(CC) $(CFLAGS) $(OBJECTS).c -c

avl.o: avl.c avl.h
	$(CC) $(CFLAGS) avl.c -c

clean:
	-rm -f *.o

purge:
	-rm -f $(OBJECTS)
