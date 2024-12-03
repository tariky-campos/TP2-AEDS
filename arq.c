#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_ITEMS 20
#define MAX_WEIGHT 40

typedef struct
{
    int peso;
    int valor;
} Item;

int knapsack(Item items[], int n, int capacity, int selecionados[], int usados[])
{
    int dp[MAX_ITEMS + 1][MAX_WEIGHT + 1] = {0};
    int keep[MAX_ITEMS + 1][MAX_WEIGHT + 1] = {0};

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

    int w = capacity;
    int totalValor = dp[n][capacity];
    int idx = 0;

    for (int i = n; i > 0; i--)
    {
        if (keep[i][w])
        {
            selecionados[idx++] = i - 1;
            usados[i - 1] = 1;
            w -= items[i - 1].peso;
        }
    }
    selecionados[idx] = -1;
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

void resolverSondas(Item items[], int n, int capacidade, int sondas)
{
    int usados[MAX_ITEMS] = {0};

    for (int sonda = 1; sonda <= sondas; sonda++)
    {
        int selecionados[MAX_ITEMS];
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

int main()
{
    int N_rochas;
    int comando;
    int capacidade = MAX_WEIGHT;
    int sondas = 3;
    
    while (comando != 1 && comando != 2)
    {
        printf("1-Arquivo de teste  2-Terminal\n");
        scanf("%d", &comando);
    }
    if (comando == 1)
    {
        char nomeArquivo[100];
        printf("Digite o nome do arquivo de entrada: ");
        scanf("%49s", nomeArquivo);

        FILE *arquivo = fopen(nomeArquivo, "r");
        if (arquivo == NULL)
        {
            fprintf(stderr, "Erro ao abrir o arquivo %s.\n", nomeArquivo);
            return 1;
        }

        int N_rochas;
        if (fscanf(arquivo, "%d", &N_rochas) != 1 || N_rochas <= 0)
        {
            fprintf(stderr, "Número de rochas inválido no arquivo.\n");
            fclose(arquivo);
            return 1;
        }

        Item *itens = (Item *)malloc(N_rochas * sizeof(Item));
        if (itens == NULL)
        {
            fprintf(stderr, "Erro ao alocar memória.\n");
            fclose(arquivo);
            return 1;
        }

        for (int i = 0; i < N_rochas; i++)
        {
            if (fscanf(arquivo, "%d %d", &itens[i].peso, &itens[i].valor) != 2)
            {
                fprintf(stderr, "Erro ao ler os dados do arquivo.\n");
                free(itens);
                fclose(arquivo);
                return 1;
            }
        }

        fclose(arquivo);

        clock_t inicio = clock();
        resolverSondas(itens, N_rochas, capacidade, sondas);
        clock_t fim = clock();

        double tempoGasto = (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("Tempo Gasto: %.2f segundos\n", tempoGasto);

        free(itens);
        return 0;
    }
    else if (comando == 2)
    {
        printf("Insira o numero de rochas: ");
        if (scanf("%d", &N_rochas) != 1 || N_rochas <= 0)
        {
            fprintf(stderr, "Numero de rochas invalido.\n");
            return 1;
        }

        // Alocação dinâmica para itens
        Item *itens = (Item *)malloc(N_rochas * sizeof(Item));
        if (itens == NULL)
        {
            fprintf(stderr, "Erro ao alocar memória.\n");
            return 1;
        }

        // Entrada de peso e valor de cada rocha
        for (int i = 0; i < N_rochas; i++)
        {
            printf("Insira o peso e valor da rocha %d (separados por espaco): ", i + 1);
            if (scanf("%d %d", &itens[i].peso, &itens[i].valor) != 2)
            {
                fprintf(stderr, "Entrada inválida.\n");
                free(itens);
                return 1;
            }
        }

        int capacidade = MAX_WEIGHT;
        int sondas = 3;

        clock_t inicio = clock();
        resolverSondas(itens, N_rochas, capacidade, sondas);
        clock_t fim = clock();

        double tempoGasto = (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("Tempo Gasto: %.2f segundos\n", tempoGasto);

        // Liberação de memória
        free(itens);

        return 0;
    }
}
