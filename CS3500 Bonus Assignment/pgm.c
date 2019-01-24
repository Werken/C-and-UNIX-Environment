#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pgm.h"

Matrix toMatrix(unsigned char *data, int n, int *w, int *type) {
	Matrix X;
	int i, j, count = N;
	int a = n % idiv(*w, N);
	int b = n / idiv(*w, N);
	int last = idiv(*w, N);
	int zero = N - (*w - ((last - 1) * N));
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (((n + 1) % last) != 0 || n == 0) {
				X.element[i][j] = data[*w * (N * b + i) + N * a + j];
			}
			else {
				if (count > zero) {
					X.element[i][j] = data[*w * (N * b + i) + N * a + j];
				}
				else {
					X.element[i][j] = 0.0;
				}
				count--;
			}
		}
		count = N;
	}
	return X;
}
void toArray(Matrix *data, int n, int *w, int *type, unsigned char *temp) {
	int i, j, count = N;
	int last = idiv(*w, N);
	int a = n % idiv(*w, N);
        int b = n / idiv(*w, N);
        int zero = N - (*w - ((last - 1) * N));
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (((n + 1) % last) != 0 || n == 0) {
				temp[*w * (N * b + i) + N * a + j] = data[n].element[i][j];
			}
			else {
				if (count > zero) {
					temp[*w * (N * b + i) + N * a + j] = data[n].element[i][j];
				}
				count--;
			}
               	}
		count = N;
	}
}
Matrix *ReadImage(char filename[], int *w, int *h, int *nBlock, int *type, int *intensity) {
	FILE *fp;
        char ch;
        fp = fopen(filename, "r");
        if (fp == NULL) {
                printf("Unable to open file\n");
        }
        ch = fgetc(fp);
        if (ch != 'P') {
                printf("Not valid file type\n");
        }
        ch = fgetc(fp);
        *type = ch - 48;
        while(fgetc(fp) != '\n');
        while (fgetc(fp) == '#') {
                while (fgetc(fp) != '\n');
        }
        fseek(fp, -1, SEEK_CUR);
        fscanf(fp, "%d %d", w, h);
	fscanf(fp, "%d", intensity);
	fgetc(fp);
	*nBlock = idiv(*w, N) * idiv(*h, N);
	Matrix *data = NULL;
	unsigned char *temp = NULL;
	int i;
	if (*type == 2) {
		int point;
		temp = (unsigned char*)malloc(sizeof(int) * (*h * *w));
		for (i = 0; i < (*h * *w); i++) {
			fscanf(fp, "%d", &point);
			temp[i] = point;
		}
        	data = (Matrix*)malloc(sizeof(Matrix) * *nBlock);
		for (i = 0; i < *nBlock; i++) {
			data[i] = toMatrix(temp, i, w, type);
		}
	}
	else if (*type == 5) {
		temp = (unsigned char*)malloc(sizeof(unsigned char) * (*h * *w));
		fread(temp, sizeof(unsigned char), (*h * *w), fp);
		data = (Matrix*)malloc(sizeof(Matrix) * *nBlock);
                for (i = 0; i < *nBlock; i++) {
                        data[i] = toMatrix(temp, i, w, type);
                }
	}
	else if (*type == 6) {
		*w *= 3;
		*nBlock = idiv(*w, N) * idiv(*h, N);
		temp = (unsigned char*)malloc(sizeof(unsigned char) * (*h * *w));
		fread(temp, sizeof(unsigned char), (*h * *w), fp);
		data = (Matrix*)malloc(sizeof(Matrix) * *nBlock);
                for (i = 0; i < *nBlock; i++) {
                        data[i] = toMatrix(temp, i, w, type);
                }
		*w /= 3;
	}
	fclose(fp);
	free(temp);
	return data;
}
void WriteImage(char filename[], Matrix *data, int *w, int *h, int *type, int intensity) {
	FILE *fp;
	fp = fopen(filename, "w");
	fputc('P', fp);
	if (*type == 2 || *type == 5) {
		fprintf(fp, "%d", 5);
	}
	else {
		fprintf(fp, "%d", *type);
	}
	fputc('\n', fp);
	fprintf(fp, "%d %d", *w, *h);
	fputc('\n', fp);
	fprintf(fp, "%d", intensity);
	fputc('\n', fp);
	unsigned char *temp = NULL;
	int nBlock = idiv(*w, N) * idiv(*h, N);
	int i;
	if (*type == 2) {
		temp = (unsigned char*)malloc(sizeof(int) * (*h * *w));
		for (i = 0; i < nBlock; i++) {
			toArray(data, i, w, type, temp);
		}
		fwrite(temp, sizeof(unsigned char), (*w * *h), fp);
	}
	else if (*type == 5) {
                temp = (unsigned char*)malloc(sizeof(unsigned char) * (*h * *w));
                for (i = 0; i < nBlock; i++) {
                        toArray(data, i, w, type, temp);
                }
		fwrite(temp, sizeof(unsigned char), (*h * *w), fp);
	}
	else if (*type == 6) {
		*w *= 3;
		int nBlockRGB = idiv(*w, N) * idiv(*h, N);
		temp = (unsigned char*)malloc(sizeof(unsigned char) * (*h * *w));
		for (i = 0; i < nBlockRGB; i++) {
			toArray(data, i, w, type, temp);
		}
		fwrite(temp, sizeof(unsigned char), (*h * *w), fp);
	}
	free(temp);
	free(data);
	fclose(fp);	
}
