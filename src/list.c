#include <dstructs.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "node.h"

/*
 * Crea una nueva instancia de lista enlazada, esta instancia se crea vacía
 * sin ningún elemento.
 */
struct linked_list *
linked_list_new(void) {
    struct linked_list *new_list = calloc(1, sizeof(*new_list));
    return new_list;
}

/*
 * Agrega un elemento en una posición arbitraria de la lista. En casos donde
 * el elemento a insertar se inserta al inicio o final, esta función llama a
 * sus funciones correspondientes automáticamente.
 */
int32_t
linked_list_add(struct linked_list *self, void *dataptr, size_t index)
{
    if (self && dataptr && index <= self->size) {
        if (index == self->size) { linked_list_add_last(self, dataptr); }
        else if (index == 0) { linked_list_add_first(self, dataptr); }
        else {
            struct node *added_node = node_new(dataptr);
            if (!added_node) { return 1; }
            size_t count = 0;
            struct node *current_node = self->head, *prev_node;
            while (current_node != NULL) {
                if (count == index) {
                    prev_node->next = added_node;
                    added_node->prev = prev_node;
                    added_node->next = current_node;
                    current_node->prev = added_node;
                    self->size += 1;
                    return 0;
                }
                count += 1;
                prev_node = current_node;
                current_node = current_node->next;
            }
        }
    }
    return 1;
}

/*
 * Añade la dirección de un dato al inicio de la lista.
 */
int32_t
linked_list_add_first(struct linked_list *self, void *dataptr)
{
    if (self && dataptr) {
        struct node *added_node = node_new(dataptr);
        if (!added_node) { return 1; }
        if (self->head) {
            added_node->next = self->head;
            self->head->prev = added_node;
        }
        self->head = added_node;
        if (self->size == 0) { self->tail = added_node; }
        self->size += 1;
    }
    return 0;
}

/*
 * Añade la dirección de un dato al final de la lista. Esta es la función
 * recomanda para agregar elementos en la lista cuando está vacía, ya que es
 * la forma más natural de pensar en agregar datos.
 */
int32_t
linked_list_add_last(struct linked_list *self, void *dataptr)
{
    if (self && dataptr) {
        struct node *added_node = node_new(dataptr);
        if (!added_node) { return 1; }
        if (self->tail) {
            self->tail->next = added_node;
            added_node->prev = self->tail;
        }
        self->tail = added_node;
        if (self->size == 0) { self->head = added_node; }
        self->size += 1;
    }
    return 0;
}

/*
 * Obtiene un elemento de la lista sin extraerlo.
 */
void *
linked_list_get(struct linked_list *self, size_t index)
{
    if (self && index < self->size) {
        size_t count = 0;
        struct node *current_node = self->head;
        while (current_node != NULL) {
            if (count == index) { return current_node->dataptr; }
            count += 1;
            current_node = current_node->next;
        }
    }
    return NULL;
}

/*
 * Extrae un elemento de la lista, en caso de que el elemento extraido sea del
 * inicio o final se llama a las funciones apropiadas.
 */
void *
linked_list_pop(struct linked_list *self, size_t index)
{
    struct node *popped_dataptr = NULL;
    if (self && index < self->size) {
        if (index == self->size - 1) {
            popped_dataptr = linked_list_pop_last(self);
        }
        else if (index == 0) {
            popped_dataptr = linked_list_pop_first(self);
        }
        else {
            size_t count = 0;
            struct node *current_node = self->head;
            while (current_node != NULL) {
                if (count == index) {
                    if (current_node->prev) {
                        current_node->prev->next = current_node->next;
                    }
                    if (current_node->next) {
                        current_node->next->prev = current_node->prev;
                    }
                    popped_dataptr = current_node->dataptr;
                    node_free(current_node);
                    self->size -= 1;
                    break;
                }
                count += 1;
                current_node = current_node->next;
            }
        }
    }
    return popped_dataptr;
}

/*
 * Extrae el primer elemento de la lista.
 */
void *
linked_list_pop_first(struct linked_list *self)
{
    void *popped_dataptr = NULL;
    if (self && self->size) {
        struct node *old_head = self->head;
        popped_dataptr = old_head->dataptr;
        self->head = old_head->next;
        self->head->prev = NULL;
        node_free(old_head);
    }
    return popped_dataptr;
}

/*
 * Extrae el último elemento de la lista.
 */
void *
linked_list_pop_last(struct linked_list *self)
{
    void *popped_dataptr = NULL;
    if (self && self->size) {
        struct node *old_tail = self->tail;
        popped_dataptr = old_tail->dataptr;
        self->tail = old_tail->prev;
        self->tail->next = NULL;
        node_free(old_tail);
    }
    return popped_dataptr;
}

void
linked_list_free(struct linked_list *self)
{
    if (self) {
        struct node *current_node;
        while ((current_node = linked_list_pop_last(self))) {
            node_free(current_node);
        }
    }
}
