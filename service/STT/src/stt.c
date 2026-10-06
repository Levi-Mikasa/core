#include <stdio.h>
#include "stt.h"

void* STT_thread(void* arg)
{
    void** args = arg;
    QUEUE_QUBULI *queue = args[0];
    printf("STT thread queue %p\n",queue);
}