#include <stdio.h>
#include <stdlib.h>
#include "pgm.h"

void readpgm(char filename[], char filename2[]) {
	FILE *fp;
        char ch;

        fp = fopen(filename, "r");
        if (fp == NULL) {
                printf("Unable to open file\n");
                return;
        }
        ch = fgetc(fp);
        if (ch != 'P') {
                printf("Not valid file type\n");
                return;
        }
        ch = fgetc(fp);
        int type = ch - 48;
        while(fgetc(fp) != '\n');
        while (fgetc(fp) == '#') {
                while (fgetc(fp) != '\n');
        }
        fseek(fp, -1, SEEK_CUR);
	int w, h, intensity;
        fscanf(fp, "%d %d", &w, &h);
	fscanf(fp, "%d", &intensity);
	fgetc(fp);
	unsigned char *data = NULL;
	if (type == 2) {
        	data = (unsigned char*)malloc(sizeof(int) * (h * w));
		int i, point;
		for (i = 0; i < (h * w); i++) {
			fscanf(fp, "%d", &point);
			data[i] = point;
		}
	}
	else if (type == 5) {
		data = (unsigned char*)malloc(sizeof(unsigned char) * (h * w));
		fread(data, sizeof(unsigned char), (h * w), fp);
	}
	else if (type == 6) {
		data = (unsigned char*)malloc(sizeof(unsigned char) * (h * w * 3));
		fread(data, sizeof(unsigned char), (h * w * 3), fp);
	}
	fclose(fp);

	save(filename2, data, type, h, w, intensity);
}
void save(char filename[], unsigned char *data, int type, int h, int w, int intensity) {
	FILE *fp;
	fp = fopen(filename, "w");
	
	fputc('P', fp);
	if (type == 2 || type == 5) {
		fprintf(fp, "%d", 5);
	}
	else {
		fprintf(fp, "%d", type);
	}
	fputc('\n', fp);
	fprintf(fp, "%d %d", w, h);
	fputc('\n', fp);
	fprintf(fp, "%d", intensity);
	fputc('\n', fp);

	if (type == 2) {
		fwrite(data, sizeof(unsigned char), (h * w), fp);	
	}
	else if (type == 5) {
		fwrite(data, sizeof(unsigned char), (h * w), fp);
	}
	else {
		fwrite(data, sizeof(unsigned char), (h * w * 3), fp);
	}

	free(data);
	fclose(fp);	
}

