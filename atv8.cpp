#include <cstdio>
#include <cstdlib>
#include <omp.h>

#define N 1000000
#define NUM_BINS 10

int main() {
    int *vetor = (int *)malloc(N * sizeof(int));
    int histograma[NUM_BINS] = {0};   // inicializado com zeros

    // Preenche o vetor com valores entre 0 e NUM_BINS-1 (serial)
    srand(42);
    for (int i = 0; i < N; i++)
        vetor[i] = rand() % NUM_BINS;

#pragma omp parallel for
    for (int i = 0; i < N; i++) {
        int valor = vetor[i];
#pragma omp critical
        {
            histograma[valor]++;
        }
    }

    long total = 0;
    for (int b = 0; b < NUM_BINS; b++) {
        printf("Bin %d: %d\n", b, histograma[b]);
        total += histograma[b];
    }
    printf("Total contado: %ld (esperado: %d)\n", total, N);

    free(vetor);
    return 0;
}