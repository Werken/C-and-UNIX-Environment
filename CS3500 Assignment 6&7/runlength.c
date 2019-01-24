#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "runlength.h"

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
int *fromBinary(unsigned char *data, int k) {
	int i, padding = k - 8, sign = 1;
	int *array = calloc(2, sizeof(int));
        if ((data[0] & (1 << 7)) >> 7 == 1) sign = -1;
        for (i = 0; i < 7; i++) {
                if ((data[0] & (1 << i)) >> i == 1) array[1] += (int)pow(2, i);
        }
        if (k >= 8) {
                for (i = 0; i < 8 - padding; i++) {
			if ((data[1] & (1 << i)) >> i == 1) array[0] += (int)pow(2, i + padding);
                }
                for (i = 7; i > 7 - padding; i--) {
			if ((data[2] & (1 << i)) >> i == 1) array[0] += (int)pow(2, i - (8 - padding));
                }
        }
	array[0] *= sign;
	return array;
}
int fromBinaryAverage(unsigned char data) {
	int i, average = 0;
	for (i = 0; i < 8; i++) {
		if ((data & (1 << i)) >> i == 1) average += (int)pow(2, i);
	}
	return average;
}
unsigned char toBinaryAverage(int ave) {
	int i, y;
	unsigned char average = 0;
	for (i = 0; i < 8; i++) {
		y = (ave & (1 << i)) >> i;
                if (y == 1) average = average | (1 << i);
	}
	return average;
}
void toBinary(unsigned char *data, int k, int n1, int n2) {
	int i, y, padding = k - 8;
	if (n1 < 0) {
		data[0] = data[0] | (1 << 7);
		n1 *= -1;
	}
	for (i = 0; i < 7; i++) {
		y = (n2 & (1 << i)) >> i;
		if (y == 1) data[0] = data[0] | (1 << i);
	}
	if (k >= 8) {
		for (i = padding; i < 8; i++) {
			y = (n1 & (1 << i)) >> i;
			if (y == 1) data[1] = data[1] | (1 << (i - padding));
		}
		for (i = 0; i < padding; i++) {
			y = (n1 & (1 << i)) >> i;
			if (y == 1) data[2] = data[2] | (1 << (8 - padding + i));
		}
	}
}
Array Consecutive(int *x) {
	int i, store = x[0], count = 0, ignore = 10000;
	for (i = 0; i < N*N; i++) {
		if (x[i] != ignore)
			store = x[i];
		if (x[i] == store && ignore != x[i]) {
                        count++;
                        ignore = store;
                }
	}
	int occurrence[count], value[count], occurCount = 0;
	store = x[0], ignore = 10000;

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
		data[count] = (((int)(x.element[ZigZag[count].row][ZigZag[count].col] + 32768.5)) - 32768);
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
