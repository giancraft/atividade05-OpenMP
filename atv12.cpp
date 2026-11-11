#include <cstdio>
#include <cstdlib>
#include <omp.h>

#define PONTOS_POR_THREAD 5000000L

int main() {
    long dentro = 0;
    long total = 0;
    double pi = 0.0;

    omp_set_num_threads(4);

#pragma omp parallel
    {
        int id = omp_get_thread_num();
        unsigned int seed = 1234 + id;    // semente propria (rand_r e thread-safe)
        long local = 0;

        for (long i = 0; i < PONTOS_POR_THREAD; i++) {
            double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;
            if (x * x + y * y <= 1.0)
                local++;
        }

#pragma omp atomic
        dentro += local;

#pragma omp atomic
        total += PONTOS_POR_THREAD;

        // Garante que TODAS as threads terminaram a geracao e somaram
#pragma omp barrier

#pragma omp single
        {
            pi = 4.0 * (double)dentro / (double)total;
        }
    }

    printf("Pontos dentro do circulo: %ld de %ld\n", dentro, total);
    printf("PI estimado = %f\n", pi);
    return 0;
}