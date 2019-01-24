#include <stdio.h>
#include <stdlib.h>
#include "hufftree.h"
#include "file.h"

void Compress(const char *fname, Matrix *data, int quality, int nBlock) {
	int dc, i;
	for (i = 0; i < nBlock; i++) {
		data[i] = EncodeDCT(data[i], quality, &dc);
		EncodeHuffman(fname, data[i], dc);
	}
}
Matrix *Decompress(const char *fname, int w, int h, int quality, int type, long filepos) {
	int w8 = idiv(w, N);
	int h8 = idiv(h, N);
	int nBlock = w8*h8;
	Matrix *data = NULL;
	if (type == 2 || type == 5) {
		data = (Matrix *)malloc(sizeof(Matrix) * nBlock);
	}
	else if (type == 6) {
		nBlock *= 3;
		data = (Matrix *)malloc(sizeof(Matrix) * nBlock);
	}
	int dc = 0, i, j;
	for (i = 0; i < nBlock; i++) {
		Tree *receive;
		data[i] = DecodeHuffman(fname, &filepos, &receive, &dc);
		data[i] = DecodeDCT(data[i], quality, dc);
		dc = 0;
		for (j = 0; j < receive[0].size + 1; j++) {
                        if (receive[j].bin != NULL) free(receive[j].bin);
                }
                free(receive);
	}
	return data;
}
Matrix DecodeDCT(Matrix data, int quality, int dc) {
	Init(quality);
	Matrix M = MatrixElementMult(Q, data);
	Matrix TransposeT = MatrixTranspose(T);
	Matrix Temp = MatrixMult(TransposeT, M);
	Matrix C = MatrixMult(Temp, T);
	C = Add(C, dc);
	CastMatrix(&C);
	return C;
}
Matrix EncodeDCT(Matrix data, int quality, int *dc) {
	float ave = ComputeAverage(data);
	*dc = round2(ave);
	Init(quality);
	Matrix M = Add(data, (*dc * -1));
	Matrix Temp = MatrixMult(T, M);
	Matrix TransposeT = MatrixTranspose(T);
	Matrix D = MatrixMult(Temp, TransposeT);
	Matrix C = MatrixElementDiv(D, Q);
	CastMatrix(&C);
	return C;
}
