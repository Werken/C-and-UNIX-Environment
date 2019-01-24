CC = gcc
INCLUDES = include
# -Wall : turn on compiler warnings
# -std=c99 : invoke C99 compiler allowing for(int i=0; ...)
CFLAGS = -Wall -std=c99 -O3 -I $(INCLUDES)
LIBS = -lm

RUN: file.o matrix.o pgm.o hufftree.o main.c
	$(CC) $(CFLAGS) $(LIBS) file.o matrix.o pgm.o hufftree.o main.c -o compress
	make clean

file.o: file.c
	$(CC) $(CFLAGS) file.c -c

matrix.o: matrix.c
	$(CC) $(CFLAGS) matrix.c -c

pgm.o: pgm.c
	$(CC) $(CFLAGS) pgm.c -c

hufftree.o: hufftree.c
	$(CC) $(CFLAGS) hufftree.c -c

clean:
	rm -f *.o

all:
	RUN
