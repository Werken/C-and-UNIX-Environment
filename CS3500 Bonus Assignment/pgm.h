#ifndef _PGM
#define _PGM

#include "matrix.h"
#define idiv(x, y) ((x > 0) ? 1 + (x - 1) / y : (x / y))

Matrix toMatrix(unsigned char *data, int n, int *w, int *type);
void toArray(Matrix *data, int n, int *w, int *type, unsigned char *temp);
Matrix *ReadImage(char filename[], int *w, int *h, int *nBlock, int *type, int *intensity);
void WriteImage(char filename[], Matrix *data, int *w, int *h, int *type, int intensity);

#endif

