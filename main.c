#include <stdio.h>
#include <stdbool.h>
#include "PPMimage.h"
#include "PGMimage.h"

typedef struct {

    bool isLoaded;
    bool isSaved;

} Handler;

void init_Handler(Handler* h)
{
    h->isLoaded = false;
    h->isSaved = false;
}

int main(int argc, char* argv[])
{
    const char* file_path = "images/tests/test.pgm";
    char input = 0;

    Handler handler;
    init_Handler(&handler);
    PGMimage image_in;
    PGMimage* image_out;

    printf("\t\tMenu\n");
    printf("\t1 - Load an image\n");
    printf("\t2 - Save an image\n");
    printf("\t3 - Show saved image\n");
    printf("\t0 - Exit\n");

    while(input != '0') {
        scanf("%c", &input);
        (void)getchar();
        
        switch (input)
        {
        case '1':
            printf("Loading image...\n");
            image_out = readPGM("images/PGM/Lena.pgm", &image_in);
            handler.isLoaded = true;
            break;

        case '2':
            if(handler.isLoaded == false) {
                printf("You need to load image first!\n");
                break;
            }
            printf("Saving an image...\n");
            writePGM(file_path, image_out);
            break;
        
        case '3':
            if(handler.isSaved == false) {
                printf("You need to save image first!\n");
                break;
            }
            show(file_path);
            break;

        case '0':
            break;

        default:
            printf("Please choose other option\n");
            break;
        }
    }

    return 0;
}