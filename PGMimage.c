#include "PGMimage.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

// function allocates 2D array for a PGM image
int** allocate_dynamic_matrix(int row, int col)
{
    int** ret_matrix;

    ret_matrix = (int**)malloc(sizeof(int*)*row);
    if(ret_matrix == NULL) {
        perror("memory allocation failure!\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<row; ++i) {
        ret_matrix[i] = (int*)malloc(sizeof(int)*col);
        if(ret_matrix[i] == NULL) {
            perror("memory allocation failure!\n");
            exit(EXIT_FAILURE);
        }
    }
    return ret_matrix;
}

// function deallocates 2D array for a PGM image
void deallocate_dynamic_matrix(int** matrix, int row)
{
    for(int i=0; i<row; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

// function skips comments line in a PGM file
void skip_comments(FILE *fp)
{
    int ch;
    char line[100];
    while((ch = fgetc(fp)) != EOF && isspace(ch)) {
        ;
    }
    if(ch == '#') {
        fgets(line, sizeof(line), fp);
        skip_comments(fp);
    }
    else {
        fseek(fp, -1, SEEK_CUR);
    }
}

// other function that skips comments line in a PGM file
void skip_comments_mucha(FILE *fp)
{
    int ch = 0;
    bool end = false;
    char line[100];
    
    do {
        if((ch=fgetc(fp)) == '#') {
            if(fgets(line, sizeof(line), fp) == NULL) 
                end = true;
        }
        else {
            ungetc(ch, fp);
        }
    } while(ch=='#' && !end);
}

// function reads an image into PGMimage struct
void readPGM(const char* file_name, PGMimage* image)
{
    FILE* PGM_file;
    char version[3];
    PGM_file = fopen(file_name, "rb");

    if(PGM_file == NULL) {
        printf("unable to access %s file", file_name);
        //perror("cannot open file!\n");
        exit(EXIT_FAILURE);
    }
    fgets(version, sizeof(version), PGM_file);
    if(strcmp(version,"P2")) {
        fprintf(stderr, "Wrong type of file!\n");
        exit(EXIT_FAILURE);
    }
    skip_comments(PGM_file);

    if (fscanf(PGM_file, "%d %d %d", &image->col, &image->row, &image->max_gray) != 3) {
        fprintf(stderr, " Failed to read image dimensions or gray scale!\n");
        exit(EXIT_FAILURE);
    }

    image->matrix = allocate_dynamic_matrix(image->row, image->col);
    for(int i=0; i<image->row; ++i)
        for(int j=0; j<image->col; ++j)
            if(fscanf(PGM_file, "%d", (&image->matrix[i][j])) != 1) {
                perror("Error while reading pixels!\n");
                exit(EXIT_FAILURE);
            }
    fclose(PGM_file);
}

void writePGM(const char* file_name, const PGMimage* image)
{
    FILE* PGM_file;
    const char* version = "P2";
    PGM_file = fopen(file_name, "wb");

    if(PGM_file == NULL) {
        printf("unable to access %s file", file_name);
        //perror("cannot open file!\n");
        exit(EXIT_FAILURE);
    }
    fprintf(PGM_file, "%s\n", version);
    fprintf(PGM_file, "%d %d\n", image->col, image->row);
    fprintf(PGM_file, "%d\n", image->max_gray);
    
    for(int i=0; i<image->row;++i) {
        for(int j=0; j<image->col; ++j) {
            fprintf(PGM_file, "%d ", image->matrix[i][j]);
        }
        fprintf(PGM_file, "\n");
    }

    fclose(PGM_file);
    //deallocate_dynamic_matrix(image->matrix, image->row);
}

// function shows chosen image (ImageMagick required (for Linux))
void show(const char* file_name)
{
    char command[100];
    strcpy(command, "display ");
    strcat(command, file_name);
    strcat(command, " &");
    //printf("%s\n", command);
    system(command);
}

void negative(PGMimage* image)
{
    for(int i=0; i<image->row; ++i)
        for(int j=0; j<image->col; ++j)
            image->matrix[i][j] = image->max_gray - image->matrix[i][j];
}

void thresholding(PGMimage* image, float level)
{
    if(level<=0) {
        perror("Thresholding level can not be negative!");  //change for abs(level<0)
        exit(EXIT_FAILURE);
    }
    int th_level = (int)(image->max_gray*(level/100));

    for(int i=0; i<image->row; ++i)
        for(int j=0; j<image->col; ++j) {
            if(image->matrix[i][j] <= th_level) image->matrix[i][j] = 0;
            if(image->matrix[i][j] > th_level) image->matrix[i][j] = image->max_gray;
        }
}

void gamma_corection(PGMimage* image, float gamma)
{
    if(gamma<=0) {
        perror("Gamma correction ratio can not be negative!");  //change for abs(level<0)
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<image->row; ++i)
        for(int j=0; j<image->col; ++j)
            image->matrix[i][j] = pow((double)image->matrix[i][j]/image->max_gray, 1/gamma)*image->max_gray;
}

void contouring(PGMimage* image)
{
    int x, y;
    for(int i=0; i<image->row; ++i)
        for(int j=0; j<image->col; ++j) {
            if(i+1<image->row) {
                x = abs(image->matrix[i+1][j] - image->matrix[i][j]);
            } else x = 0;
            if(j+1<image->col) {
                y = abs(image->matrix[i][j+1] - image->matrix[i][j]);
            } else y = 0;
            image->matrix[i][j] = x + y;
        }
}

// does not work, but previous version worked ???
void horizontal_blur(PGMimage* image, int range)
{
    int tmp = 0;
    for(int i=0; i<image->row; ++i) {
        for(int j=0; j<image->col; ++j) {
            if(i+range<image->row && i>range-1)
            {
                for(int k=0; k<range; ++k) {
                    tmp += (image->matrix[i+k][j] + image->matrix[i-k][j]);
                }
                tmp -= image->matrix[i][j];  //to delete one extra matrix[x][y] value (for k=0)
                image->matrix[i][j] = (1/range)*tmp;
                tmp = 0;
            }
        }
    } 
}

void histogram_stretching(PGMimage* image)
{
    int local_max=0, local_min=255;
    for(int i=0; i<image->row; ++i)
        for(int j=0; j<image->col; ++j) {
            int tmp = image->matrix[i][j];
            if(tmp>local_max) 
                local_max = tmp;
            if(tmp<local_min) 
                local_min = tmp;
        }
    image->max_gray = local_max;
    //printf("local min: %d, local max_ %d\n", local_max, local_min);
    for(int i=0; i<image->row; ++i)
        for(int j=0; j<image->col; ++j)
            image->matrix[i][j] = (image->matrix[i][j]-local_min)*MAX_PIXEL_VALUE/(local_max-local_min);
}