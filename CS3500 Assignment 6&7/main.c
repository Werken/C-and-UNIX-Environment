#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "runlength.h"
#include "file.h"
#include "pgm.h"

typedef struct _datInfo{
	int w;
	int h;
	int quality;
	int type;
	long fp;
} datInfo;

datInfo getMetaData(const char *fname) {
	FILE *fp = fopen(fname, "r");
	datInfo data;
	int state = 0, w, h, quality, type, i = 0;
	char ch = 'A';
	char cache[15];
	while (ch != '\n') {
		ch = fgetc(fp);
		if (ch == ' ') {
			state += 1;
			memset(cache, 0, strlen(cache));
			i = 0;
			continue;
		}
		cache[i++] = ch;
		switch (state) {
			case 0:
				w = atoi(cache);
				break;
			case 1:
                                h = atoi(cache);
                                break;
			case 2:
                                quality = atoi(cache);
                                break;
			case 3:
                                type = atoi(cache);
                                break;
		}
	}
	data = (datInfo){w, h, quality, type, ftell(fp)};
	return data;
	free(cache);
}

int main(int argc, char **argv)
{
	int w, h, nBlock, type, intensity;
	if (argv[1][0] == '-' && argv[1][1] == 'c') {
		int quality = atoi(argv[4]);
		Matrix *data = ReadImage(argv[2], &w, &h, &nBlock, &type, &intensity);
		FILE *fp = fopen(argv[3], "w");
		fprintf(fp, "%d %d %d %d\n", w, h, quality, type);
		fclose(fp);
		Compress(argv[3], data, quality, nBlock);
		free(data);
	}
	else if (argv[1][0] == '-' && argv[1][1] == 'd') {
		datInfo dinfo = getMetaData(argv[2]);
		Matrix *data = Decompress(argv[2], dinfo.w, dinfo.h, dinfo.quality, dinfo.type, dinfo.fp);
		WriteImage(argv[3], data, &dinfo.w, &dinfo.h, &dinfo.type, 255);
	}
}
