#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "pqueue.h"
#include "menu.h"

char *options[] = {
    "Insertar dato.",
    "Extraer dato.",
    "Salir."
};
char *const short_options = "ixq";

int32_t
main(void)
{
    struct pqueue *main_pqueue = pqueue_new(10);
    struct element last_extracted = { 0 };
    int32_t *tmpdataptr;
    int8_t tmppriority;
    struct menu *main_menu = menu_new("Acciones.", options, short_options);
    int32_t opt;
    while (true) {
        system("clear");
        printf("Heap.\nVista de arreglo: \n");
        pqueue_print(main_pqueue);
        printf("Vista de árbol:\n");
        pqueue_print_heap(main_pqueue);
        if (last_extracted.dataptr) {
            printf("Último extraido: Valor %d\tPrioridad %hhd\n",
                   *((int32_t *)last_extracted.dataptr),
                   last_extracted.priority);
        }
        opt = menu_activate(main_menu);
        switch (opt) {
        case 'i':
            tmpdataptr = malloc(sizeof(int32_t));
            printf("Ingrese valor seguido de prioridad: ");
            if (scanf("%d %hhd", tmpdataptr, &tmppriority) == 2) {
                if (!pqueue_enqueue(main_pqueue, tmpdataptr, tmppriority)) {
                    printf("Valor %d con prioridad %hhd ingresado con éxito.\n",
                           *tmpdataptr, tmppriority);
                } else {
                    printf("Error grave, terminando programa...\n");
                    exit(1);
                }
            }
            break;
        case 'x':
            if (pqueue_get_max(main_pqueue)) {
                if (last_extracted.dataptr) { free(last_extracted.dataptr); }
                last_extracted = pqueue_dequeue_elem(main_pqueue);
            }
            break;
        case 'q':
            pqueue_free(main_pqueue);
            menu_free(main_menu);
            goto end;
        }
    }
end:
    return 0;
}
