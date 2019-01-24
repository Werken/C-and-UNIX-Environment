#include <stdio.h>
#include <stdlib.h>
#include "pgm.h"

int main(int argc, char **argv)
{
	if (argc == 3) {
		int w, h, nBlock, type, intensity;
		Matrix *data = ReadImage(argv[1], &w, &h, &nBlock, &type, &intensity);

		WriteImage(argv[2], data, &w, &h, &type, &intensity);

		free(data);
	}
	else {
		fprintf(stderr, "Usage: %s image_path output_path\n", argv[0]);
		exit(1);
	}
	return 0;
}
