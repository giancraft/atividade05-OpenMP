#include <cstdio>
#include <omp.h>

#define NUM_THREADS 4
#define N 16

int main() {
    int a[N], b[N];
    omp_set_num_threads(NUM_THREADS);

#pragma omp parallel
    {
        int id = omp_get_thread_num();
        int nt = omp_get_num_threads();

        // ETAPA 1: cada thread preenche sua parte de 'a'
        for (int i = id; i < N; i += nt)
            a[i] = i * i;
        printf("Thread %d terminou a etapa 1\n", id);

        // Todas as threads esperam aqui ate que a etapa 1 termine
#pragma omp barrier

        // ETAPA 2: usa dados escritos por OUTRAS threads na etapa 1
        for (int i = id; i < N; i += nt)
            b[i] = a[(i + 1) % N] + a[i];
        printf("Thread %d terminou a etapa 2\n", id);
    }

    for (int i = 0; i < N; i++)
        printf("b[%d] = %d\n", i, b[i]);
    return 0;
}