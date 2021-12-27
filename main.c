#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "PPMimage.h"
#include "PGMimage.h"
#include "Handler.h"


int main(int argc, char* argv[])
{
    const char* file_path = "images/tests/test.pgm";
    const char* input_image = "images/PGM/Lena.pgm";
    char input = 0;

    Handler* handler = malloc(sizeof(Handler));
    init_Handler(handler);
    PGMimage* img = malloc(sizeof(PGMimage));
    printf(" size of PGMimage structure: %ld \n\n", sizeof(img));

    printf("\t\tMenu\n");
    printf("\t1 - Load an image\n");
    printf("\t2 - Save an image\n");
    printf("\t3 - Show saved image\n");
    printf("\t4 - Negative\n");
    printf("\t5 - Thresholding\n");
    printf("\t6 - Gamma correction\n");
    printf("\t7 - Contouring\n");
    printf("\t8 - Horizontal blur\n");
    printf("\t9 - Histogram stretching\n");
    printf("\ta - Mirror reflection\n");
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
            readPGM(input_image, img);
            handler->isLoaded = true;
            break;

        case '2':
            if(handler->isLoaded == false) {
                printf("You need to load image first!\n");
                break;
            }
            printf("Saving an image...\n");
            writePGM(file_path, img);
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

        case '4':
            if(handler->isLoaded == false) {
                printf("You need to load image first!\n");
                break;
            }
            printf("Performing transformation - negative\n");
            negative(img);
            break;

        case '5':
            if(handler->isLoaded == false) {
                printf("You need to load image first!\n");
                break;
            }
            printf("Performing transformation - thresholding\n");
            thresholding(img, 69);
            break;

        case '6':
            if(handler->isLoaded == false) {
                printf("You need to load image first!\n");
                break;
            }
            printf("Performing transformation - gamma correction\n");
            gamma_corection(img, 2.5);
            break;

        case '7':
            if(handler->isLoaded == false) {
                printf("You need to load image first!\n");
                break;
            }
            printf("Performing transformation - contouring\n");
            contouring(img);
            break;

        case '8':
            if(handler->isLoaded == false) {
                printf("You need to load image first!\n");
                break;
            }
            printf("Performing transformation - blur\n");
            horizontal_blur(img);
            break;  

        case '9':
            if(handler->isLoaded == false) {
                printf("You need to load image first!\n");
                break;
            }
            printf("Performing transformation - histogram stretching\n");
            histogram_stretching(img);
            break;
        
        case 'a':
            if(handler->isLoaded == false) {
                printf("You need to load image first!\n");
                break;
            }
            printf("Performing transformation - mirror reflection\n");
            mirror_reflection(img);
            break;  

        case '0':
            if(handler->isLoaded == true) {
                deallocate_dynamic_matrix(img->matrix, img->row);  // deallocating here, bc user may not want to lose current image data
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