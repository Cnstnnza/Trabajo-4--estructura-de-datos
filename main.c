#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tsp.h"

int main() {
    char comando[MAX_LINE];
    Grafo grafo;
    grafo.inicializado = false;
    grafo.matrizAdyacencia = NULL;

    printf("Bienvenido al sistema PVV. Ingrese comandos.\n");

    while (1) {
        printf(">pvv ");
        if (!fgets(comando, sizeof(comando), stdin)) break;

        comando[strcspn(comando, "\n")] = 0; // Quitar salto de linea
        char *ptr = strtok(comando, " ");
        if (ptr == NULL) continue;

        if (strcmp(ptr, "start") == 0) {
            ptr = strtok(NULL, " ");
            if (ptr) inicializarGrafo(&grafo, atoi(ptr));
            else printf("Error: Indique numero de nodos.\n");
        } 
        else if (strcmp(ptr, "read") == 0) {
            ptr = strtok(NULL, " ");
            if (ptr && grafo.inicializado) {
                agregarRuta(&grafo, ptr);
                resolverTSP(&grafo); // Verificar y calcular ruta automaticamente
            } else {
                printf("Error: Grafo no inicializado o falta archivo.\n");
            }
        } 
        else if (strcmp(ptr, "graph") == 0) {
            if (grafo.inicializado) imprimirGrafo(&grafo);
            else printf("Error: Grafo no creado.\n");
        } 
        else if (strcmp(ptr, "exit") == 0) {
            printf("Limpiando cache y saliendo\n");
            liberarGrafo(&grafo);
            break;
        } 
        else {
            printf("Comando no reconocido.\n");
        }
    }
    return 0;
}