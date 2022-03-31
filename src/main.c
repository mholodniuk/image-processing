#include "../inc/Utils.h"
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if(argc != 2) {
        fprintf(stderr, "%s", "Not enough arguments!\nUse: ./bin/main [pgm]/[ppm]\n");
        return 1;
    }
    if(strcmp(argv[1], "pgm") == 0) {
        run_PGM();
    }
    if(strcmp(argv[1], "ppm") == 0) {
        run_PPM();
    }
    return 0;
}