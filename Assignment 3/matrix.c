#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

#define N 8

void PrintMatrix(Matrix a) {
        int i,j;
        for(i = 0; i < N; i++) {
                for(j = 0; j < N; j++) {
                        printf("%d ", (int)a.element[i][j]);
                }
                printf("\n");
        }
}
