#ifndef PPMIMAGE_H
#define PPMIMAGE_H

#include <stdio.h>

typedef struct
{
    int*** matrix;
    int row, col, max_gray;
    const char* comment;

} PPMimage;

void sprint(const char* name);

//int*** allocate_dynamic_matrix(int row, int col);
//void deallocate_dynamic_matrix(int*** matrix, int row);
void skip_comments(FILE *fp);
void skip_comments_mucha(FILE *fp);
PPMimage* readPPM(const char* file_name, PPMimage* image);
void writePPM(const char* file_name, const PPMimage* image);
void show(const char* file_name);

#endif