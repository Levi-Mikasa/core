#ifndef TTS_H
#define TTS_H

typedef struct 
{
    int q;
}QUEUE_QUBUL;

typedef struct
{
    int e;
}EVENT_PUBULI;

void* TTS_thread(void* arg);
#endif