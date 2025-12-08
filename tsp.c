#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tsp.h"

// Funciones Privadas (auxiliares para backtracking)
void backtracking(Grafo *g, int actual, int contador, int costoActual, int *minCosto, bool *visitado, int *rutaActual, int *mejorRuta);

// Helpers
int obtenerIndice(char c) { return c - 'A'; }
char obtenerNombre(int i) { return i + 'A'; }

// Inicializa la estructura
void inicializarGrafo(Grafo *g, int n) {
    if (g->inicializado) liberarGrafo(g);

    g->numCiudades = n;
    // Asignación dinámica de matriz
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

// Libera memoria para evitar fugas (Requisito de Memoria)
void liberarGrafo(Grafo *g) {
    if (!g->inicializado) return;
    for (int i = 0; i < g->numCiudades; i++) {
        free(g->matrizAdyacencia[i]);
    }
    free(g->matrizAdyacencia);
    g->matrizAdyacencia = NULL;
    g->inicializado = false;
}

// Lectura del archivo ruta.txt
void agregarRuta(Grafo *g, char *archivo) {
    FILE *fp = fopen(archivo, "r");
    if (!fp) {
        printf("Error al abrir el archivo %s\n", archivo);
        return;
    }

    printf("Agregando enlaces desde archivo.\n");
    char origen, destino;
    int costo;
    // Lee formato: A B 15
    while (fscanf(fp, " %c %c %d", &origen, &destino, &costo) == 3) {
        int u = obtenerIndice(origen);
        int v = obtenerIndice(destino);
        
        if (u < g->numCiudades && v < g->numCiudades) {
            [cite_start]// Grafo no dirigido: A->B es igual a B->A 
            g->matrizAdyacencia[u][v] = costo;
            g->matrizAdyacencia[v][u] = costo;
        }
    }
    fclose(fp);
}

// Muestra el grafo en formato de matriz de adyacencia
void imprimirGrafo(Grafo *g) {
    printf("   ");
    for(int i=0; i<g->numCiudades; i++) printf("%c  ", obtenerNombre(i));
    printf("\n");
    for (int i = 0; i < g->numCiudades; i++) {
        printf("%c ", obtenerNombre(i));
        for (int j = 0; j < g->numCiudades; j++) {
            printf("%2d ", g->matrizAdyacencia[i][j]);
        }
        printf("\n");
    }
}

// Logica Principal (Ciclo Hamiltoniano) 
void resolverTSP(Grafo *g) {
    printf("Verificando que existe una ruta.\n");
    
    // PENDIENTE DE IMPLEMENTACIÓN
    // De momento, solo imprime que está verificando
    printf("La verificacion y calculo de ruta esta pendiente.\n");
}

void backtracking(Grafo *g, int actual, int contador, int costoActual, int *minCosto, bool *visitado, int *rutaActual, int *mejorRuta) {
    // Implementar el algoritmo.
}