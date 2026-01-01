/**
 * @file tsp.c
 * @brief Implementacion de las funciones de manejo de grafos y algoritmo TSP.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tsp.h"

// --- Prototipos Privados ---
/**
 * @brief Funcion recursiva auxiliar para realizar la busqueda en profundidad (Backtracking).
 * @param g Puntero al grafo.
 * @param actual Indice del nodo actual.
 * @param contador Numero de nodos visitados en la rama actual.
 * @param costoActual Costo acumulado hasta el momento.
 * @param minCosto Puntero al costo minimo global encontrado (para poda).
 * @param visitado Array de booleanos para marcar nodos visitados.
 * @param rutaActual Array que almacena el camino actual.
 * @param mejorRuta Array que almacena el mejor camino encontrado hasta ahora.
 */
void backtracking(Grafo *g, int actual, int contador, int costoActual, int *minCosto, bool *visitado, int *rutaActual, int *mejorRuta);

// --- Helpers ---
int obtenerIndice(char c) { return c - 'A'; }
char obtenerNombre(int i) { return i + 'A'; }

void help() {
    printf("%sComandos disponibles:%s\n", AMARILLO, RESET);
    printf("%s  start <N>             Inicia el grafo con N nodos.%s\n", AZUL, RESET);
    printf("%s  read <archivo.txt>    Lee la ruta desde archivo.%s\n", AZUL, RESET);
    printf("%s  graph                 Muestra la matriz de adyacencia.%s\n", AZUL, RESET);
    printf("%s  exit                  Libera memoria y cierra el programa.%s\n", AZUL, RESET);
}

void inicializarGrafo(Grafo *g, int n) {
    if (g->inicializado) liberarGrafo(g);

    g->numCiudades = n;
    // Asignacion dinamica de matriz (filas)
    g->matrizAdyacencia = (int **)malloc(n * sizeof(int *));
    if (g->matrizAdyacencia == NULL) {
        printf("%sError fatal: No hay memoria suficiente.%s\n", ROJO, RESET);
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        // Asignacion dinamica de columnas
        g->matrizAdyacencia[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            g->matrizAdyacencia[i][j] = 0; // 0 = sin conexion
        }
    }
    g->inicializado = true;
    printf("%sGrafo creado con %d nodos%s\n", VERDE, n, RESET);
}

void liberarGrafo(Grafo *g) {
    if (!g->inicializado) return;
    for (int i = 0; i < g->numCiudades; i++) {
        free(g->matrizAdyacencia[i]);
    }
    free(g->matrizAdyacencia);
    g->matrizAdyacencia = NULL;
    g->inicializado = false;
}

void agregarRuta(Grafo *g, char *archivo) {
    FILE *fp = fopen(archivo, "r");
    if (!fp) {
        printf("%sError al abrir el archivo %s%s\n", ROJO, archivo, RESET);
        return;
    }

    printf("%sAgregando enlaces desde archivo.%s\n", AMARILLO, RESET);
    char origen, destino;
    int costo;
    // " %c" ignora espacios en blanco antes de leer el caracter
    while (fscanf(fp, " %c %c %d", &origen, &destino, &costo) == 3) {
        int u = obtenerIndice(origen);
        int v = obtenerIndice(destino);
        
        // Validacion de limites para evitar Segmentation Fault
        if (u >= 0 && u < g->numCiudades && v >= 0 && v < g->numCiudades) {
            g->matrizAdyacencia[u][v] = costo;
            g->matrizAdyacencia[v][u] = costo; // Grafo no dirigido
        } else {
            printf("%sAdvertencia: Nodo %c o %c fuera de rango.%s\n", ROJO, origen, destino, RESET);
        }
    }
    fclose(fp);
}

void imprimirGrafo(Grafo *g) {
    printf("%s\nRepresentacion en Matriz de Adyacencia:\n%s", AMARILLO, RESET);
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

void resolverTSP(Grafo *g) {
    printf("%sVerificando que existe una ruta...%s\n", AMARILLO, RESET);

    // Asignacion de memoria auxiliar
    int *rutaActual = (int *)malloc(g->numCiudades * sizeof(int));
    int *mejorRuta = (int *)malloc(g->numCiudades * sizeof(int));
    bool *visitado = (bool *)calloc(g->numCiudades, sizeof(bool)); 
    int minCosto = INF;

    // Inicializacion: Empezamos en nodo 0 (A)
    visitado[0] = true;
    rutaActual[0] = 0;

    // Llamada al algoritmo
    backtracking(g, 0, 1, 0, &minCosto, visitado, rutaActual, mejorRuta);

    // Resultados
    if (minCosto == INF) {
        printf("%sNo existe un camino hamiltoniano valido.%s\n", AMARILLO, RESET);
    } else {
        printf("%sCamino encontrado con exito.%s\n", VERDE, RESET);
        printf("%sRuta optima: %s", VERDE, RESET);
        for (int i = 0; i < g->numCiudades; i++) {
            printf("%c -> ", obtenerNombre(mejorRuta[i]));
        }
        printf("%c\n", obtenerNombre(mejorRuta[0])); // Retorno al inicio
        printf("Costo total minimo: %d\n", minCosto);
    }

    // Limpieza de memoria auxiliar
    free(rutaActual);
    free(mejorRuta);
    free(visitado);
}

void backtracking(Grafo *g, int actual, int contador, int costoActual, int *minCosto, bool *visitado, int *rutaActual, int *mejorRuta) {
    
    // PODA: Si el costo actual ya supera el mejor encontrado, cortamos esta rama
    if (costoActual >= *minCosto) return;

    // CASO BASE: Hemos visitado todos los nodos
    if (contador == g->numCiudades) {
        // Verificar si existe camino de vuelta al origen (nodo 0)
        if (g->matrizAdyacencia[actual][0] > 0) {
            int costoTotal = costoActual + g->matrizAdyacencia[actual][0];
            if (costoTotal < *minCosto) {
                *minCosto = costoTotal;
                // Copiar la ruta actual a la mejor ruta
                for(int i=0; i<g->numCiudades; i++) mejorRuta[i] = rutaActual[i];
            }
        }
        return;
    }

    // RECURSION: Probar vecinos
    for (int v = 0; v < g->numCiudades; v++) {
        // Si no ha sido visitado Y existe conexion directa
        if (!visitado[v] && g->matrizAdyacencia[actual][v] > 0) {
            visitado[v] = true;
            rutaActual[contador] = v;
            
            backtracking(g, v, contador + 1, costoActual + g->matrizAdyacencia[actual][v], minCosto, visitado, rutaActual, mejorRuta);
            
            // Backtracking (desmarcar para probar otras ramas)
            visitado[v] = false;
        }
    }
}