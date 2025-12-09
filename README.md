# Trabajo-4--estructura-de-datos
Repositorio para el trabajo 4 de estructura de datos grupo 8

Este programa resuelve el Problema del Vendedor Viajante (TSP) utilizando un enfoque de fuerza bruta (backtracking) para encontrar un Ciclo Hamiltoniano de costo minimo.El sistema carga un grafo desde un archivo de texto, verifica la existencia de una rutavalida y calcula el costo total.

## ARCHIVOS DEL PROYECTO 
1. main.c      : interfaz de consola y manejo de comandos usuario.  
2. tsp.c       : logica del algoritmo, manejo de memoria y estructuras.  
3. tsp.h       : cabeceras y definiciones de funciones.  
4. Makefile    : script para compilacion automatizada.  
5. ruta.txt    : archivo de ejemplo con las conexiones del grafo.  

## INSTRUCCIONES DE COMPILACION 

OPCION 1: Usando Make (Recomendado para Linux/WSL/MacOS)  
1. abrir una terminal en la carpeta del proyecto.  
2. ejecutar el comando:  
   make  
3. esto generara el ejecutable llamado 'pvv_app'.  

OPCION 2: Compilacion manual con GCC (Windows/Linux sin Make)  
Si no se tiene 'make' instalado, se puede compilar manualmente escribiendo:  
   gcc -o pvv_app main.c tsp.c
   
Nota: asegurarse de incluir ambos archivos .c en el comando.  

## INSTRUCCIONES DE EJECUCION
En Linux/Mac:  
   ./pvv_app  

En Windows (CMD o PowerShell):  
   pvv_app.exe  

## COMANDOS

Una vez dentro del programa, se vera el prompt ">pvv". Los comandos disponibles son:  

1. Iniciar el grafo:  
   >pvv start <N>  
   (donde N es la cantidad de ciudades/nodos, ej: 5)  

2. Leer ruta y resolver:  
   >pvv read <archivo.txt>  
   (carga los enlaces y busca la solucion automaticamente)  
   ejemplo: >pvv read ruta2.txt  

3. Ver la matriz de adyacencia:  
   >pvv graph  
   (muestra como quedo cargado el grafo en memoria)  

4. Salir:  
   >pvv exit  
   (libera la memoria y cierra el programa)  

## FORMATO DEL ARCHIVO DE RUTA
El archivo de texto debe contener las conexiones en el siguiente formato:  
Origen Destino Costo  
A B 15  
B C 25  
...

## LIMPIEZA
Para borrar los archivos ejecutables generados, ejecutar:  
   make clean  
(o borra manualmente pvv_app.exe)  