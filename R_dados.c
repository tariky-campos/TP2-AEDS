#include "R_dados.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_WEIGHT 40



int knapsack(R_dados items[], int n, int capacity, int selecionados[], int usados[])
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
            if (items[i - 1].peso <= w && !usados[i - 1])
            {
                int incluir = items[i - 1].valor + dp[i - 1][w - items[i - 1].peso];
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
            if (pesoAcumulado + items[i - 1].peso > MAX_WEIGHT)
                continue;

            selecionados[idx++] = i - 1;
            usados[i - 1] = 1;
            w -= items[i - 1].peso;
            pesoAcumulado += items[i - 1].peso;
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


void resolverSondas(R_dados items[], int n, int capacidade, int sondas)
{
    int usados[n];
    for (int i = 0; i < n; i++)
        usados[i] = 0;

    for (int sonda = 1; sonda <= sondas; sonda++)
    {
        int selecionados[n];
        int valorTotal = knapsack(items, n, capacidade, selecionados, usados);

        int tamanho = 0;
        while (selecionados[tamanho] != -1)
        {
            tamanho++;
        }

        ordenarArray(selecionados, tamanho);

        int pesoTotal = 0;
        printf("Sonda %d: Peso ", sonda);
        for (int i = 0; i < tamanho; i++)
        {
            int idx = selecionados[i];
            pesoTotal += items[idx].peso;
        }
        printf("%d, Valor %d, Solucao [", pesoTotal, valorTotal);
        for (int i = 0; i < tamanho; i++)
        {
            printf("%d", selecionados[i]);
            if (i < tamanho - 1)
                printf(", ");
        }
        printf("]\n");
    }
}
