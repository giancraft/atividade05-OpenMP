#include <cstdio>
#include <cstdlib>
#include <omp.h>

#define N 1000000

int main() {
    int *vetor = (int *)malloc(N * sizeof(int));
    int pares = 0, impares = 0;

    srand(42);
    for (int i = 0; i < N; i++)
        vetor[i] = rand() % 1000;

#pragma omp parallel for
    for (int i = 0; i < N; i++) {
        if (vetor[i] % 2 == 0) {
#pragma omp atomic
            pares++;
        } else {
#pragma omp atomic
            impares++;
        }
    }

    printf("Pares:   %d\n", pares);
    printf("Impares: %d\n", impares);
    printf("Total:   %d (esperado: %d)\n", pares + impares, N);

    free(vetor);
    return 0;
}