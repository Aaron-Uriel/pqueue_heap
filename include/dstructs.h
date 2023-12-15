#ifndef PQUEUE_H
#define PQUEUE_H

#include <stdint.h>
#include <stddef.h>

/*
 * Representación interna de un elemento para la cola con prioridad, incluye
 * el dato recibido junto con su prioridad, el propósito de la estructura es
 * solo agrupar estos dos elementos.
 */
struct element {
    void *dataptr;
    int8_t priority;
};

/*
 * Estructura que representa una cola con prioridad, guarda a todos sus
 * elementos dentro de un arreglo para mayor rapidez. La cola puede crecer de
 * tamaño bajo demanda, lo cual afectará también al rendimiento y uso de
 * memoria.
 */
struct pqueue {
    struct element *elements;
    size_t reserved_space;
    size_t size;
};
struct pqueue *pqueue_new(size_t size);
void pqueue_free(struct pqueue *const self);
int32_t pqueue_enqueue(struct pqueue *const self, void *const dataptr,
                       int8_t priority);
int32_t pqueue_enqueue_elem(struct pqueue *const self,
                                      struct element elem);
void *pqueue_get_max(struct pqueue *const self);
void *pqueue_dequeue(struct pqueue *const self);
int32_t pqueue_set_priority(struct pqueue *const self, void *const dataptr,
                            int8_t priority);
void pqueue_print(struct pqueue *const self);
void pqueue_print_heap(struct pqueue *const self);
struct element pqueue_dequeue_elem(struct pqueue *const self);

/*
 * Lista enlazada. Estructura que representa a una lista enlazada doblemente
 * enlazada.
 */
struct linked_list {
    size_t size;
    struct node *head;
    struct node *tail;
};
struct linked_list *linked_list_new(void);
void linked_list_free(struct linked_list *self);
int32_t linked_list_add(struct linked_list *self, void *dataptr, size_t index);
int32_t linked_list_add_first(struct linked_list *self, void *dataptr);
int32_t linked_list_add_last(struct linked_list *self, void *dataptr);
void *linked_list_get(struct linked_list *self, size_t index);
void *linked_list_pop(struct linked_list *self, size_t index);
void *linked_list_pop_first(struct linked_list *self);
void *linked_list_pop_last(struct linked_list *self);

#endif
