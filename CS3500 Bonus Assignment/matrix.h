#ifndef _MATRIX
#define _MATRIX

#define PI 3.14159265358979323846
#define N 8

typedef struct _Matrix {
        double element[N][N];
} Matrix;

Matrix Q;
Matrix T;

void CastMatrix(Matrix *a);
void PrintMatrix(Matrix *a);
Matrix MatrixTranspose(Matrix a);
float ComputeAverage(Matrix a);
int round2(double ave);
Matrix Add(Matrix a, int dc);
Matrix AddFix(Matrix a, int dc);
Matrix MatrixElementDiv(Matrix a, Matrix b);
Matrix MatrixElementMult(Matrix a, Matrix b);
Matrix MatrixMult(Matrix a, Matrix b);
void Init(int quality);

#endif
