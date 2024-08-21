#include <stdio.h>
#include <omp.h>

#define N 1000000

int main() {
    long long sum = 0;
    double start_time, end_time;

    // Iniciar el tiempo
    start_time = omp_get_wtime();

    // Calcular la suma de los primeros N números naturales en paralelo
    #pragma omp parallel
    {
        long long local_sum = 0;

        #pragma omp for
        for (int i = 1; i <= N; i++) {
            local_sum += i;
        }

        #pragma omp critical
        {
            sum += local_sum;
        }
    }

    // Finalizar el tiempo
    end_time = omp_get_wtime();

    // Imprimir el resultado y el tiempo de ejecución
    printf("La suma de los primeros %d números naturales es: %lld\n", N, sum);
    printf("Tiempo de ejecución: %f segundos\n", end_time - start_time);

    return 0;
}