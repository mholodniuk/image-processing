#include "PPMimage.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define CHANNELS 3

// function allocates 3D array for a PGM image
int*** allocate_dynamic_matrix_3D(int row, int col)
{
    int*** ret_matrix;

    ret_matrix = (int***)malloc(sizeof(int**)*row);
    if(ret_matrix == NULL) {
        perror("memory allocation failure!\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<row; ++i) {
        ret_matrix[i] = (int**)malloc(sizeof(int*)*col);

        if(ret_matrix[i] == NULL) {
            perror("memory allocation failure!\n");
            exit(EXIT_FAILURE);
        }
        for(int j=0; j<col; ++j) {
            ret_matrix[i][j] = (int*)malloc(sizeof(int)*CHANNELS);

            if(ret_matrix[i][j] == NULL) {
                perror("memory allocation failure!\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    return ret_matrix;
}
void deallocate_dynamic_matrix_3D(int*** matrix, int row, int col)
{
    for(int i=0; i<row; ++i) {
        for(int j=0; j<col; ++j)
            free(matrix[i][j]);
        free(matrix[i]);
    }
    free(matrix);
}

// function skips comments line in a PPM file
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

// function reads an image into PPMimage struct
void readPPM(const char* file_name, PPMimage* image)
{
    FILE* PPM_file;
    char version[3];
    PPM_file = fopen(file_name, "rb");

    if(PPM_file == NULL) {
        printf("unable to access %s file", file_name);
        //perror("cannot open file!\n");
        exit(EXIT_FAILURE);
    }
    fgets(version, sizeof(version), PPM_file);
    if(strcmp(version,"P3")) {
        fprintf(stderr, "Wrong type of file!\n");
        exit(EXIT_FAILURE);
    }
    skip_comments(PPM_file);

    if (fscanf(PPM_file, "%d %d %d", &image->col, &image->row, &image->max_gray) != 3) {
        fprintf(stderr, " Failed to read image dimensions or gray scale!\n");
        exit(EXIT_FAILURE);
    }

    image->matrix = allocate_dynamic_matrix_3D(image->row, image->col);
    for(int i=0; i<image->row; ++i)
        for(int j=0; j<image->col; ++j)
            for(int k=0; k<CHANNELS; ++k) {
                if(fscanf(PPM_file, "%d", (&image->matrix[i][j][k])) != 1) {
                perror("Error while reading pixels!\n");
                exit(EXIT_FAILURE);
                }
            }   
    fclose(PPM_file);
}

void writePPM(const char* file_name, const PPMimage* image)
{
    FILE* PPM_file;
    const char* version = "P3";
    PPM_file = fopen(file_name, "wb");

    if(PPM_file == NULL) {
        printf("unable to access %s file", file_name);
        //perror("cannot open file!\n");
        exit(EXIT_FAILURE);
    }
    fprintf(PPM_file, "%s\n", version);
    fprintf(PPM_file, "%d %d\n", image->col, image->row);
    fprintf(PPM_file, "%d\n", image->max_gray);
    
    for(int i=0; i<image->row;++i) {
        for(int j=0; j<image->col; ++j) 
            for(int k=0; k<CHANNELS; ++k) {
            fprintf(PPM_file, "%d ", image->matrix[i][j][k]);
        }
        fprintf(PPM_file, "\n");
    }

    fclose(PPM_file);
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