#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include <dstructs.h>
/*
 * Funciones para obtener índices de distintos elementos del heap relativos al
 * índice de un nodo.
 */
static inline size_t heap_parent(size_t index) {
    return (index) ? (index - 1) / 2 : 0;
}
static inline size_t heap_lchild(size_t index) { return 2 * index + 1; }
static inline size_t heap_rchild(size_t index) { return 2 * index + 2; }

/*
 * Realiza un intercambio entre dos regiones de memoria.
 * En caso de que algún argumento sea nulo se regresa o alguna asignación de
 * memoria falle se regresa un valor distinto de 0.
 */
int32_t
memswap(void *a, void *b, size_t size)
{
    if (a && b && size) {
        void *tmp = malloc(size);
        if (tmp) {
            memmove(tmp, a, size);
            memmove(a, b, size);
            memmove(b, tmp, size);
        } else {
            return 1;
        }
        free(tmp);
    } else {
        return 1;
    }
    return 0;
}

/*
 * Devuelve la cantidad de dígitos de un número.
 */
uint8_t
digits(int32_t num)
{
    if (num == 0) { return 1; }
    if (num < 0) { num = -num; }
    return log10(num) + 1;
}

/*
 * Realiza el 'tamizado' de un nodo hacia arriba, asumiendo que el
 * elemento recibido rompe la propiedad de orden de heap del árbol.
 * Se regresa un valor distinto a 0 en caso de haber recibido un valor nulo o
 * haber recibido un nodo sin padre.
 */
int32_t
pqueue_sift_up(struct pqueue *self, size_t index)
{
    if (self && index < self->size) {
        struct element *elem, *parent;
        do {
            elem = &self->elements[index];
            parent = &self->elements[heap_parent(index)];
            if (parent->priority < elem->priority) {
                memswap(parent, elem, sizeof(*elem));
                index = heap_parent(index);
            } else {
                break;
            }
        } while (index > 0);
    } else {
        return 1;
    }
    return 0;
}

/*
 * Realiza una 'tamizado' hacia abajo, asumiendo que el elemento rompe la
 * propiedad de heap del árbol y debe de ir abajo.
 */
int32_t
pqueue_sift_down(struct pqueue *self, size_t index)
{
    if (self && index < self->size) {
        struct element *elem, *lchild, *rchild, *max;
        bool has_rchild;
        bool has_lchild;
        size_t max_index = index;
        while (true) {
            has_lchild = heap_lchild(index) < self->size;
            has_rchild = heap_rchild(index) < self->size;
            elem = &self->elements[index];
            lchild = (has_lchild)? &self->elements[heap_lchild(index)]: NULL;
            rchild = (has_rchild)? &self->elements[heap_rchild(index)]: NULL;
            max = elem;
            if (lchild && (!rchild || lchild->priority > rchild->priority)) {
                max = lchild;
                max_index = heap_lchild(index);
            }
            else if (lchild && rchild &&
                     lchild->priority <= rchild->priority) {
                max = rchild;
                max_index = heap_rchild(index);
            }
            if (max->priority > elem->priority) {
                if (memswap(max, elem, sizeof(*elem))) {
                    return 1;
                }
                index = max_index;
            } else {
                break;
            }
        }
    } else {
        return 1;
    }
    return 0;
}


/*
 * Crea una nueva cola con prioridad y regresa su dirección.
 * Se puede reservar una cantidad tope de elementos inicial pasando un como
 * argumento un valor. Un tamaño inicial de 0, resulta en una cola de 1
 * elemento.
 */
struct pqueue *
pqueue_new(size_t reserved_space)
{
    struct pqueue *new_pqueue = malloc(sizeof(*new_pqueue));
    if (new_pqueue) {
        new_pqueue->reserved_space = (reserved_space)? reserved_space: 1;
        new_pqueue->elements = malloc(sizeof(struct element) * reserved_space);
        new_pqueue->size = 0;
    }
    return new_pqueue;
}

/*
 * Libera la memoria relacionada con la cola con prioridad.
 */
void
pqueue_free(struct pqueue *const self)
{
    if (self) {
        free(self->elements);
        free(self);
    }
}

/*
 * Agrega un nuevo dato a la cola con prioridad.
 * Esta función preserva las propiedades de orden del heap aplicando un
 * sift up.
 */
int32_t
pqueue_enqueue(struct pqueue *const self, void *const dataptr,
               int8_t priority)
{
    if (self && dataptr) {
        size_t new_size = self->size + 1;
        if (new_size >= self->reserved_space) {
            size_t new_reserved_space = self->reserved_space * 2;
            self->elements = realloc(
                self->elements, new_reserved_space * sizeof(struct element));
            /*
             * Este es un error crítico que debe de manejarse mejor.
             */
            if (!self->elements) {
                return 1;
            }
        }
        self->elements[new_size - 1] = (struct element) {
            .dataptr = dataptr,
            .priority = priority
        };
        self->size = new_size;
        pqueue_sift_up(self, new_size - 1);
    }
    return 0;
}

/*
 * Agrega un nuevo dato a la cola. El dato se recibe dentro de una estructura
 * elemento que incluye un apuntador al dato y su prioridad deseada.
 */
int32_t
pqueue_enqueue_elem(struct pqueue *const self, struct element elem)
{
    if (self && elem.dataptr) {
        size_t new_size = self->size + 1;
        if (new_size >= self->reserved_space) {
            size_t new_reserved_space = self->reserved_space * 2;
            self->elements = realloc(
                self->elements, new_reserved_space * sizeof(struct element));
            /*
             * Este es un error crítico que debe de manejarse mejor.
             */
            if (self->elements) {
                return 1;
            }
        }
        self->elements[new_size - 1] = elem;
        self->size = new_size;
        pqueue_sift_up(self, new_size - 1);
    }
    return 0;
}

