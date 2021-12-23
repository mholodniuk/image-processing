#ifndef PGMIMAGE_H
#define PGMIMAGE_H

#include <stdio.h>

typedef struct
{
    int** matrix;
    int row, col, max_gray;
    const char* comment;

} PGMimage;

int** allocate_dynamic_matrix(int row, int col);
void deallocate_dynamic_matrix(int** matrix, int row);
void skip_comments(FILE *fp);
void skip_comments_mucha(FILE *fp);
PGMimage* readPGM(const char* file_name, PGMimage* image);
void writePGM(const char* file_name, const PGMimage* image);
void show(const char* file_name);

#endif