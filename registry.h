
#ifndef _REGISTRY_H
#define _REGISTRY_H

typedef struct Table Registry;

Registry* create();
int put(Registry* registry, const char* key, void* value);
void* get(Registry* registry, const char* key);
void* remove(Registry* registry, const char* key);
int* contains(Registry* registry, const char* key);
void* first(Registry* registry);
void* next(Registry* registry);
void destroy(Registry* registery);

#endif