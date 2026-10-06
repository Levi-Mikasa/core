#ifndef LLM_H
#define LLM_H

typedef struct queue
{
    int q;
}QUEUE_QUBULIC;

typedef struct event
{
    int e;
}EVENT_PUBULIC;
void* LLM_thread(void* arg);
#endif