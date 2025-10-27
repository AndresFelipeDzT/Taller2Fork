/******************************************************
* Fecha 28/10/2025
* Pontificia Universidad Javeriana
* Profesor: J. Corredor, PhD
* Autor: Andres Diaz
* Materia: Sistemas opertivos
* Temas: Procesos y comunicación entre procesos
******************************************************/
#ifndef __FUNCIONES_H__
#define __FUNCIONES_H__
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Prototipos de las funciones


void leerArchivo(const char *nombreArchivo, int *arreglo, int N);

int sumarArreglo(int *arreglo, int N);

#endif
