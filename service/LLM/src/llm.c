#include <stdio.h>
#include "llm.h"

void* LLM_thread(void* arg)
{
    void** args = arg;
    QUEUE_QUBULIC* queue1 = args[0];
    QUEUE_QUBULIC* queue2 = args[1];
    EVENT_PUBULIC* event1 = args[2];
    printf("LLM thread queue %p\n",queue1);
    printf("LLM thread queue %p\n",queue2);
    printf("LLM thread event %p\n",event1);
}