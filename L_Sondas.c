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

int knapsack(rocha rochas[], int n, int capacity, int *selecionados, int *usados)
{
    // Alocação dinâmica para dp e keep
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    int **keep = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++)
    {
        dp[i] = (int *)malloc((capacity + 1) * sizeof(int));
        keep[i] = (int *)malloc((capacity + 1) * sizeof(int));
    }

    // Inicializar dp e keep com 0
    for (int i = 0; i <= n; i++)
        for (int w = 0; w <= capacity; w++)
            dp[i][w] = keep[i][w] = 0;

    // Preenchendo dp e keep
    for (int i = 1; i <= n; i++)
    {
        for (int w = 0; w <= capacity; w++)
        {
            if (rochas[i - 1].peso <= w && !usados[i - 1])
            {
                int incluir = rochas[i - 1].valor + dp[i - 1][w - rochas[i - 1].peso];
                int excluir = dp[i - 1][w];
                if (incluir > excluir)
                {
                    dp[i][w] = incluir;
                    keep[i][w] = 1;
                }
                else
                {
                    dp[i][w] = excluir;
                }
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Reconstruir solução
    int w = capacity;
    int totalValor = dp[n][capacity];
    int idx = 0;
    int pesoAcumulado = 0;

    for (int i = n; i > 0; i--)
    {
        if (keep[i][w])
        {
            if (pesoAcumulado + rochas[i - 1].peso > MAX_WEIGHT)
                continue;

            selecionados[idx++] = i - 1;
            usados[i - 1] = 1;
            w -= rochas[i - 1].peso;
            pesoAcumulado += rochas[i - 1].peso;
        }
    }
    selecionados[idx] = -1;

    // Liberar memória das matrizes dp e keep
    for (int i = 0; i <= n; i++)
    {
        free(dp[i]);
        free(keep[i]);
    }
    free(dp);
    free(keep);

    return totalValor;
}
void ordenarArray(int array[], int tamanho)
{
    for (int i = 0; i < tamanho - 1; i++)
    {
        for (int j = i + 1; j < tamanho; j++)
        {
            if (array[i] > array[j])
            {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

void resolverSondas(L_Sondas *ListaS, int n_sondas, rocha rochas[], int n)
{
    int *usados = (int*)malloc(n * sizeof(int));  // Alocação dinâmica
    if (usados == NULL) {
        fprintf(stderr, "Falha na alocação de memória para o vetor usados.\n");
        return ;
    }
     // Inicializa todos os valores de usados como 0
    memset(usados, 0, n * sizeof(int));
    int *selecionados = (int*)malloc(n * sizeof(int));  // Alocação dinâmica
    if (selecionados == NULL) {
        fprintf(stderr, "Falha na alocação de memória para o vetor selecionados.\n");
        free(usados);
        return ;
    }

    Apontador_S atual = ListaS->pPrimeiro->pProx;  // Ponteiro para o primeiro elemento da lista encadeada

    for (int i = 0; i < n_sondas && atual != NULL; i++) {

        int valorTotal = knapsack(rochas, n, atual->sonda.capacidade, selecionados, usados);

        int tamanho = 0;
        while (selecionados[tamanho] != -1) {
            tamanho++;
        }

        ordenarArray(selecionados, tamanho);

        int pesoTotal = 0;
        printf("Sonda %d: Peso ", atual->sonda.idSonda);  // Usando 'atual->sonda.id' para acessar o id da sonda corrente
        for (int j = 0; j < tamanho; j++) {
            int idx = selecionados[j];
            pesoTotal += rochas[idx].peso;
        }
        printf("%d, Valor %d, Solucao [", pesoTotal, valorTotal);
        for (int j = 0; j < tamanho; j++) {
            printf("%d", selecionados[j]);
            if (j < tamanho - 1)
                printf(", ");
        }
        printf("]\n");

        atual = atual->pProx;  // Avança para a próxima sonda na lista encadeada
    }
    free(usados);
    free(selecionados);
}
