# GRR20190363 Luan Machado Bernardt

CC = gcc
CFLAGS = -Wall

OBJECTS= wavinfo wavvol wavecho wavwide wavnorm wavcat wavmix wavrev

all: $(OBJECTS) clean

$(OBJECTS): $(OBJECTS).o wavlib.o
	$(CC) $(CFLAGS) $(OBJECTS).o wavlib.o -o $(OBJECTS)

$(OBJECTS).o: $(OBJECTS).c wavlib.h
	$(CC) $(CFLAGS) $(OBJECTS).c -c

wavlib.o: wavlib.c wavlib.h
	$(CC) $(CFLAGS) wavlib.c -c

clean:
	-rm -f *.o

purge:
	-rm -f $(OBJECTS)
