CC = gcc
INCLUDES = include
# -Wall : turn on compiler warnings
# -std=c99 : invoke C99 compiler allowing for(int i=0; ...)
CFLAGS = -Wall -std=c99 -O3 -I $(INCLUDES)
LIBS = -lm

RUN: file.o matrix.o runlength.o main.c
	$(CC) $(CFLAGS) $(LIBS) file.o matrix.o runlength.o main.c -o compress
	make clean

file.o: file.c
	$(CC) $(CFLAGS) file.c -c

matrix.o: matrix.c
	$(CC) $(CFLAGS) matrix.c -c

runlength.o: runlength.c
	$(CC) $(CFLAGS) runlength.c -c

clean:
	rm -f *.0

all:
	RUN
