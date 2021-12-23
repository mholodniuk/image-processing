#include <stdio.h>
#include <stdbool.h>
#include "PPMimage.h"
#include "PGMimage.h"
#include "Handler.h"


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
    printf("\t4 - Negative\n");
    printf("\t0 - Exit\n");

    while(input != '0') {
        scanf("%c", &input);
        (void)getchar();
        
        switch (input)
        {
        case '1':
            if(handler.isLoaded == true) {
                printf("This action will override current image.\n");
            }
            printf("Loading image...\n");
            image_out = readPGM("images/PGM/Lena2.pgm", &image_in);
            handler.isLoaded = true;
            break;

        case '2':
            if(handler.isLoaded == false) {
                printf("You need to load image first!\n");
                break;
            }
            printf("Saving an image...\n");
            writePGM(file_path, image_out);
            handler.isSaved = true;
            break;
        
        case '3':
            if(handler.isSaved == false) {
                printf("You need to save image first!\n");
                break;
            }
            show(file_path);
            break;

        case '4':
            if(handler.isLoaded == false) {
                printf("You need to load image first!\n");
                break;
            }
            printf("Performing transformation\n");
            negative(image_out);
            break;

        case '0':
            break;

        default:
            deallocate_dynamic_matrix(image_out->matrix, image_out->row);  // deallocation here, bc user may not want to forget current image
            printf("Please choose other option\n");
            break;
        }
    }

    return 0;
}