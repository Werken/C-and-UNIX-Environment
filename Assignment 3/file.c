#include <stdio.h>
#include <stdlib.h>
#include "runlength.h"
#include "file.h"

#define BUF_SIZE 1024

void Write(int *occurrences, int s, int k)
{
	FILE *fp = fopen("test.txt", "wb");
	unsigned char buffer[BUF_SIZE];
	int i;
	for (i = 0; i < BUF_SIZE; i++)
	{
		buffer[i] = '0';
	}
	if (fp == NULL)
	{
		printf("Could not open file\n");
	}
	int count = 0, j;
	unsigned char *value, *occurrence;
	for (i = 0; i < s; i += 2)
	{
		buffer[count] = (occurrences[i] >= 0) ? '0' : '1';
		value = toBinary(occurrences[i + 1], k - 1);
		for (j = 0; j < k - 1; j++) {
			buffer[++count] = value[j];
		}
		occurrence = toBinary(abs(occurrences[i]), k);
		for (j = 0; j < k; j++) {
			buffer[++count] = occurrence[j];
		}
		count++;
		free(value);
		free(occurrence);
	}
	fwrite(buffer, sizeof(unsigned char), count, fp);
	fflush(fp);

	fclose(fp);
}
Array Read(int s, int k)
{
        FILE *fp = fopen("test.txt", "rb");
	int *data3;
        int i;
        if (fp == NULL)
        {
                printf("Could not open file\n");
        }
	int count = 0, size = 0;
	int *contents = malloc(s * sizeof(int));
	char buffer[k * 2];
	int c = 0;
	while (1)
	{
		if (feof(fp))
		{
			break;
		}
		for (i = 0; i < k * 2; i++) {
			c = fgetc(fp);
			if (c == -1)
			{
				break;
			}
			buffer[count++] = (char)c;
		}
		if (c == -1)
		{
			break;
		}
		data3 = fromBinary(buffer, k);
		contents[size++] = data3[0];
		contents[size++] = data3[1];
		free(data3);
		count = 0;
	}
        fclose(fp);
	Array occurrences = {contents, size};
	return occurrences;
}
