#include <stdio.h>
#include <tts.h>
#include "protocol.h"

void* TTS_thread(void* arg)
{
    void** args = arg;
    QUEUE_QUBULIC *queue1 = args[0];
    EVENT_PUBULIC *event1 = args[1];
    printf("TTS thread queue1 addreas is %p value is %d,\n",queue1,queue1->index);
    printf("TTS thread event1 addread is %p value is %d,\n",event1,event1->index);
    int i=10000;
    while (i != 0)
    {
        i--;

    }
    printf("(after)TTS thread queue1 addreas is %p value is %d,\n",queue1,queue1->index);
    printf("(after)TTS thread event1 addread is %p value is %d,\n",event1,event1->index);
    
}