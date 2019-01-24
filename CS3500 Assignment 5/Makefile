CC = gcc
INCLUDES = include
# -Wall : turn on compiler warnings
# -std=c99 : invoke C99 compiler allowing for(int i=0; ...)
CFLAGS = -Wall -std=c99 -O3 -I $(INCLUDES)
LIBS = -lm

RUN: pgm.o main.c
	$(CC) $(CFLAGS) $(LIBS) pgm.o main.c -o compress
	make clean

pgm.o: pgm.c
	$(CC) $(CFLAGS) pgm.c -c

clean:
	rm -f *.0

all:
	RUN
