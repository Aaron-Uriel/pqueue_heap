#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include "menu.h"

#define MENU_WIDTH_CONSTANT 6

/*
 * Función que lee presiones de teclas individuales de teclado desde stdin sin
 * efecto de eco en pantalla.
 * La función requiere de las bibliotecas termios.h, unistd.h y stdio.h.
 */
int
getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

/*
 * Crea una cadena formada por repeticiones de la cadena recibida.
 * Una repetición significa tener la cadena original.
 */
char *
strrep(const char *const str, uint32_t reps)
{
    char *repstr = NULL;
    if (str && reps > 0) {
        const size_t strsize = strlen(str) + 1;
        const size_t repsize = (strsize - 1) * reps + 1;
        repstr = malloc(repsize);
        if (repstr) {
            size_t i;
            for (i = 0; i < repsize; i += strsize - 1) {
                memcpy(repstr + i, str, strsize);
            }
            repstr[repsize - 1] = '\0';
        }
    }
    return repstr;
}

/*
 * Crea una nueva instancia de menu.
 * Esta función no copia cadenas, por lo que las cadenas que se pasan como
 * argumentos se espera que estén disponibles durante todo el tiempo de vida
 * del menú.
 */
struct menu *
menu_new(char *title, char *longopts[], char *shortopts)
{
    struct menu *new_menu = NULL;
    if (title && shortopts && longopts && *longopts) {
        size_t optsc = 0, maxlen = strlen(title), current_len;
        while(longopts[optsc]) {
            current_len = strlen(longopts[optsc]);
            if (maxlen < current_len) { maxlen = current_len; }
            optsc += 1;
        }
        new_menu =
            malloc(sizeof(struct menu) + sizeof(char *) * optsc);
        if (new_menu) {
            new_menu->title = title;
            new_menu->width = maxlen + 5;
            new_menu->fill_border = strrep("─", new_menu->width);
            new_menu->optsc = optsc;
            new_menu->shortopts = shortopts;
            for(uint8_t i = 0; i < new_menu->optsc; i += 1) {
                new_menu->longopts[i] = longopts[i];
            }
        }
    }
    return new_menu;
}

/*
 * Muestra el menú en pantalla y espera la lectura en teclado de una opción
 * válida.
 * Esta función devuelve la opción válida leida para ser manejada
 * externamente.
 */
int32_t
menu_activate(struct menu *self)
{
    printf("┌─%s─┐\n", self->fill_border);
    printf("│ %*s │\n", -self->width, self->title);
    printf("├─%s─┤\n", self->fill_border);
    size_t i = 0;
    while (self->shortopts[i] && self->longopts[i]) {
        printf("│  [%c] %*s │\n", self->shortopts[i], (-self->width + 5),
               self->longopts[i]);
        i += 1;
    }
    printf("└─%s─┘\n", self->fill_border);

    int32_t ch;
    while (!strchr(self->shortopts, ch = getch()));
    return ch;
}

void
menu_free(struct menu *self)
{
    free(self->fill_border);
    free(self);
}
