#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hufftree.h"

struct MinHeapNode *newNode(int data, unsigned freq) {
	struct MinHeapNode *temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));

	temp->left = temp->right = NULL;
	temp->data = data;
	temp->freq = freq;
	return temp;
}
struct MinHeap *createMinHeap(unsigned capacity) {
	struct MinHeap *minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));

	minHeap->size = 0;
	minHeap->capacity = capacity;
	minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
	return minHeap;
}
Array Consecutive(Matrix *x) {
        int values[N * N];
        int freq[N * N];
        int i, j, count = 0;
	for (i = 0; i < N * N; i++) {
		values[i] = -255;
		freq[i] = -255;
	}
	int matrix[N * N];
	for (i = 0; i < N; i++) {
                for (j = 0; j < N; j++) {
			matrix[i * N + j] = (int)x->element[i][j];
		}
	}
        for (i = 0; i < N * N; i++) {
                for (j = 0; j < N * N; j++) {
			if (matrix[i] == values[j]) {
				freq[j] += 1;
				break;
			}	
                        else if (values[j] == -255) {
                                values[j] = matrix[i];
                                freq[j] = 1;
                                count++;
                                break;
                        }
                }
        }
        int *contents = malloc(sizeof(int) * count * 2);
        for (i = 0; i < count * 2; i+=2) {
                contents[i] = values[i / 2];
                contents[i + 1] = freq[i / 2];
        }
        Array group = {contents, count * 2};
        return group;
}
void swapMinHeapNode(struct MinHeapNode **a, struct MinHeapNode **b) {
	struct MinHeapNode *tmp = *a;
	*a = *b;
	*b = tmp;
}
void minHeapify(struct MinHeap *minHeap, int index) {
	int smallest = index;
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	
	if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
		smallest = left;
	if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
		smallest = right;
	if (smallest != index) {
		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[index]);
		minHeapify(minHeap, smallest);
	}
}
int isSizeOne(struct MinHeap *minHeap) {
	return (minHeap->size == 1);
}

struct MinHeapNode *extractMin(struct MinHeap *minHeap) {
	struct MinHeapNode *temp = minHeap->array[0];
	minHeap->array[0] = minHeap->array[minHeap->size - 1];
	--minHeap->size;
	minHeapify(minHeap, 0);
	return temp;
}

void insertMinHeap(struct MinHeap *minHeap, struct MinHeapNode *minHeapNode) {
	++minHeap->size;
	int i = minHeap->size - 1;
	while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
		minHeap->array[i] = minHeap->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}
	minHeap->array[i] = minHeapNode;
}
void buildMinHeap(struct MinHeap *minHeap) {
	int n = minHeap->size - 1;
	int i;
	for (i = (n - 1) / 2; i >= 0; --i)
		minHeapify(minHeap, i);
}
void getArr(int arr[], int n, Tree *collect, int *s) {
	int i;
	collect[*s].bin = malloc(sizeof(int) * n);
	collect[*s].len = n;
	for (i = 0; i < n; i++) {
		collect[*s].bin[i] = arr[i];
	}
	*s += 1;
}
int isLeaf(struct MinHeapNode *root) {
	return !(root->left) && !(root->right);
}

struct MinHeap *createAndBuildMinHeap(int data[], int freq[], int size) {
	struct MinHeap *minHeap = createMinHeap(size);
	int i;
	for (i = 0; i < size; i++)
		minHeap->array[i] = newNode(data[i], freq[i]);
	minHeap->size = size;
	buildMinHeap(minHeap);
	return minHeap;
}

