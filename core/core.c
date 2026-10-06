#include "core.h"
#include "service_registry.h"
#include "resource_registry.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    void* x;
    SERVICE_NAME thread;
    TYPE type;
    size_t index;
    SERVICE_NAME belong;
}RESOURCE;


RESOURCE* resource_create()
{
    RESOURCE *resource = NULL;

    for (size_t i = 0; i < resource_count; ++i)
    {
        resource = realloc(resource,(i+1)*sizeof(*resource));
        resource[i].type = resource_registry[i].type;
        resource[i].thread = resource_registry[i].thread;
        resource[i].index = resource_registry[i].index;
        resource[i].belong = resource_registry[i].belong;
        switch (resource_registry[i].type)
        {
        case QUEUE: 
            bool found = false;

            for (size_t j = 0; j < i; ++j)
            {
                if (resource_registry[i].type == resource_registry[j].type &&
                    resource_registry[i].thread == resource_registry[j].thread)
                {
                    resource[i].x = resource[j].x;
                    found = true;
                    break;
                }
            }   
            if (!found)
            {           
                QUEUE_QUBULIC *queue = malloc(sizeof(*queue));
                resource[i].x = queue;
            }
                    
            printf("queue point is %p\n",resource[i].x);
            break;

        case EVENT:
            found = false;

            for (size_t j = 0; j < i; ++j)
            {
                if (resource_registry[i].type == resource_registry[j].type &&
                    resource_registry[i].thread == resource_registry[j].thread)
                {
                    resource[i].x = resource[j].x;
                    found = true;
                    break;
                }
            } 
            if (!found)
            {
                QUEUE_QUBULIC *event = malloc(sizeof(*event));
                resource[i].x = event;
            }
            

            printf("event point is %p\n",resource[i].x);
            break;
        
        case DATA:
            found = false;

            for (size_t j = 0; j < i; ++j)
            {
                if (resource_registry[i].type == resource_registry[j].type &&
                    resource_registry[i].thread == resource_registry[j].thread)
                {
                    resource[i].x = resource[j].x;
                    found = true;
                    break;
                }
            } 
            if (!found)
            {
                QUEUE_QUBULIC *data = malloc(sizeof(*data));
                resource[i].x = data;
            }
            

            printf("data point is %p\n",resource[i].x);
            break;
        
        default:
            resource[i].x = NULL;
            break;
        }
    }
    return resource;
      

}

void* DATA_create(SERVICE_NAME THREAD ,RESOURCE* resource)
{
    void** arg = NULL;
    size_t max_index = 0;
    for (size_t i = 0; i < resource_count; ++i)
    {
        if (resource[i].belong & THREAD)
        {
            if (max_index < resource[i].index )
            {
                max_index = resource[i].index;
            }
            
        }
        
    }
    arg = calloc(max_index,sizeof(void*));
    
    for (size_t i = 0; i < resource_count; ++i)
    {
        /* 找到元数据 */
        if (resource[i].belong & THREAD)
        {
            arg[resource[i].index] = resource[i].x;

        
        }
        
    }
    
    return arg;
}

void core_start()
{
    RESOURCE *resource =resource_create();

    for (size_t i = 0; i < service_count; ++i)
    {
        printf("starting service: %s\n",service_registry[i].name);

        pthread_t tid;

        pthread_create(
            &tid,
            NULL,
            service_registry[i].thread,
            DATA_create(service_registry[i].data,resource)
        );
    }
}