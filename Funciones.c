/******************************************************
* Fecha 28/10/2025
* Pontificia Universidad Javeriana
* Profesor: J. Corredor, PhD
* Autor: Andres Diaz
* Materia: Sistemas opertivos
* Temas: Procesos y comunicación entre procesos
******************************************************/
#include "Funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 * La primera funcion es leer archivo
 * ++++++++++++++++++++++++++++++++++
 * Lee los enteros desde un archivo y los almacena
 * Esta tiene diversos parametros como lo son:
 *  nombreArchivo: es un apuntador al nombre del archivo 
 *  arreglo: puntero al arreglo donde se almacenan los enteros recibidos
 *  N que representa la cantidad de elementos en el fichero
 */
void leerArchivo(const char *nombreArchivo, int *arreglo, int N) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (!archivo) { //En caso de que no logre abrirlo
        perror("Error al abrir archivo");
        exit(1);
    }
//Escanea los elementos hasta llegar a N
    for (int i = 0; i < N; i++) {
        fscanf(archivo, "%d", &arreglo[i]);
    }

    fclose(archivo); //Cierra la puerta de entrada
}

/*
 * La segunda funcion es sumar arreglo
 * +++++++++++++++++++++++++++++++++++
 * Suma todos los elementos de un arreglo de tamano N.
 * Esta tiene diversos parametros como lo son:
 *  arreglo que en donde estan los enteros
 *  N que representa el tamano del arreglo
 *
 *  En este caso la funcion retorna la suma de los elementos
 */
int sumarArreglo(int *arreglo, int N) {
    int suma = 0; //Inicializa la variable
    for (int i = 0; i < N; i++) {
        suma += arreglo[i]; //Va guardando el acumulado
    }
    return suma;
}

