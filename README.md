# Cola con prioridad con Heapsort.
Implementación de una cola con prioridad hecha en C, usando Heapsort para
obtener el elemento de máxima prioridad.
Este proyecto está destinado para la materia de Análisis de Algoritmos
(2023-2024) de la Facultad de Ingeniería Eléctrica en la UMNSH.

## Uso.
Para compilar el programa usar el siguiente comando:
```bash
gcc main.c menu.c pqueue.c -Wall -g -lm
```
El programa presentará un menú en el cual se tiene que presionar una tecla
especificada para cada opción (sin necesidad de presionar enter).
### Dependencias.
El programa necesita las siguientes bibliotecas no estándar disponibles en el
entorno:
- `unistd.h`.
- `termios.h`.

## Requisitos y limitaciones.
Para tener completo el programa serán necesarias las siguientes
características.
### Programa.
- Demostrar toda la funcionalidad básica de una cola con prioridad.
- Ser sencilla y entendible para cualquier usuario familiarizado con
estructuras de datos básicas y algoritmos de ordenamiento.
- No contener errores.

### Estructura de datos.
Para la estructura de datos se necesita lo siguiente:
- Insertar elementos a una cola con su prioridad dada. Con complejidad
$O(\log_{2}{n})$
- Obtener el elemento de mayor prioridad sin extraerlo. Con complejidad
$O(1)$
- Extraer el elemento con la mayor prioridad. Con complejidad $O(\log_{2}{n})$

### Estabilidad.
Dado que la cola usará un heap binario para organizar las prioridades, los
elementos devueltos si tendrán la mayor prioridad pero no necesariamente
saldrán en el orden relativo con el que entraron ya que las operaciones de
_sift up_ y _sift down_ alteran dicho orden relativo entre elementos de misma
prioridad.


## Implementación.
### Cola con prioridad.
La cola con prioridad consiste de un arreglo de elementos, dicho arreglo
crecerá bajo demanda doblando su tamaño original. Cada elemento del arreglo
contendrá un apuntador y una prioridad, el apuntador apunta a una dirección de
interés del usuario y este es de tipo void para facilitar el tratamiento de
datos de tipos arbitrarios en la cola.

En el resto del documento me referiré con 'dato' a al apuntador a un dato de
interés contenido en la cola.

#### Interfaz externa.
Son las funciones prototipadas en `pqueue.h` que se podrán usar desde el
archivo `main.c`, proveen todo lo necesario para manejar la cola.

Adicionalmente la cola también provee una función para imprimir el heap
binario en forma de árbol, esta función se usa en el código principal.

#### Implementación interna.
Implementadas y solo usadas de `pqueue.c`, aquí se definieron funciones para
tratar más fácilmente las operaciones que realiza la cola. Entre ellas se
encuentran las implementaciones de `sift_up` y `sift_down`, además de una
función especial `memswap` para realizar intercambios entre dos regiones de
memoria.

### Menú
Una estructura no necesaria para el programa pero que facilita la interacción,
incluye una estructura una función para crear nuevos menús y una para
activarlos (mostrarlos en pantalla).

### Código principal.
El código de `main.c` utiliza todo lo descrito anteriormente. En esta parte
del código se tiene una cola con prioridad que será la que se manipulará, a
dicha cola se le insertarán direcciones a variables enteras como datos, estos
datos se irán creando e insertando a la cola.

Para dar una mejor noción de la cola se imprime en pantalla la representación
interna del heap, una representación en árbol del heap y el último elemento
extraído del heap.