/*
 * Regresa un dato sin extraerlo de la cola, dicho dato cumple con tener la
 * mayor prioridad en la cola. Se garantiza que el elemento regresado haya sido
 * uno con la mayor prioridad, pero no el órden relativo entre elementos de la
 * misma prioridad.
 */
void *
pqueue_get_max(struct pqueue *const self)
{
    void *dataptr = NULL;
    if (self && self->size) {
        dataptr = self->elements[0].dataptr;
    }
    return dataptr;
}

/*
 * Extrae un dato con la mayor prioridad en la cola. Se garantiza que el
 * elemento regresado haya sido uno con la mayor prioridad, pero no el órden
 * relativo entre elementos de la misma prioridad.
 */
void *
pqueue_dequeue(struct pqueue *const self)
{
    void *extracted_dataptr = NULL;
    if (self && self->size) {
        extracted_dataptr = self->elements[0].dataptr;
        memmove(&self->elements[0], &self->elements[self->size - 1],
                sizeof(*self->elements));
        self->size -= 1;
        pqueue_sift_down(self, 0);
    }
    return extracted_dataptr;
}

/*
 * Extrae un elemento que contenga la mayor prioridad, incluyendo la prioridad
 * con la que fue recibida en la cola.
 */
struct element
pqueue_dequeue_elem(struct pqueue *const self)
{
    struct element extracted_element = { 0 };
    if (self && self->size) {
        extracted_element = self->elements[0];
        memmove(&self->elements[0], &self->elements[self->size - 1],
                sizeof(*self->elements));
        self->size -= 1;
        pqueue_sift_down(self, 0);
    }
    return extracted_element;
}

/*
 * Altera una cadena recibida y guarda en ella una representación del heap de
 * prioridades de la cola en forma de cadena de caracteres.
 * En caso de que la representación de cadena no quepa en buf, se libera y crea
 * un nuevo buffer del tamaño adecuado.
 */
/*
 * Esta función no la uso porque intenté hacer algo 'interesante' pero
 * realmente es complicado hacer que funcione bien.
 */
char *
pqueue_strrepr(struct pqueue *const self, char **buf, size_t *bufsize)
{
    if (self && self->size && buf && *buf && bufsize && *bufsize) {
        /* 
         * Esto puede fallar si máximo es 17 y otro elemento es de prioridad
         * -100.
         */
        uint8_t number_slots = digits(self->elements[0].priority) + 2;
        size_t reprsize = sizeof(char)*self->size*number_slots + 1;
        if (*bufsize < reprsize) {
            free(*buf);
            *buf = malloc(reprsize);
            *bufsize = reprsize;
        }
        if (*buf) {
            size_t i;
            for (i = 0; i < self->size - 1; i += 1) {
                sprintf(*buf + i * number_slots, "%*hhd ",
                        -number_slots, self->elements[i].priority);
            }
            sprintf(*buf + i * number_slots, "%*hhd\n", -number_slots,
                    self->elements[self->size - 1].priority);
        }
    }
    return *buf;
}

/*
 * Imprime las prioridades dentro del heap de la cola.
 */
void
pqueue_print(struct pqueue *const self)
{
    if (self && self->size) {
        size_t i;
        for (i = 0; i < self->size - 1; i += 1) {
            printf("%hhd ", self->elements[i].priority);
        }
        printf("%hhd\n", self->elements[i].priority);
    }
}

void
indent(uint8_t level, uint32_t active_levels)
{
    bool level_is_active;
    for (uint8_t currlevel = 0; currlevel < level - 1; currlevel += 1) {
        level_is_active = active_levels & (1 << currlevel);
        printf((level_is_active)? "│   ": "    ");
    }
}

/* 
 * Imprime cada hijo de un nodo raíz dado, la impresión es realizada
 * recursivamente.
 * Los niveles activos de cada árbol son guardados en una variable estática
 * al interior de la función.
 */
void
recursive_print(struct pqueue *self, size_t index, bool closesLevel)
{
    if (self && self->size) {
        static uint32_t active_levels = 0; /* Solo con manipulaciones de bit a bit */
        uint8_t current_level = log2(index + 1);
        if (closesLevel) {
            /* Operador implicación negada o "a and ~b". */
            active_levels = active_levels & ~(1 << (current_level - 1));
        } else {
            active_levels = active_levels | (1 << (current_level - 1));
        }

        indent(current_level, active_levels);
        printf("%s %d\n", (closesLevel) ? "└──" : "├──",
               self->elements[index].priority);
        bool has_rchild = heap_rchild(index) < self->size;
        bool has_lchild = heap_lchild(index) < self->size;
        if (has_rchild) {
            recursive_print(self, heap_rchild(index), false);
            recursive_print(self, heap_lchild(index), true);
        }
        else if (has_lchild) {
            recursive_print(self, heap_lchild(index), true);
        }
    }
}

void
pqueue_print_heap(struct pqueue *const self)
{
    if (self && self->size) {
        printf("%d\n", self->elements[0].priority);
        bool has_rchild = heap_rchild(0) < self->size;
        bool has_lchild = heap_lchild(0) < self->size;
        if (has_rchild) {
            recursive_print(self, heap_rchild(0), false);
            recursive_print(self, heap_lchild(0), true);
        }
        else if (has_lchild) {
            recursive_print(self, heap_lchild(0), true);
        }
    }
}

