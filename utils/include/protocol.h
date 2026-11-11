#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdlib.h>
// data
typedef struct data
{

    size_t index;
 
}DATA_PUBULIC;

typedef struct
{
    
    size_t index;
 
}QUEUE_QUBULIC;

typedef struct
{
    
    size_t index;
 
}EVENT_PUBULIC;

DATA_PUBULIC* DATA_INIT();
QUEUE_QUBULIC* QUEUE_INIT();
EVENT_PUBULIC* EVENT_INIT();

#endif