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
            for (int j = 0; j < n; j++) {
                melhor_combinacao_indices[j] = combinacoes[i][j];
            }
        }
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
int adicionar_rocha_na_sonda(DadosSonda *sondai, rocha *r) {
    if (sondai->capacidade >= r->peso) {
        sondai->capacidade -= r->peso; // Atualiza a capacidade da sonda
        
        return 1; // Sucesso
    }
    return 0; // Falha
}
void colocar_na_sonda(L_Sondas *ListaSonda, int **combinacoes, int max_combinacoes, int N_rochas,
                      rocha *rochas, int pesomax, int *melhor_combinacao_indices, int *usadas) {
    for (int i = 0; i < 3; i++) { // Encontrar as 3 melhores combinações
        int valor = encontrar_melhor_combinacao(combinacoes, max_combinacoes, N_rochas, rochas,
                                                pesomax, melhor_combinacao_indices, usadas);
        if (valor == 0) {
            break; // Se não houver mais combinações válidas, para
        }

        int peso_total_sonda = 0;
        int valor_total_sonda = 0;

        printf("\nSonda %d ", i + 1);  // Indica o número da sonda
        printf("Solucao: [");  // Inicia a exibição da solução em formato de lista

        // Variável para controle de vírgula
        int primeiro = 1;

        // Tentar colocar as rochas da melhor combinação em uma sonda
        Apontador_S pAux = ListaSonda->pPrimeiro->pProx;
        for (int j = 0; j < N_rochas; j++) {
            if (melhor_combinacao_indices[j] == 1) { // Se a rocha está na melhor combinação
                if (!primeiro) {
                    printf(","); // Adiciona vírgula entre os elementos
                }
                printf("%d", j); // Imprime o índice da rocha

                primeiro = 0; // Após o primeiro elemento, as próximas rochas terão vírgula

                int alocada = 0;
                while (pAux != NULL) { // Percorrer sondas para encontrar espaço
                    if (adicionar_rocha_na_sonda(&pAux->sonda, &rochas[j])) {
                        alocada = 1;
                        peso_total_sonda += rochas[j].peso;
                        valor_total_sonda += rochas[j].valor;
                        break;
                    }
                    pAux = pAux->pProx; // Próxima sonda
                }
                if (!alocada) {
                    printf("Nao ha espaço suficiente em nenhuma sonda para a rocha #%d com peso %d.\n", j, rochas[j].peso);
                }
            }
        }

        printf("]");  // Fecha a lista de soluções

        // Imprimir valor total e peso total da sonda
        printf("\nValor total: %d\n", valor_total_sonda);
        printf("Peso total : %d\n", peso_total_sonda);

        // Marcar as rochas como usadas
        marcar_rochas_usadas(N_rochas, melhor_combinacao_indices, usadas);
    }
}
