#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "L_Sondas.h"
#define MAX_WEIGHT 40


// Inicializa a lista de sondas vazia
void FLVazia_S(L_Sondas *L_Sondas) {
    L_Sondas->pPrimeiro = (Apontador_S)malloc(sizeof(Celula_S)); // Aloca a célula cabeça
    L_Sondas->pUltimo = L_Sondas->pPrimeiro; // Inicializa o último apontando para o primeiro
    L_Sondas->pPrimeiro->pProx = NULL; // Define o próximo da célula cabeça como NULL
}

// Insere uma nova sonda no final da lista
int LInsere_S(L_Sondas *L_Sondas, DadosSonda *pSonda) {
    L_Sondas->pUltimo->pProx = (Apontador_S)malloc(sizeof(Celula_S)); // Aloca nova célula
    L_Sondas->pUltimo = L_Sondas->pUltimo->pProx; // Move o ponteiro do último
    L_Sondas->pUltimo->sonda = *pSonda; // Copia os dados da sonda para a nova célula
    L_Sondas->pUltimo->pProx = NULL; // Define o próximo como NULL
    return 1; // Retorna sucesso
}


// Imprime os dados de todas as sondas na lista
void Imprime_S(L_Sondas *L_Sondas) {
    Apontador_S pAux = L_Sondas->pPrimeiro->pProx; // Começa após a célula cabeça
    while (pAux != NULL) {
        printf("ID: %d\n", pAux->sonda.idSonda);
        printf("Capacidade: %.2f\n", pAux->sonda.capacidade);
        pAux = pAux->pProx;
    }
}

void gerar_combinacoes(int index, int n, rocha *rochas, int *combinacao_atual, int **combinacoes, int *count) {
    if (index == n) {
        combinacoes[*count] = malloc(n * sizeof(int)); // Aloca espaço para a combinação
        for (int i = 0; i < n; i++) {
            combinacoes[*count][i] = combinacao_atual[i]; // Salva a combinação
        }
        (*count)++;
        return;
    }

    // Sem incluir a rocha atual
    combinacao_atual[index] = 0;
    gerar_combinacoes(index + 1, n, rochas, combinacao_atual, combinacoes, count);

    // Incluindo a rocha atual
    combinacao_atual[index] = 1;
    gerar_combinacoes(index + 1, n, rochas, combinacao_atual, combinacoes, count);
}
// Função para calcular a melhor combinação
int encontrar_melhor_combinacao(int **combinacoes, int total_combinacoes, int n, rocha *rochas, int pesomax, int *melhor_combinacao_indices, int *usadas) {
    int melhor_valor = 0;
    int melhor_peso = 0;

    for (int i = 0; i < total_combinacoes; i++) {
        int peso_atual = 0;
        int valor_atual = 0;
        int valido = 1;

        for (int j = 0; j < n; j++) {
            if (combinacoes[i][j] == 1) {
                if (usadas[j]) {
                    valido = 0; // Ignora combinações com rochas já usadas
                    break;
                }
                peso_atual += rochas[j].peso;
                valor_atual += rochas[j].valor;
            }
        }

        if (!valido) continue;

        // Verifica se a combinação é válida e melhor
        if (peso_atual <= pesomax && valor_atual > melhor_valor) {
            melhor_valor = valor_atual;
            melhor_peso = peso_atual;
            for (int j = 0; j < n; j++) {
                melhor_combinacao_indices[j] = combinacoes[i][j];
            }
        }
    }
    // Exibe a melhor combinação
    if (melhor_valor > 0) {
        printf("Melhor combinação:\n");
        for (int i = 0; i < n; i++) {
            printf("%d ", melhor_combinacao_indices[i]);
        }
        printf("\nPeso total: %d\nValor total: %d\n", melhor_peso, melhor_valor);
    } else {
        printf("Nenhuma combinação válida encontrada.\n");
    }

    return melhor_valor;
}
// Marca as rochas usadas na melhor combinação
void marcar_rochas_usadas(int n, int *melhor_combinacao_indices, int *usadas) {
    for (int i = 0; i < n; i++) {
        if (melhor_combinacao_indices[i] == 1) {
            usadas[i] = 1;
        }
    }
}



