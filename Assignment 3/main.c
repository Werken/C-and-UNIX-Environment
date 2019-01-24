#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "runlength.h"
#include "file.h"

#define N 8

int main(int argc, char **argv)
{
	Matrix C =    {{10,  4, 2,  5, 1, 0, 0, 0,
                    3,  9, 1,  2, 1, 0, 0, 0,
                   -7, -5, 1, -2, -1, 0, 0, 0,
                   -3, -5, 0, -1, 0, 0, 0, 0,
                   -2,  1, 0,  0, 0, 0, 0, 0,
                    0,  0, 0,  0, 0, 0, 0, 0,
                    0,  0, 0,  0, 0, 0, 0, 0,
       	            0,  0, 0,  0, 0, 0, 0, 0}};

	int k = atoi(argv[1]);
	int *zzData = ZigZagOrdering(C);
	int count = 0;
	while (count < N*N) {
		printf("%d ", zzData[count]);
		count++;
	}
	printf("\n");
	printf("\n");
	Matrix C2;
	count = 0;
	Array zzArray = Consecutive(zzData);
	while (count < zzArray.size) {
                printf("%d %d\n", zzArray.contents[count], zzArray.contents[count + 1]);
                count += 2;
        }
	printf("\n");
	int *zzData2 = malloc(zzArray.size * sizeof(int));
	count = 0;
	while (count < zzArray.size) {
		zzData2[count] = zzArray.contents[count];
		zzData2[count + 1] = zzArray.contents[count + 1];
		count += 2;
	}
	Write(zzData2, count, k);
	free(zzData2);
	free(zzArray.contents);
	Array zzDecode = Read(count, k);
	Array zzArray2 = reverse(zzDecode.contents, count);
	free(zzDecode.contents);
	count = 0;
	while (count < N*N) {
		printf("%d ", zzArray2.contents[count]);
		count++;
	}
	printf("\n");
	printf("\n");
	C2 = InverseZigZagOrdering(zzArray2.contents);
	free(zzArray2.contents);
	PrintMatrix(C2);
}
