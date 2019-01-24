#ifndef _FILE
#define _FILE

#define BUF_SIZE 10240 
#define idiv(x, y) ((x > 0) ? 1 + (x - 1) / y : (x / y))

void Compress(const char *fname, Matrix *data, int quality, int nBlock);
Matrix *Decompress(const char *fname, int w, int h, int quality, int type, long filepos);
Matrix DecodeDCT(Matrix data, int quality, int dc);
Matrix DecodeRunlength(const char *fname, int *dc, long *filepos);
Matrix EncodeDCT(Matrix data, int quality, int *dc);
void EncodeRunlength(const char *filename, Matrix data, int dc);
void Write(int *occurrences, int s, const char *filename, int dc);
Array Read(const char *fname, long *filepos, int *dc);

#endif
