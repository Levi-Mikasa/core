#include <stdio.h>
#include "stt.h"
#include "protocol.h"

void* STT_thread(void* arg)
{
    void** args = arg;
    QUEUE_QUBULIC *queue1 = args[0];
    printf("STT thread queue1 addreas is %p value is %d,\n",queue1,queue1->index);
    int i = 10000;
    while (i != 0)
    {
        i--;

    }

    printf("(after)STT thread queue1 addreas is %p value is %d,\n",queue1,queue1->index);
}