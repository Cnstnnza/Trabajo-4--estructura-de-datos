#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tsp.h"

// Funciones privadas (auxiliares para backtracking) ---
void backtracking(Grafo *g, int actual, int contador, int costoActual, int *minCosto, bool *visitado, int *rutaActual, int *mejorRuta);

// Inicializa la estructura
void inicializarGrafo(Grafo *g, int n) {
    if (g->inicializado) liberarGrafo(g);

    g->numCiudades = n;
    // Asignación dinamica de matriz
    g->matrizAdyacencia = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        g->matrizAdyacencia[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            g->matrizAdyacencia[i][j] = 0; // 0 = sin conexión
        }
    }
    g->inicializado = true;
    printf("Grafo creado con %d nodos\n", n);
}