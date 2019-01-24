#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

Matrix Q50 = {{16, 11, 10, 16, 24, 40, 51, 61,
        12, 12, 14, 19, 26, 58, 60, 55,
        14, 13, 16, 24, 40, 57, 69, 56,
        14, 17, 22, 29, 51, 87, 80, 62,
        18, 22, 37, 56, 68,109,103, 77,
        24, 35, 55, 64, 81,104,113, 92,
        39, 64, 78, 87,103,121,120,101,
        72, 92, 95, 98,112,100,103, 99}};

void PrintMatrix(Matrix *a) {
        int i,j;
        for(i = 0; i < N; i++) {
                for(j = 0; j < N; j++) {
                        printf("%d ", (int)a->element[i][j]);
                }
                printf("\n");
        }
}
Matrix MatrixTranspose(Matrix a) {
	int i,j;
	Matrix X;
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			X.element[i][j] = a.element[j][i];
		}
	}
	return X;
}
float ComputeAverage(Matrix a) {
	int i,j,count = 0;
	float ave,sum = 0.0;
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			sum += a.element[i][j];
			count++;
		}
	}
	ave = sum / (float)count;

	return ave;
}
int round2(double ave) {
	int n = (int)(ave < 0 ? (ave - 0.5) : (ave + 0.5));
	return n;
}
Matrix Add(Matrix a, int dc) {
        int i,j;
        for(i = 0; i < N; i++) {
                for(j = 0; j < N; j++) {
                        a.element[i][j] = a.element[i][j] + (float)dc;
                }
        }
        return a;
}
Matrix AddFix(Matrix a, int dc) {
	int i,j,temp;
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			temp = a.element[i][j] + (float)dc;
			if (temp < 0) temp = 0;
			else if (temp > 255) temp = 255;
			a.element[i][j] = temp;
		}
	}
	return a;
}
Matrix MatrixElementDiv(Matrix a, Matrix b) {
	int i,j;
	Matrix H;
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			H.element[i][j] = a.element[i][j] / b.element[i][j];
		}
	}
	return H;
}
Matrix MatrixElementMult(Matrix a, Matrix b) {
        int i,j;
        Matrix H;
        for(i = 0; i < N; i++) {
                for(j = 0; j < N; j++) {
                        H.element[i][j] = a.element[i][j] * b.element[i][j];
                }
        }
        return H;
}
Matrix MatrixMult(Matrix a, Matrix b) {
	int i,j,k;
	Matrix H;
	for(i = 0; i < N; i++) {
                for(j = 0; j < N; j++) {
                        H.element[i][j] = 0.0;
                }
        }
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			for(k = 0; k < N; k++) {
				H.element[i][j] += a.element[i][k] * b.element[k][j];
			}
		}
	}
	return H;
}

void Init(int quality) {
	int i,j;
	float r1,r2,scale,X;
	r1 = (1.0/50) * (100 - quality);
	r2 = 50 / quality;
	scale = (quality > 50 ? r1 : r2);
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			X = Q50.element[i][j] * scale;
			if (i == 0) {
				T.element[i][j] = 1 / sqrt(N);
			}
			else
				T.element[i][j] = (sqrt(2.0/N) * cos(((2.0 * j + 1.0) * i * PI) / (2.0 * N)));
			if (X <= 1)
				Q.element[i][j] = 1;
			else if (X >= 255)
				Q.element[i][j] = 255;
			else
				Q.element[i][j] = X;
		}
	}
}
