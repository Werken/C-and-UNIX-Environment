#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "matrix.h"
#include "runlength.h"

#define N 8

struct zigzag ZigZag[N*N] = {
    {0,0},
    {0,1},{1,0},
    {2,0},{1,1},{0,2},
    {0,3},{1,2},{2,1},{3,0},
    {4,0},{3,1},{2,2},{1,3},{0,4},
    {0,5},{1,4},{2,3},{3,2},{4,1},{5,0},
    {6,0},{5,1},{4,2},{3,3},{2,4},{1,5},{0,6},
    {0,7},{1,6},{2,5},{3,4},{4,3},{5,2},{6,1},{7,0},
    {7,1},{6,2},{5,3},{4,4},{4,5},{2,6},{1,7},
    {2,7},{3,6},{4,5},{5,4},{6,3},{7,2},
    {7,3},{6,4},{5,5},{4,6},{3,7},
    {4,7},{5,6},{6,5},{7,4},
    {7,5},{6,6},{5,7},
    {6,7},{7,6},
    {7,7}
};

int data[N*N];
unsigned char *toBinary(int x, int k) {
	int i;
	int j = 0;
	unsigned char *output = malloc(k * sizeof(unsigned char));
	for (i = k - 1; i >= 0; i--) {
		if (x == 0) {
			output[j] = '0';
		} else {		
			if (x >= pow(2, i)) {
				output[j] = '1';
				x -= (int)pow(2, i);
			} else {
				output[j] = '0';
			}
		}
		j++;
	}
	return output;
}
int *fromBinary(char input[], int k) {
        int i, j, sign;
        sign = (input[0] == '0') ? 1 : -1;
        int offset = 1;
        int value = 0, occurrence = 0;
        for (i = 0; i < k-1; i++) {
                value += (int)pow(2, k - 2 - i) * ((int)input[offset] - 48);
                offset++;
        }
        for (j = 0; j < k; j++) {
                occurrence += (int)pow(2, k - 1 - j) * ((int)input[offset] - 48);
		offset++;
        }
        int *result = malloc(2 * sizeof(int));
	result[0] = occurrence * sign;
        result[1] = value;
        return result;
}
Array Consecutive(int *x) {
	int i, store = x[0], count = 0, ignore = 0;
	for (i = 0; i < N*N; i++) {
		if (x[i] != ignore)
			store = x[i];
		if (x[i] == store && ignore != x[i]) {
                        count++;
                        ignore = store;
                }
	}
	int occurrence[count], value[count], occurCount = 0;
	store = x[0], ignore = 0;

	int *data1 = malloc((count*2) * sizeof(int));

	for (i = 0; i < (count*2); i++) {
		data1[i] = 0;
	}
	for (i = 0; i < count; i++) {
		occurrence[i] = 0;
		value[i] = 0;
	}
	count = 0;
	for (i = 0; i <= N*N; i++) {
                if (x[i] != ignore) {
                        store = x[i];
			occurCount++;
		}
		else
			occurCount++;
                if (x[i] == store && ignore != x[i]) {
                        ignore = store;
			value[count] = x[i];
			occurrence[count-1] = occurCount;
			occurCount = 0;
			count++;
                }
		else
			occurrence[count-1] = occurCount;
        }
	i = 0;
	int j = 0;
	while (i < count) {
		data1[j] = value[i];
		data1[j + 1] = occurrence[i];
		i++;
		j += 2;
	}
	Array arr = {data1, j};
	return arr;
}
Array reverse(int *x, int s) {
	int i, count = 0;
	for (i = 0; i < s; i += 2) {
		count += x[i + 1];
	}
	int *rData = malloc(count * sizeof(int));
	int value = 0, occurrence = 0;
	int count2 = 0, j = 1;
	for (i = 0; i < s; i += 2) {
		value = x[i];
		occurrence = x[i + 1];
		rData[count2] = value;
		while (j < occurrence) {
			rData[++count2] = value;
			j++;
		}
		count2++;
		j = 1;
	}
	Array arr = {rData, count2};
	return arr;
}
int* ZigZagOrdering(Matrix x) {
	int count = 0;
	while(count < N*N) {
		data[count] = x.element[ZigZag[count].row][ZigZag[count].col];
		count++;
	}
	return data;
}
Matrix InverseZigZagOrdering(int *x) {
	int count = 0,i,j;
	Matrix X;
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			X.element[ZigZag[count].row][ZigZag[count].col] = x[count];
			count++;
		}
	}
	return X;	
}
