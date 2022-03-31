#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdio.h>

typedef struct {

    bool isLoaded;
    bool isSaved;

} Handler;

void show(const char* file_name);
void init_Handler(Handler* h);
void skip_comments(FILE *fp);
void run_PGM();
void run_PPM();

#endif