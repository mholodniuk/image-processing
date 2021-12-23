#ifndef HANDLER_H
#define HANDLER_H

#include <stdbool.h>

typedef struct {

    bool isLoaded;
    bool isSaved;

} Handler;

void init_Handler(Handler* h);

#endif