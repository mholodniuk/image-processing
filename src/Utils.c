#include "Utils.h"

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void init_Handler(Handler* h)
{
    h->isLoaded = false;
    h->isSaved = false;
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