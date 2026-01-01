/**
 * @file tsp.h
 * @brief Interfaz principal para el manejo de Grafos y resolucion del TSP (Traveling Salesman Problem).
 * @author Grupo 8
 * @date 2025
 *
 * Contiene las definiciones de estructuras, macros de colores y prototipos de funciones
 * para la manipulacion de grafos y algoritmos de busqueda.
 */

#ifndef TSP_H
#define TSP_H

#include <stdbool.h>

// --- MACROS DE COLORES PARA LA TERMINAL ---
#define ROJO     "\x1b[31m"
#define VERDE    "\x1b[32m"
#define AMARILLO "\x1b[33m"
#define MORADO   "\x1b[35m"
#define RESET    "\x1b[0m"
#define AZUL     "\x1b[34m"

#define MAX_LINE 100
/** @brief Valor centinela para representar infinito en comparaciones de costos. */
#define INF 2147483647 

/**
 * @struct Grafo
 * @brief Estructura que representa un grafo ponderado mediante matriz de adyacencia.
 */
typedef struct {
    int numCiudades;        /**< Numero total de nodos (ciudades) en el grafo. */
    int **matrizAdyacencia; /**< Matriz dinamica NxN donde [i][j] es el costo de ir de i a j. */
    bool inicializado;      /**< Bandera para verificar si la memoria ha sido reservada. */
} Grafo;

/**
 * @brief Muestra los comandos disponibles en la consola.
 */
void help();

/**
 * @brief Inicializa el grafo reservando memoria dinamica para la matriz de adyacencia.
 * @param g Puntero a la estructura Grafo.
 * @param n Numero de ciudades (nodos).
 */
void inicializarGrafo(Grafo *g, int n);

/**
 * @brief Libera la memoria dinamica asociada al grafo.
 * @param g Puntero a la estructura Grafo.
 */
void liberarGrafo(Grafo *g);

/**
 * @brief Lee un archivo de texto y carga las aristas (rutas) en el grafo.
 * @param g Puntero a la estructura Grafo.
 * @param archivo Nombre del archivo a leer (ej: ruta.txt).
 */
void agregarRuta(Grafo *g, char *archivo);

/**
 * @brief Imprime la matriz de adyacencia en la consola.
 * @param g Puntero a la estructura Grafo.
 */
void imprimirGrafo(Grafo *g);

/**
 * @brief Algoritmo principal: Encuentra el ciclo hamiltoniano de costo minimo.
 * Utiliza backtracking con poda.
 * @param g Puntero a la estructura Grafo.
 */
void resolverTSP(Grafo *g);

// --- Funciones de utilidad ---

/**
 * @brief Convierte un caracter (ej: 'A') a su indice numerico (0).
 * @param c Caracter de la ciudad.
 * @return int Indice correspondiente (0, 1, 2...).
 */
int obtenerIndice(char c);

/**
 * @brief Convierte un indice numerico a su nombre de ciudad (ej: 0 -> 'A').
 * @param i Indice de la ciudad.
 * @return char Caracter correspondiente.
 */
char obtenerNombre(int i);

#endif