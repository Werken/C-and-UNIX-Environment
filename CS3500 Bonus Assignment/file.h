#ifndef _FILE
#define _FILE

#define BUF_SIZE 10240 

void Compress(const char *fname, Matrix *data, int quality, int nBlock);
Matrix *Decompress(const char *fname, int w, int h, int quality, int type, long filepos);
Matrix DecodeDCT(Matrix data, int quality, int dc);
Matrix EncodeDCT(Matrix data, int quality, int *dc);

#endif
