#ifndef SERVICE_REGISTRY_H
#define SERVICE_REGISTRY_H

#include <stddef.h>
#include "resource_registry.h"
typedef struct
{
    const char *name;
    void *(*thread)(void *arg);
    SERVICE_NAME data;
} ServiceDefinition;

extern const ServiceDefinition service_registry[];
extern const size_t service_count;

#endif