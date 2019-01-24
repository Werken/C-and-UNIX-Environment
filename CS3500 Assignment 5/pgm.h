#ifndef _PGM
#define _PGM

#define N 8
#define idiv(x, y) ((x > 0) ? 1 + (x - 1) / y : (x / y))

typedef struct _Matrix {
	double element[N][N];
} Matrix;

Matrix toMatrix(unsigned char *data, int n, int *w, int *type);
void toArray(Matrix *data, int n, int *w, int *type, unsigned char *temp);
Matrix *ReadImage(char filename[], int *w, int *h, int *nBlock, int *type, int *intensity);
void WriteImage(char filename[], Matrix *data, int *w, int *h, int *type, int *intensity);

#endif
