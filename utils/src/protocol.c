#include <protocol.h>

DATA_PUBULIC* DATA_INIT()
{
    DATA_PUBULIC* DATA = malloc(sizeof(DATA_PUBULIC*));
    DATA->index = 0;
    return DATA;
}
QUEUE_QUBULIC* QUEUE_INIT()
{
    QUEUE_QUBULIC* QUEUE = malloc(sizeof(QUEUE_QUBULIC*));
    QUEUE->index = 10;
    return QUEUE;
}
EVENT_PUBULIC* EVENT_INIT()
{
    EVENT_PUBULIC* EVENT = malloc(sizeof(EVENT_PUBULIC*));
    EVENT->index = 100;
    return EVENT;
}