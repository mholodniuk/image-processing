#ifndef PGMIMAGE_H
#define PGMIMAGE_H

#define MAX_PIXEL_VALUE 255
#define MIN_PIXEL_VALUE 0

#include <stdio.h>

typedef struct
{
    int** matrix;
    int row, col, max_gray;
    const char* comment;

} PGMimage;

int** allocate_dynamic_matrix(int row, int col);
void deallocate_dynamic_matrix(int** matrix, int row);
void readPGM(const char* file_name, PGMimage* image);
void writePGM(const char* file_name, const PGMimage* image);
void negative(PGMimage* image);
void thresholding(PGMimage* image, float level);
void gamma_corection(PGMimage* image, float gamma);
void contouring(PGMimage* image);
void horizontal_blur(PGMimage* image);
void histogram_stretching(PGMimage* image);
void mirror_reflection(PGMimage* image);
void scale(PGMimage* image, unsigned int scale);


#endif