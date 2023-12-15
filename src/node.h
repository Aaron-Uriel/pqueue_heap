#include <stdint.h>

#ifndef NODE_H
#define NODE_H

struct node {
    void *dataptr;
    struct node *next;
    struct node *prev;
};
struct node *node_new(void *dataptr);
void node_free(struct node *self);

#endif
