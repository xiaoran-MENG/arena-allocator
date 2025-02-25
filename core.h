#ifndef _CORE_H
#define _CORE_H

typedef enum
{
   FALSE,
   TRUE
} Boolean;

typedef int (*Comparator)(void *value, void *other);

typedef struct Table Table;

void validate(Table *table);
Table *create(Comparator comparator);
Boolean add(Table *table, void *value);
void *remove(Table *table, void *value);
void *clear(Table *table);
void *search(Table *table, void *value);
void *first(Table *table);
void *next(Table *table);
void *destroy(Table *table);

#endif