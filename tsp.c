#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tsp.h"

// Funciones Privadas (auxiliares para backtracking) 
void backtracking(Grafo *g, int actual, int contador, int costoActual, int *minCosto, bool *visitado, int *rutaActual, int *mejorRuta);

// Helpers
int obtenerIndice(char c) { return c - 'A'; }
char obtenerNombre(int i) { return i + 'A'; }

void help() {
    printf("%sComandos disponibles:%s\n", AMARILLO, RESET);
    printf("%s  start <N>                      Inicia el grafo con N nodos.%s\n", AZUL, RESET);
    printf("%s  read <archivo.txt>             Lee la ruta desde archivo.%s\n", AZUL, RESET);
    printf("%s  graph                          Muestra la matriz de adyacencia.%s\n", AZUL, RESET);
    printf("%s  exit                           Libera memoria y cierra el programa.%s\n", AZUL, RESET);
}
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
    printf("%sGrafo creado con %d nodos%s\n", VERDE, n, RESET);
}

// Libera memoria para evitar fugas (Requisito de memoria)
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
        printf("%sError al abrir el archivo %s%s\n", ROJO, archivo, RESET);
        return;
    }

    printf("%sAgregando enlaces desde archivo.%s\n", AMARILLO, RESET);
    char origen, destino;
    int costo;
    while (fscanf(fp, " %c %c %d", &origen, &destino, &costo) == 3) {
        int u = obtenerIndice(origen);
        int v = obtenerIndice(destino);
        
        if (u < g->numCiudades && v < g->numCiudades) {
            g->matrizAdyacencia[u][v] = costo;
            g->matrizAdyacencia[v][u] = costo;
        }
    }
    fclose(fp);
}

// Muestra el grafo en formato de matriz de adyacencia
void imprimirGrafo(Grafo *g) {
    printf("%s\nRepresentación en Matriz de Adyacencia:\n%s", AMARILLO, RESET);
    printf("   ");
    for(int i=0; i<g->numCiudades; i++) printf("%c  ", obtenerNombre(i));
    printf("\n");
    for (int i = 0; i < g->numCiudades; i++) {
        printf(" %c ", obtenerNombre(i));
        for (int j = 0; j < g->numCiudades; j++) {
            printf("%2d ", g->matrizAdyacencia[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Logica Principal (Ciclo Hamiltoniano)
void resolverTSP(Grafo *g) {
    printf("%sVerificando que existe una ruta.%s\n", AMARILLO, RESET);

    // Asignación de memoria auxiliar para el algoritmo
    int *rutaActual = (int *)malloc(g->numCiudades * sizeof(int));
    int *mejorRuta = (int *)malloc(g->numCiudades * sizeof(int));
    // calloc inicializa a cero (falso)
    bool *visitado = (bool *)calloc(g->numCiudades, sizeof(bool)); 
    int minCosto = INF;

    // Empezamos siempre en A (índice 0)
    visitado[0] = true;
    rutaActual[0] = 0;

    // Llamada recursiva para encontrar el camino más corto
    backtracking(g, 0, 1, 0, &minCosto, visitado, rutaActual, mejorRuta);

    if (minCosto == INF) {
        printf("%sNo existe un camino que recorra todos las ciudades y regrese a la ciudad de origen.%s\n", AMARILLO, RESET);
    } else {
        printf("%sExiste un camino que recorre todos las ciudades y regresa a la ciudad de origen.%s\n", VERDE, RESET);
        printf("%sRuta a seguir: %s", VERDE, RESET);
        // Imprimir la ruta encontrada
        for (int i = 0; i < g->numCiudades; i++) {
            printf("%c", obtenerNombre(mejorRuta[i]));
        }
        printf("%c\n", obtenerNombre(mejorRuta[0])); // Cierra el ciclo volviendo al inicio
        printf("Costo total minimo: %d\n", minCosto);
    }

    free(rutaActual);
    free(mejorRuta);
    free(visitado);
}

// Algoritmo de Backtracking para buscar Ciclos Hamiltonianos
void backtracking(Grafo *g, int actual, int contador, int costoActual, int *minCosto, bool *visitado, int *rutaActual, int *mejorRuta) {
    
    // Poda: si el costo actual ya iguala o supera al mínimo encontrado, no hay necesidad de seguir por esta rama.
    if (costoActual >= *minCosto) return;

    // (contador == N)
    if (contador == g->numCiudades) {
        // (Condición de ciclo)
        if (g->matrizAdyacencia[actual][0] > 0) {
            int costoTotal = costoActual + g->matrizAdyacencia[actual][0];
            if (costoTotal < *minCosto) {
                *minCosto = costoTotal;
                // Guardar mejor ruta encontrada
                for(int i=0; i<g->numCiudades; i++) mejorRuta[i] = rutaActual[i];
            }
        }
        return;
    }

    // Recursividad: Probar vecinos no visitados
    for (int v = 0; v < g->numCiudades; v++) {
        // ha sido visitado? 
        // (costo > 0)
        if (!visitado[v] && g->matrizAdyacencia[actual][v] > 0) {
            visitado[v] = true;
            rutaActual[contador] = v;
            
            // Llamada recursiva
            backtracking(g, v, contador + 1, costoActual + g->matrizAdyacencia[actual][v], minCosto, visitado, rutaActual, mejorRuta);
            
            // Backtracking: Desmarcar el nodo para que pueda ser usado en otras ramas (permutaciones)
            visitado[v] = false;
        }
    }
}


