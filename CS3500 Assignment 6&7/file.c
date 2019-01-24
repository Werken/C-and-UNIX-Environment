#include <stdio.h>
#include <stdlib.h>
#include "runlength.h"
#include "file.h"

void Compress(const char *fname, Matrix *data, int quality, int nBlock) {
	int dc, i;
	for (i = 0; i < nBlock; i++) {
		data[i] = EncodeDCT(data[i], quality, &dc);
		EncodeRunlength(fname, data[i], dc);
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
	int dc = 0, i;
	for (i = 0; i < nBlock; i++) {
		data[i] = DecodeRunlength(fname, &dc, &filepos);
		data[i] = DecodeDCT(data[i], quality, dc);
		dc = 0;
	}
	return data;
}
Matrix DecodeDCT(Matrix data, int quality, int dc) {
	Init(quality);
	Matrix M = MatrixElementMult(Q, data);
	Matrix TransposeT = MatrixTranspose(T);
	Matrix Temp = MatrixMult(TransposeT, M);
	Matrix C = MatrixMult(Temp, T);
	C = AddFix(C, dc);
	return C;
}
Matrix DecodeRunlength(const char *fname, int *dc, long *filepos) {	
	Array zzDecode = Read(fname, filepos, dc);
	Array zzArray = reverse(zzDecode.contents, zzDecode.size);
	free(zzDecode.contents);
	Matrix C = InverseZigZagOrdering(zzArray.contents);
	free(zzArray.contents);
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
	return C;
}
void EncodeRunlength(const char *filename, Matrix data, int dc) {
	int *zzData = ZigZagOrdering(data);
        Array zzArray = Consecutive(zzData);
        int *zzData2 = malloc(zzArray.size * sizeof(int));
	int count = 0;
        while (count < zzArray.size) {
                zzData2[count] = zzArray.contents[count];
                zzData2[count + 1] = zzArray.contents[count + 1];
                count += 2;
        }
        Write(zzData2, zzArray.size, filename, dc);
        free(zzData2);
        free(zzArray.contents);
}
void Write(int *occurrences, int s, const char *filename, int dc) {
	int k = 10;
	FILE *fp = fopen(filename, "a+b");
	int buffer[BUF_SIZE];
	int i;
	for (i = 0; i < BUF_SIZE; i++)
	{
		buffer[i] = 0;
	}
	if (fp == NULL)
	{
		printf("Could not open file\n");
	}
	unsigned char ave;
	ave = toBinaryAverage(dc);
	fwrite(&ave, sizeof(unsigned char), 1, fp);
	for (i = 0; i < s; i += 2) {
		unsigned char *data = calloc(3, sizeof(unsigned char));
		toBinary(data, k, occurrences[i], occurrences[i + 1]);
		fwrite(data, sizeof(unsigned char), 3, fp);
		fflush(fp);
		free(data);
	}
	fclose(fp);
}
Array Read(const char *fname, long *filepos, int *dc)
{
	int k = 10;
        FILE *fp = fopen(fname, "rb");
	fseek(fp, *filepos, SEEK_SET);
        if (fp == NULL)
        {
                printf("Could not open file\n");
        }
	unsigned char ave_buffer;
	fread(&ave_buffer, sizeof(unsigned char), 1, fp);
	*dc = fromBinaryAverage(ave_buffer);
	int *contents = malloc(2 * sizeof(int));
	int occurrence = 0, count = 0, size = 2;
	while (occurrence != 64) {
		unsigned char *buffer = malloc(2 * sizeof(int));
		fread(buffer, sizeof(unsigned char), 3, fp);
		int *fromBin = fromBinary(buffer, k);
		occurrence += fromBin[1];
		contents[count] = fromBin[0];
		contents[count + 1] = fromBin[1];
		count += 2;
		size += 2;
		contents = realloc(contents, size * sizeof(int)); 
		free(fromBin);
		free(buffer);
	}
	contents = realloc(contents, size * sizeof(int) - 2);
	*filepos = ftell(fp);
        fclose(fp);
	Array occurrences = {contents, count};
	return occurrences;
}
