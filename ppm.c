#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "PPMimage.h"
#include "Handler.h"


int main(int argc, char* argv[])
{
    const char* file_path = "images/tests/test.ppm";
    const char* input_image = "images/PPM/kubus.ppm";
    char input = 0;

    Handler* handler = malloc(sizeof(Handler));
    init_Handler(handler);
    PPMimage* img = malloc(sizeof(PPMimage));
    printf("size of PPMimage structure: %ld \n\n", sizeof(img));

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
            if(handler->isLoaded == true) {
                printf("This action will override current image.\n");
            }
            printf("Loading image...\n");
            readPPM(input_image, img);
            handler->isLoaded = true;
            break;

        case '2':
            if(handler->isLoaded == false) {
                printf("You need to load image first!\n");
                break;
            }
            printf("Saving an image...\n");
            writePPM(file_path, img);
            handler->isSaved = true;
            break;
        
        case '3':
            if(handler->isSaved == false) {
                printf("You need to save image first!\n");
                break;
            }
            printf("Showing image...\n");
            show(file_path);
            break;

        case '0':
            if(handler->isLoaded == true) {
                deallocate_dynamic_matrix_3D(img->matrix, img->row, img->col);  // deallocating here, bc user may not want to lose current image data
                break;
            }
            break;

        default:
            printf("Please choose other option\n");
            break;
        }
    }

    return 0;
}