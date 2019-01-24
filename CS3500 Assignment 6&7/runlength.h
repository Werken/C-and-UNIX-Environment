#ifndef _RUN
#define _RUN

#include "matrix.h"

typedef struct _Array {
        int *contents;
        int size;
} Array;

struct zigzag {
    int row, col;
};

extern struct zigzag ZigZag[N*N];

int *fromBinary(unsigned char *data, int k);
int fromBinaryAverage(unsigned char data);
unsigned char toBinaryAverage(int ave);
void toBinary(unsigned char *data, int k, int n1, int n2);
Array Consecutive(int *x);
Array reverse(int *x, int s);
int* ZigZagOrdering(Matrix x);
Matrix InverseZigZagOrdering(int *x);

#endif 
