#include <cstdio>
#include <omp.h>

int main() {
    int dado = 0;        // variavel compartilhada com o dado produzido
    int pronto = 0;      // flag: 1 = dado disponivel

    omp_set_num_threads(4);

#pragma omp parallel shared(dado, pronto)
    {
        int id = omp_get_thread_num();

        if (id == 0) {
            // PRODUTORA
            dado = 42;
            printf("Produtora (thread 0) gerou o dado: %d\n", dado);

#pragma omp flush(dado)      // publica o dado na memoria
            pronto = 1;
#pragma omp flush(pronto)    // publica a flag
        } else {
            // CONSUMIDORAS
            int visto;
            do {
#pragma omp flush(pronto)    // le o valor mais recente da flag
                visto = pronto;
            } while (!visto);

#pragma omp flush(dado)          // le o valor mais recente do dado
            printf("Consumidora (thread %d) leu o dado: %d -> processado: %d\n",
                   id, dado, dado * 2);
        }
    }
    return 0;
}