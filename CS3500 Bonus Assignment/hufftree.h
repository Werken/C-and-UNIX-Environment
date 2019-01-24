#ifndef _HUFF
#define _HUFF

#include "matrix.h"

#define MAX_TREE_HT 100
#define idiv(x, y) ((x > 0) ? 1 + (x - 1) / y : (x / y))

typedef struct _Tree {
        int *bin;
        int number;
        int len;
        int size;
        struct MinHeapNode *grab;
} Tree;

typedef struct _Encode {
        int arrS;
        int *arrB;
} Encode;

struct MinHeapNode {
        int data;
        unsigned freq;
        struct MinHeapNode *left, *right;
};

struct MinHeap {
        unsigned size;
        unsigned capacity;
        struct MinHeapNode **array;
};

typedef struct _Array {
        int *contents;
        int size;
} Array;

struct MinHeapNode *newNode(int data, unsigned freq);
struct MinHeap *createMinHeap(unsigned capacity);
Array Consecutive(Matrix *x);
void swapMinHeapNode(struct MinHeapNode **a, struct MinHeapNode **b);
void minHeapify(struct MinHeap *minHeap, int index);
int isSizeOne(struct MinHeap *minHeap);
struct MinHeapNode *extractMin(struct MinHeap *minHeap);
void insertMinHeap(struct MinHeap *minHeap, struct MinHeapNode *minHeapNode);
void buildMinHeap(struct MinHeap *minHeap);
void getArr(int arr[], int n, Tree *collect, int *s);
int isLeaf(struct MinHeapNode *root);
struct MinHeap *createAndBuildMinHeap(int data[], int freq[], int size);
struct MinHeapNode *buildHuffmanTree(int data[], int freq[], int size, struct MinHeap **clear);
void makeCodes(struct MinHeapNode *root, int arr[], int top, Tree *collect, int *s);
void freeCodes(struct MinHeapNode *root, int top);
void HuffmanCodes(int data[], int freq[], int size, Tree *collect, int *s, struct MinHeapNode **fRoot);
unsigned char toBinary(int num);
unsigned char *huffEncode(Encode array, int size);
Encode stringNums(Tree *collect, int *arrT, int size);
void writeCodes(const char *fname, Tree *collect, int size, int *arrT, int dc);
Tree *readCodes(const char *fname, long *filepos, int *dc);
void createArray(int *arr, Matrix *X);
int *revertCodes(int *array, int size);
Matrix makeMatrix(int *code, Tree *tree, int cSize, int tSize);
void EncodeHuffman(const char *fname, Matrix M, int dc);
Matrix DecodeHuffman(const char *fname, long *filepos, Tree **receive, int *dc);

#endif
