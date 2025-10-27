/******************************************************
* Fecha 28/10/2025
* Pontificia Universidad Javeriana
* Profesor: J. Corredor, PhD
* Autor: Andres Diaz
* Materia: Sistemas opertivos
* Temas: Procesos y comunicacion entre procesos
******************************************************/
//Las librerias que se van a usar
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "Funciones.h"

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Uso: ./a.out N1 archivo00 N2 archivo01\n");
        exit(1);
    }

    int N1 = atoi(argv[1]);
    char *archivoA = argv[2];
    int N2 = atoi(argv[3]);
    char *archivoB = argv[4];

    // Arreglos para almacenar los datos de los archivos
    int *A = (int *) malloc(sizeof(int)*N1);
    int *B = (int *) malloc(sizeof(int)*N2);
    int pipefd[2]; // pipefd[0] = lectura, pipefd[1] = escritura

    pipe(pipefd);

    // Leer datos desde archivos
    leerArchivo(archivoA, A, N1);
    leerArchivo(archivoB, B, N2);

    pid_t pid1 = fork();

    if (pid1 == 0) {
        // Primer hijo
        int sumaA;
        pid_t pidNieto = fork();

        if (pidNieto == 0) {
            // Nieto: suma arreglo A y devuelve resultado al primer hijo
            int suma = sumarArreglo(A, N1);
            exit(suma);
        } else {
            // Primer hijo espera al nieto y lee su resultado
            waitpid(pidNieto, &sumaA, 0);
            sumaA = WEXITSTATUS(sumaA);

            // Lee la suma de B enviada por el segundo hijo
            int sumaB;
            read(pipefd[0], &sumaB, sizeof(int));

            // Calcula suma total y la envía por el pipe al padre
            int sumaTotal = sumaA + sumaB;

            write(pipefd[1], &sumaA, sizeof(int));
            write(pipefd[1], &sumaB, sizeof(int));
            write(pipefd[1], &sumaTotal, sizeof(int));
            exit(0);
        }

    } else {
        pid_t pid2 = fork();

        if (pid2 == 0) {
            // Segundo hijo: suma arreglo B y envía resultado al primer hijo
            int suma = sumarArreglo(B, N2);
            write(pipefd[1], &suma, sizeof(int));
            exit(0);
        } else {
            // Padre espera a ambos hijos y recibe suma final
            close(pipefd[1]);
            wait(NULL);
            wait(NULL);

            int sumaA, sumaB, sumaTotal;
            read(pipefd[0], &sumaA, sizeof(int));
            read(pipefd[0], &sumaB, sizeof(int));
            read(pipefd[0], &sumaTotal, sizeof(int));

            printf("Suma arreglo A: %d\n", sumaA);
            printf("Suma arreglo B: %d\n", sumaB);
            printf("Suma total: %d\n", sumaTotal);
        }
    }
    // Liberar memoria
    free(A);
    free(B);
    return 0;
}
