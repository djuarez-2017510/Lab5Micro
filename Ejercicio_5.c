#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 131072
#define CUTOFF 1024 

long parallel_count_key(long Nlen, long *a, long key, int depth) {
    long count = 0;

    if (Nlen <= CUTOFF) {
        for (int i = 0; i < Nlen; i++)
            if (a[i] == key) count++;
    } else {
        long mid = Nlen / 2;
        long count_left = 0, count_right = 0;

        #pragma omp task shared(count_left) if(depth < omp_get_max_threads())
        count_left = parallel_count_key(mid, a, key, depth + 1);

        #pragma omp task shared(count_right) if(depth < omp_get_max_threads())
        count_right = parallel_count_key(Nlen - mid, a + mid, key, depth + 1);

        #pragma omp taskwait
        count = count_left + count_right;
    }

    return count;
}

int main() {
    long a[N], key = 42, nkey = 0;

    for (long i = 0; i < N; i++) a[i] = rand() % N;

    a[N % 43] = key;
    a[N % 73] = key;
    a[N % 3] = key;

    #pragma omp parallel
    {
        #pragma omp single
        nkey = parallel_count_key(N, a, key, 0);
    }

    printf("Numero de veces que 'key' aparece paralelamente: %ld\n", nkey);

    return 0;
}
