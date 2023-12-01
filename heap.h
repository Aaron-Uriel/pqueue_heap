#ifndef HEAP_H
#define HEAP_H

/*
 * Funciones auxiliares para el manejo de heaps dentro de arreglos.
 * Implementaciones genéricas de siftup y siftdown no son útiles para la cola
 * con prioridad debido a su diseño. Solo se implementan funciones que
 * facilitan el desplazamiento dentro de un heap binario.
 */

#include <stdint.h>
#include <stddef.h>
int32_t heap_parent(size_t index);
int32_t heap_left_child(size_t index);

#endif
