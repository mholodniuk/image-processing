#ifndef PPMIMAGE_H
#define PPMIMAGE_H

#include <stdio.h>

#define MAX_PIXEL_VALUE 255
#define MIN_PIXEL_VALUE 0
#define CHANNELS 3

typedef struct
{
    int*** matrix;
    int row, col, max_gray;
    const char* comment;

} PPMimage;

void sprint(const char* name);

int*** allocate_dynamic_matrix_3D(int row, int col);
void deallocate_dynamic_matrix_3D(int*** matrix, int row, int col);
void readPPM(const char* file_name, PPMimage* image);
void writePPM(const char* file_name, const PPMimage* image);


#endif