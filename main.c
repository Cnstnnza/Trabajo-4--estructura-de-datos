#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tsp.h"



int main() {
    char comando[MAX_LINE];
    Grafo grafo;
    grafo.inicializado = false;
    grafo.matrizAdyacencia = NULL;

    printf("%sBienvenido al sistema PVV.%s\n", MORADO, RESET);
    printf("%sSi necesita ayuda ingrese el comando help%s\n",AMARILLO, RESET);

    while (1) {
        printf("%s>pvv %s", MORADO, RESET);
        if (!fgets(comando, sizeof(comando), stdin)) break;

        comando[strcspn(comando, "\n")] = 0; // Quitar salto de linea
        char *ptr = strtok(comando, " ");
        if (ptr == NULL) continue;

        if (strcmp(ptr, "start") == 0) {
            ptr = strtok(NULL, " ");
            if (ptr) inicializarGrafo(&grafo, atoi(ptr));
            else printf("%sError: Indique numero de nodos.%s\n", ROJO, RESET);
        } 
        else if (strcmp(ptr, "read") == 0) {
            ptr = strtok(NULL, " ");
            if (ptr && grafo.inicializado) {
                agregarRuta(&grafo, ptr);
                resolverTSP(&grafo); // Verificar y calcular ruta automaticamente
            } else {
                printf("%sError: Grafo no inicializado o falta archivo.%s\n", ROJO, RESET);
            }
        } 
        else if (strcmp(ptr, "graph") == 0) {
            if (grafo.inicializado) imprimirGrafo(&grafo);
            else printf("%sError: Grafo no creado.%s\n", ROJO, RESET);
        } 
        else if (strcmp(ptr, "exit") == 0) {
            printf("%sLimpiando cache y saliendo%s\n", MORADO, RESET);
            liberarGrafo(&grafo);
            break;
        }
        else if (strcmp(ptr, "help") == 0) {
            help();
        } 
        else {
            printf("%sComando no reconocido.%s\n", ROJO, RESET);
        }
    }
    return 0;
}