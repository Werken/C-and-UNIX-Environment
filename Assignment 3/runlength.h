#define N 8

typedef struct _Array {
        int *contents;
        int size;
} Array;

struct zigzag {
    int row, col;
};

extern struct zigzag ZigZag[N*N];

unsigned char *toBinary(int x, int k);
int *fromBinary(char input[], int k);
Array Consecutive(int *x);
Array reverse(int *x, int s);
int* ZigZagOrdering(Matrix x);
Matrix InverseZigZagOrdering(int *x);
