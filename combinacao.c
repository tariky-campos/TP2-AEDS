#include "combinacao.h"



// Função para calcular peso e valor totais de uma combinação
void avaliarCombinacao(ROcha pares[], int n, int indices[], int *pesoTotal, int *valorTotal) {
    *pesoTotal = 0;
    *valorTotal = 0;
    for (int i = 0; i < n; i++) {
        if (indices[i]) {
            *pesoTotal += pares[i].peso;
            *valorTotal += pares[i].valor;
        }
    }
}

// Função para gerar todas as combinações possíveis
void gerarCombinacoes(ROcha pares[], int n, int capacidade, ROcha **combinacoesValidas, int *tamanho, int usados[]) {
    int totalCombinacoes = 1 << n; // 2^n combinações possíveis
    *tamanho = 0;

    // Alocar memória para armazenar combinações válidas
    *combinacoesValidas = malloc(totalCombinacoes * sizeof(ROcha));

    for (int i = 0; i < totalCombinacoes; i++) {
        int pesoTotal = 0, valorTotal = 0;
        int indices[n];

        for (int j = 0; j < n; j++) {
            indices[j] = (i >> j) & 1;
        }

        avaliarCombinacao(pares, n, indices, &pesoTotal, &valorTotal);

        if (pesoTotal <= capacidade) {
            int valido = 1;
            for (int j = 0; j < n; j++) {
                if (indices[j] && usados[j]) {
                    valido = 0;
                    break;
                }
            }

            if (valido) {
                (*combinacoesValidas)[*tamanho].peso = pesoTotal;
                (*combinacoesValidas)[*tamanho].valor = valorTotal;
                (*tamanho)++;
            }
        }
    }
}

// Função para encontrar a combinação com o maior valor
ROcha encontrarMaiorValor(ROcha combinacoes[], int tamanho, int *melhorIndices, ROcha pares[], int n) {
    ROcha melhor = {0, 0};
    for (int i = 0; i < tamanho; i++) {
        if (combinacoes[i].valor > melhor.valor) {
            melhor = combinacoes[i];
        }
    }

    int totalCombinacoes = 1 << n;
    for (int i = 0; i < totalCombinacoes; i++) {
        int pesoTotal = 0, valorTotal = 0;
        int indices[n];

        for (int j = 0; j < n; j++) {
            indices[j] = (i >> j) & 1;
        }

        avaliarCombinacao(pares, n, indices, &pesoTotal, &valorTotal);

        if (pesoTotal == melhor.peso && valorTotal == melhor.valor) {
            for (int j = 0; j < n; j++) {
                melhorIndices[j] = indices[j];
            }
            break;
        }
    }

    return melhor;
}
