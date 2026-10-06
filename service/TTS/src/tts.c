#include <stdio.h>
#include <tts.h>

void* TTS_thread(void* arg)
{
    void** args = arg;
    QUEUE_QUBUL *queue = args[0];
    EVENT_PUBULI *event1 = args[1];
    printf("TTS thread queue %p\n",queue);
    printf("TTS thread event %p\n",event1);
}