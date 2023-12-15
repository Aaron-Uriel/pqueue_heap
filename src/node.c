#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <dstructs.h>
#include "node.h"

/*
 * Devuelve un apuntador que contiene la dirección de un nodo recién creado,
 * con la dirección del dato ingresado.
 */
struct node *
node_new(void *dataptr)
{
	struct node *const new_node = malloc(sizeof(*new_node));
    if (new_node) {
        new_node->dataptr = dataptr;
        new_node->next = NULL;
        new_node->prev = NULL;
    }
	return new_node;
}

/*
 * Libera el espacio en memoria ocupado por el nodo.
 */
void
node_free(struct node *self)
{
    if (self) { free(self); }
}

