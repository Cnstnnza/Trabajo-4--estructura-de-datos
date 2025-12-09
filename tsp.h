#ifndef TSP_H
#define TSP_H

#include <stdbool.h>
// COLORES PARA TERMINAL
#define ROJO "\x1b[31m"
#define VERDE "\x1b[32m"
#define AMARILLO "\x1b[33m"
#define MORADO "\x1b[35m"
#define RESET "\x1b[0m"
#define AZUL "\x1b[34m"

#define MAX_LINE 100
#define INF 2147483647 // valor maximo para un entero, para poder comparar



// Estructura para manejar el grafo
typedef struct {
    int numCiudades;
    int **matrizAdyacencia; // Matriz para distancias
    bool inicializado;
} Grafo;

void help();
// funciones principales
void inicializarGrafo(Grafo *g, int n);
void liberarGrafo(Grafo *g);
void agregarRuta(Grafo *g, char *archivo);
void imprimirGrafo(Grafo *g);

// hamilton
void resolverTSP(Grafo *g);


// otras funciones
int obtenerIndice(char c);
char obtenerNombre(int i);

#endif