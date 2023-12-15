# Estructuras de datos.
Estructuras de datos hechas en C para la materia de análisis de algoritmos.
Este proyecto está destinado para la materia de Análisis de Algoritmos
(2023-2024) de la Facultad de Ingeniería Eléctrica en la UMNSH.

## Compilación.
Este proyecto para compilar requiere de lo siguiente:
- [Meson](https://mesonbuild.com/) versión `1.2.0` o mayor para ser
construido.
- Un compilador de C disponible en el `PATH`.
- Tener disponible `math.h`.
- Tener `unistd.h` para poder compilar la demo.
- Tener `termios.h` para poder compilar la demo.

El programa consiste de una biblioteca que puede ser usada por otros proyectos
hechos en C. Está pensada específicamente para ser usada como subproyecto de
proyectos en Meson.
Para configurar el proyecto y permitir que compile las pruebas y demos
ejecute:
```bash
meson setup -Denable-tests=true build
```
Esto creó un directorio `build` que tendrá todo el entorno necesario para
compilar el proyecto. Para el proyecto ejecute:
```bash
meson compile -C build
```

## Estructuras de datos implementadas.
Este repositorio incluye por ahora implementaciones cola de prioridad y listas
no ordenadas de datos. Se irán incluyendo más conforme pase el tiempo.

### Cola con prioridad.
La cola se implementa usando Heapsort para obtener el elemento de
máxima/mínima prioridad, se decide el criterio de prioridad al momento de
construir la cola.
La cola con prioridad cumple con lo siguiente lo siguiente:
- Insertar elementos a una cola con su prioridad dada. Con complejidad
$O(\log_{2}{n})$.
- Obtener el elemento de mayor prioridad sin extraerlo. Con complejidad
$O(1)$.
- Extraer el elemento con la mayor prioridad. Con complejidad
$O(\log_{2}{n})$.

#### Estabilidad.
Dado que la cola usará un heap binario para organizar las prioridades, los
elementos devueltos si tendrán la mayor prioridad pero no necesariamente
saldrán en el orden relativo con el que entraron ya que las operaciones de
_sift up_ y _sift down_ alteran dicho orden relativo entre elementos de misma
prioridad.

#### Implementación.
La cola con prioridad consiste de un arreglo de elementos, dicho arreglo
crecerá bajo demanda doblando su tamaño original. Cada elemento del arreglo
contendrá un apuntador y una prioridad, el apuntador apunta a una dirección de
interés del usuario y este es de tipo void para facilitar el tratamiento de
datos de tipos arbitrarios en la cola.

Adicionalmente la cola también provee una función para imprimir el heap
binario en forma de árbol, esta función se usa en la demo.

#### Demo.
Se creó una demostración del funcionamiento de la cola con prioridad, si ya se
compiló el proyecto con las pruebas activadas, se puede ejecutar la demo con
el siguiente comando (asumiendo que se está en la raíz del proyecto):
```bash
./build/tests/demo/pqueue_demo
```
El programa presentará un menú en el cual se tiene que presionar una tecla
especificada para cada opción (sin necesidad de presionar enter).

Para dar una mejor noción de la cola se imprime en pantalla la representación
interna del heap, una representación en árbol del heap y el último elemento
extraído del heap.

### Lista enlazada.
Una lista de datos que no tiene orden específico, hecha para representar
arreglos dinámicos, esta implementación usará nodos para ello. Las operaciones
permitidas son:
- Insertar. Inserta un dato en una posición arbitraria dentro de la
estructura. Complejidad $O(n)$ para el peor caso.
- Extraer. Extrae un dato de una posición arbitraria de los datos almacenados.
Complejidad $O(n)$ para el peor caso.
- Obtención de datos. Obtenemos un dato sin extraerlo desde la lista.
Complejidad $O(n)$ para el peor caso.
- Realizar pop. Operación más sencilla que una extracción, solo válida para
el inicio y el final. Complejidad $O(1)$.
- Añadir al inicio/final. Operación más sencilla que una inserción normal.
Complejidad $O(1)$.

#### Implementación.
La lista usará nodos para almacenar los datos ingresados a la lista, estos
datos serán también del tipo `void *`. Los nodos serán simplemente enlazados, 


## Interfaz externa.
Son las funciones prototipadas en `dstructs.h`, proveen todo lo necesario para
manejar las estructuras de datos desde otros proyectos.

### Implementación interna.
Hay funciones implementadas dentro de la biblioteca que solo se usan dentro de
ella, tratan de simplificar realizadas por las estructuras. Entre ellas se
encuentran las implementaciones de `sift_up` y `sift_down`, además de una
función especial `memswap` para realizar intercambios entre dos regiones de
memoria.

## Menú
Una estructura no necesaria para el programa pero que facilita la interacción,
incluye una estructura una función para crear nuevos menús y una para
activarlos (mostrarlos en pantalla).
