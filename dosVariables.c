#include <stdio.h>
#include <omp.h>

// Definimos el número de iteraciones para el ciclo for
#define N 10

int main() {
    int variable1 = 0; 
    int variable2 = 10;

    // Imprimimos los valores iniciales de las variables
    printf("Valor inicial de variable1: %d\n", variable1);
    printf("Valor inicial de variable2: %d\n\n", variable2);

    
    #pragma omp parallel
    {
        int i, idHilo, variable2_private = variable2;

        // Obtenemos el ID del hilo actual
        idHilo = omp_get_thread_num();

        // Distribuimos las iteraciones del ciclo for entre los hilos
        #pragma omp for
        for (i = 0; i < N; ++i) {
            #pragma omp atomic
            variable1 += i;
            variable2_private += i;
            printf("Hilo %d: variable1 = %d, variable2_private = %d\n", idHilo, variable1, variable2_private);
        }
    }

    // Imprimimos los valores finales de las variables después de la región paralela
    printf("\nValor final de variable1: %d\n", variable1);
    printf("Valor final de variable2: %d\n", variable2);

    return 0;
}