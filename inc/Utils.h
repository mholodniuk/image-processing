#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdio.h>

typedef struct {

    bool isLoaded;
    bool isSaved;

} Handler;

void init_Handler(Handler* h);
void show(const char* file_name);
void skip_comments(FILE *fp);

#endif