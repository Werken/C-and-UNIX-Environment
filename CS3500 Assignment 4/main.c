#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgm.h"

int main(int argc, char **argv)
{
	char *input = malloc(strlen(argv[1]) + 1);
	strcpy(input, argv[1]);
	char *output = malloc(strlen(argv[2]) + 1);
	strcpy(output, argv[2]);

	readpgm(input, output);	

	free(input);
	free(output);
}
