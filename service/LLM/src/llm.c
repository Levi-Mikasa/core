#include <stdio.h>
#include "llm.h"
#include "protocol.h"



void* LLM_thread(void* arg)
{
    void** args = arg;
    QUEUE_QUBULIC* queue1 = args[0];
    QUEUE_QUBULIC* queue2 = args[1];
    EVENT_PUBULIC* event1 = args[2];
    printf("LLM thread queue1 addreas is %p value is %d,\n",queue1,queue1->index);
    printf("LLM thread queue2 addreas is %p value is %d,\n",queue2,queue2->index);
    printf("LLM thread event1 addreas is %p value is %d,\n",event1,event1->index);

    queue1->index+=6;
    queue2->index+=24;
    event1->index+=33;

}