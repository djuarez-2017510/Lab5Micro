#include <stdio.h>
#include <omp.h>

#define N 10
#define FIB_LIMIT 20
#define ARR_SIZE 10

// Función para calcular el factorial de un número
void factorial(int n, long long *result) {
    *result = 1;
    for (int i = 1; i <= n; i++) {
        *result *= i;
    }
}

// Función para generar la serie de Fibonacci hasta un límite
void fibonacci(int limit, long long fib[]) {
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i < limit; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }
}

// Función para encontrar el máximo en un arreglo
void find_max(int arr[], int size, int *max) {
    *max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > *max) {
            *max = arr[i];
        }
    }
}

int main() {
    int arr[ARR_SIZE] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 0};
    long long fact_result;
    long long fib_result[FIB_LIMIT];
    int max_result;

    // Ejecutar las funciones en paralelo usando omp sections
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            factorial(N, &fact_result);
            printf("Factorial de %d es: %lld\n", N, fact_result);
        }

        #pragma omp section
        {
            fibonacci(FIB_LIMIT, fib_result);
            printf("Serie de Fibonacci hasta %d términos: ", FIB_LIMIT);
            for (int i = 0; i < FIB_LIMIT; i++) {
                printf("%lld ", fib_result[i]);
            }
            printf("\n");
        }

        #pragma omp section
        {
            find_max(arr, ARR_SIZE, &max_result);
            printf("El máximo en el arreglo es: %d\n", max_result);
        }
    }

    return 0;
}