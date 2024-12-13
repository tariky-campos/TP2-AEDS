#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "combinacao.h"

#define NUM_SONDAS 3

int main() {
    FILE *arquivoEntrada = fopen("entrada.txt", "r");
    if (!arquivoEntrada) {
        fprintf(stderr, "Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    int n;
    fscanf(arquivoEntrada, "%d", &n);

    ROcha pares[n];
    for (int i = 0; i < n; i++) {
        fscanf(arquivoEntrada, "%d %d", &pares[i].peso, &pares[i].valor);
    }
    fclose(arquivoEntrada);

    int capacidade = 40;
    ROcha *combinacoesValidas;
    int tamanho;
    int usados[n];
    for (int i = 0; i < n; i++) usados[i] = 0;

    DadosSonda sondas[NUM_SONDAS];
    for (int i = 0; i < NUM_SONDAS; i++) {
        InicializaSonda(&sondas[i], i + 1);
    }

    clock_t inicio, fim;
    double tempoTotal = 0.0;

    int melhorIndices[n];

    for (int i = 0; i < NUM_SONDAS; i++) {
        inicio = clock();
        gerarCombinacoes(pares, n, capacidade, &combinacoesValidas, &tamanho, usados);
        fim = clock();
        tempoTotal += ((double)(fim - inicio)) / CLOCKS_PER_SEC;

        ROcha melhor = encontrarMaiorValor(combinacoesValidas, tamanho, melhorIndices, pares, n);

        printf("\nSonda %d: ", sondas[i].idSonda);
        printf("Peso: %d, Valor: %d\n", melhor.peso, melhor.valor);
        printf("Itens: ");
        for (int j = 0; j < n; j++) {
            if (melhorIndices[j]) {
                printf("%d (Peso: %d, Valor: %d), ", j, pares[j].peso, pares[j].valor);
                usados[j] = 1;
            }
        }
        printf("\n");
        free(combinacoesValidas);
    }

    printf("\nTempo total de execucao: %.5f segundos\n", tempoTotal);

    return 0;
}
