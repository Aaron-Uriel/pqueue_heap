#ifndef MENU_H
#define MENU_H

#include <stdint.h>
#include <stdlib.h>

/*
 * Estructuras y funciones para la presentación de menús.
 * El menú consiste de: título, opciones largas, opciones cortas, y prompt.
 * Las funciones cubren los aspectos de impresión del menú y detectar que
 * opción fue dada, el manejo de 'qué hacen las opciones' es externo.
 */
struct menu {
    char *title;
    char *fill_border;
    size_t width;
    size_t optsc; /* optsc == options_count == cantidad_de_opciones */
    char *shortopts;
    char *longopts[];
};

struct menu *menu_new(char *title, char *longopts[], char *shortopts);
void menu_free(struct menu *self);
int32_t menu_activate(struct menu *self);

#endif
