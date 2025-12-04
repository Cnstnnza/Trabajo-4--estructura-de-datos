#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 100

int main() {
    char comando[MAX_LINE];

    printf("--- Modo Prueba: Solo deteccion de comandos ---\n");
    printf("Bienvenido. Escriba sus comandos.\n");

    while (1) {
        printf(">pvv "); 

        if (!fgets(comando, sizeof(comando), stdin)) break;
        comando[strcspn(comando, "\n")] = 0;
        char *ptr = strtok(comando, " ");
        if (ptr == NULL) continue;

        if (strcmp(ptr, "start") == 0) {
            ptr = strtok(NULL, " ");
            if (ptr) {
                printf("[OK] Comando START detectado. Nodos solicitados: %s\n", ptr);
            } else {
                printf("[ERROR] Comando START requiere un numero.\n");
            }
        }
        else if (strcmp(ptr, "read") == 0) {
            ptr = strtok(NULL, " ");
            if (ptr) {
                printf("[OK] Comando READ detectado. Archivo a leer: %s\n", ptr);
            } else {
                printf("[ERROR] Comando READ requiere un nombre de archivo.\n");
            }
        } 
        else if (strcmp(ptr, "graph") == 0) {
            printf("[OK] Comando GRAPH detectado.\n");
        } 
        else if (strcmp(ptr, "exit") == 0) {
            printf("[OK] Comando EXIT detectado. Saliendo...\n");
            break; // Rompe el ciclo while
        } 
        else {
            printf("[!] Comando '%s' no reconocido.\n", ptr);
        }
    }
    return 0;
}