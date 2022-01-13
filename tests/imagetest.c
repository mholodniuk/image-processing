#include <criterion/criterion.h>

#include "../inc/PGMimage.h"
// to run test the library has to not include main.c file
// otherwise it runs main instead of test (idk why)

Test(imagetest, dummytest) {
    PGMimage* img = malloc(sizeof(PGMimage));
    cr_expect(img != NULL, "this pointer should not be null");
}