struct MinHeapNode *buildHuffmanTree(int data[], int freq[], int size, struct MinHeap **clear) {
	struct MinHeapNode *left, *right, *top;
	struct MinHeap *minHeap = createAndBuildMinHeap(data, freq, size);
	while (!isSizeOne(minHeap)) {
		left = extractMin(minHeap);
		right = extractMin(minHeap);
		top = newNode(255, left->freq + right->freq);
		top->left = left;
		top->right = right;
		insertMinHeap(minHeap, top);
	}
	*clear = minHeap;
	return extractMin(minHeap);
}
void makeCodes(struct MinHeapNode *root, int arr[], int top, Tree *collect, int *s) {
	if (root->left) {
		arr[top] = 0;
		makeCodes(root->left, arr, top + 1, collect, s);
	}
	if (root->right) {
		arr[top] = 1;
		makeCodes(root->right, arr, top + 1, collect, s);
	}
	if (isLeaf(root)) {
		collect[*s].number = root->data;
		getArr(arr, top, collect, s);
	}
}
void freeCodes(struct MinHeapNode *root, int top) {
        if (root->left) {
                freeCodes(root->left, top + 1);
        }
        if (root->right) {
                freeCodes(root->right, top + 1);
        }
	free(root);
}
void HuffmanCodes(int data[], int freq[], int size, Tree *collect, int *s, struct MinHeapNode **fRoot) {
	struct MinHeap *clear;
	struct MinHeapNode *root = buildHuffmanTree(data, freq, size, &clear);
	int arr[MAX_TREE_HT], top = 0;
	makeCodes(root, arr, top, collect, s);
	*fRoot = root;
	free(clear->array);
	free(clear);
}
unsigned char toBinary(int num) {
	int i, y;
	unsigned char binNum = 0;
	for (i = 0; i < 8; i++) {
		y = (num & (1 << i)) >> i;
                if (y == 1) binNum = binNum | (1 << i);
	}
	return binNum;
}
unsigned char *huffEncode(Encode array, int size) {
	int bytes = size / 8;
	if (size % 8 != 0) bytes++;
	unsigned char *buffer = malloc(sizeof(unsigned char) * bytes);
	memset(buffer, 0, sizeof(unsigned char) * bytes);
	int i, cur = 0, loop = 0;
	while (loop != size) {
		for (i = 0; i < 8; i++) {
			if (cur * 8 + i == size) {
				loop = size;
				break;
			}
			if (array.arrB[(cur * 8) + i] == 1) buffer[cur] = buffer[cur] | (1 << (7 - i));
		}
		cur++;
	}
	return buffer;
}
Encode stringNums(Tree *collect, int *arrT, int size) {
	int i, j, k, count = 0;
	Encode strings;
	strings.arrB = malloc(sizeof(int));
	for (i = 0; i < N * N; i++) {
		for (j = 0; j < size; j++) {
			if (arrT[i] == collect[j].number) {
				count += collect[j].len;
				strings.arrB = realloc(strings.arrB, sizeof(int) * count);
				for (k = 0; k < collect[j].len; k++) {
					strings.arrB[count - collect[j].len + k] = collect[j].bin[k];
				}
			}
		}
	}
	strings.arrS = count;
	return strings;
}
void writeCodes(const char *fname, Tree *collect, int size, int *arrT, int dc) {
	FILE *fp = fopen(fname, "a+b");
	int number, length;
	Encode array = stringNums(collect, arrT, size);
	unsigned char ave;
	ave = toBinary(dc);
	fwrite(&ave, sizeof(unsigned char), 1, fp);
	fwrite(&size, sizeof(unsigned char), 1, fp);
	int i, j;
	for (i = 0; i < size; i++) {
		collect[i].number += 150;
		number = toBinary(collect[i].number);
		collect[i].number -= 150;
		length = toBinary(collect[i].len);
		fwrite(&number, sizeof(unsigned char), 1, fp);
		fwrite(&length, sizeof(unsigned char), 1, fp);
		for (j = 0; j < collect[i].len; j++) fwrite(&collect[i].bin[j], sizeof(unsigned char), 1, fp);
	}
	fwrite(&array.arrS, sizeof(unsigned char), 1, fp);
	unsigned char *bits = huffEncode(array, array.arrS);
	fwrite(bits, sizeof(unsigned char), idiv(array.arrS, 8), fp);
	free(bits);
	free(array.arrB);
	fclose(fp);
}
Tree *readCodes(const char *fname, long *filepos, int *dc) {
	FILE *fp = fopen(fname, "rb");
	fseek(fp, *filepos, SEEK_SET);
	if (fp == NULL) {
		printf("Could not open file\n");
	}
	Tree *collect = malloc(sizeof(Tree));
	int cur = 0, i, j;
	unsigned char buf;
	fread(&buf, sizeof(unsigned char), 1, fp);
	*dc = (int)buf;
	fscanf(fp, "%c", &buf);
	int loop = (int)buf;
	for (i = 0; i < loop; i++) {
		fread(&buf, sizeof(unsigned char), 1, fp);
		collect[cur].number = (int)buf;
		//collect[cur].number -= 150;
		fread(&buf, sizeof(unsigned char), 1, fp);
		collect[cur].len = (int)buf;
		collect[cur].bin = malloc(sizeof(int) * collect[cur].len);
		for (j = 0; j < collect[cur].len; j++) { 
			fread(&buf, sizeof(unsigned char), 1, fp);
			collect[cur].bin[j] = (int)buf;
		}
		cur++;
		collect = realloc(collect, sizeof(Tree) * (cur + 1));
	}	
	fread(&buf, sizeof(unsigned char), 1, fp);
	int tSize = (int)buf;
	collect[cur].len = tSize;
	collect[cur].size = idiv(tSize, 8);
	collect[cur].bin = malloc(sizeof(int) * idiv(tSize, 8));
	for (i = 0; i < idiv(tSize, 8); i++) {
		fread(&buf, sizeof(unsigned char), 1, fp);
		collect[cur].bin[i] = (int)buf;
	}
	collect[0].size = cur;
	*filepos = ftell(fp);
	fclose(fp);
	return collect;
}
void createArray(int *arr, Matrix *X) {
	int i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			arr[(i * N) + j] = X->element[i][j];
		}
	}
}
int *revertCodes(int *array, int size) {
        int *buffer = malloc(sizeof(int) * size);
        memset(buffer, 0, sizeof(int) * size);
        int i, cur = 0, loop = 0, y;
        while (loop != size) {
                for (i = 0; i < 8; i++) {
                        if (cur * 8 + i == size) {
                                loop = size;
                                break;
                        }
			y = (array[cur] & (1 << (7 - i))) >> (7 - i);
			buffer[cur * 8 + i] = y;
                }
                cur++;
        }
        return buffer;
}
Matrix makeMatrix(int *code, Tree *tree, int cSize, int tSize) {
	int i, j, k, l, count = 0, temp = 0, mCount = 0;
	int buffer[20], mArray[N * N];
	for (i = 0; i < 20; i++) buffer[i] = 255;
	for (i = 0; i < cSize; i++) {
		buffer[temp++] = code[count++];
		for (j = 0; j < tSize; j++) {
			for (k = 0; k < 20; k++) {
				if (buffer[k] != tree[j].bin[k]) break;
				if (k == tree[j].len - 1) {
					mArray[mCount++] = tree[j].number;
					for (l = 0; l < tree[j].len; l++) buffer[l] = 255;
					temp = 0;
					break;
				}
			}
		}
	}
	Matrix Q;
	for (i = 0; i < N; i++) {
                for (j = 0; j < N; j++) {
                        Q.element[i][j] = 0;
                }
        }
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			Q.element[i][j] = mArray[(i * N) + j];
		}
	}
	return Q;
}
void EncodeHuffman(const char *fname, Matrix M, int dc) {
	int s = 0;
        Tree *collect;
        int *arrT = malloc(sizeof(int) * N * N);
        createArray(arrT, &M);
        Array consec = Consecutive(&M);
        int i, arr[consec.size / 2], freq[consec.size / 2], count = 0;
        for (i = 0; i < consec.size; i += 2) {
                arr[count] = consec.contents[i];
                freq[count] = consec.contents[i + 1];
                count++;
        }
        collect = malloc(sizeof(Tree) * (consec.size / 2));
        int size = sizeof(arr) / sizeof(arr[0]);
        struct MinHeapNode *fRoot;
        HuffmanCodes(arr, freq, size, collect, &s, &fRoot);
        writeCodes(fname, collect, consec.size / 2, arrT, dc);
        for (i = 0; i < consec.size / 2; i++) {
                free(collect[i].bin);
        }
        free(collect);
        free(consec.contents);
        free(arrT);
        freeCodes(fRoot, 0);
}
Matrix DecodeHuffman(const char *fname, long *filepos, Tree **receive, int *dc) {
	Tree *get = readCodes(fname, filepos, dc);
	int *hCodes = revertCodes(get[get[0].size].bin, get[get[0].size].len);
        Matrix X = makeMatrix(hCodes, get, get[get[0].size].len, get[0].size);
	*receive = get;
        free(hCodes);
	return X;
}
