#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "core.h"

typedef struct Node
{
    void *value;
    Node *next;
} Node;

struct Table
{
    Node *top;
    Node *traverser;
    int size;
    int traversals_count;
    Comparator comparator;
};

void validate(Table *table)
{
}

Table *create(Comparator comparator)
{
    Table *table = malloc(sizeof(Table));
    if (NULL == table) return NULL;
    table->top = NULL;
    table->traverser = NULL;
    table->size = 0;
    table->traversals_count = 0;
    table->comparator = comparator;
    return table;
}

Boolean add(Table *table, void *value)
{
    validate(table);
    assert(value);
    if (!value) return FALSE;
    Boolean result = FALSE;
    Node *node = malloc(sizeof(Node));
    assert(node);
    if (!node) return FALSE;
    node->value = value;
    Node *current = NULL, *previous = NULL;

    if (!table->comparator)
    {
        current = table->top;
        assert(!current || current->value);
        // 3
        // 1 2 4
        //     c
        //   p
        while (current && table->comparator(value, current->value) > 0)
        {
            previous = current;
            current = current->next;
        }
    }

    if (previous)
    {
        node->next = previous->next;
        previous->next = node;
    } 
    else
    {
        node->next = table->top;
        table->top = node;
    }

    table->size++;
    validate(table);
    return TRUE;
}

void *remove(Table *table, void *value)
{
    validate(table);
    assert(table->comparator);
    assert(value);
    if (!value) return NULL;
    Node *current = table->top;
    Node *previous = NULL;
    while (current && table->comparator(value, current->value) != 0)
    {
        previous = current;
        current = current->next;
    }
    if (!current) return NULL;
    if (previous) previous->next = current->next;
    else table->top = current->next;
    void *result = current->value;
    free(current);
    table->size--;
    validate(table);
    return result;
}

void *clear(Table *table)
{
    validate(table);
    while (table->top)
    {
        Node *current = table->top;
        table->top = table->top->next;
        free(current);
    }
    table->size = 0;
    validate(table);
}

void *search(Table *table, void *value)
{
    validate(table);
    assert(table->comparator);
    assert(value);
    if (!value) return NULL;
    for (Node *current = table->top; current; current = current->next)
    {
        assert(current->value);
        if (table->comparator(value, current->value) == 0) return current->value;
    }
    return NULL;
}

void *first(Table *table)
{
    validate(table);
    if (!table->top) return NULL;
    table->traverser = table->top->next;
    table->traversals_count = 1;
    assert(table->traversals_count <= table->size);
    assert(table->top->value);
    return table->top->value;
}

void *next(Table *table)
{
    validate(table);
    if (!table->traverser) return NULL;
    void *result = table->traverser->value;
    assert(result);
    table->traverser = table->traverser->next;
    table->traversals_count++;
    assert(table->traversals_count <= table->size);
    return result;
}

void *destroy(Table *table)
{
    clear(table);
    free(table);
}
