#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "L_Sondas.h"



#define MAX_WEIGHT 40
#define MAX_SONDAS 3


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
            printf("%d ", selecionados[j]);
            if (j < tamanho - 1)
                printf(", ");
        }
        printf("]\n");

        atual = atual->pProx;  // Avança para a próxima sonda na lista encadeada
    }
    free(usados);
    free(selecionados);
}


int main()
{
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);

    // Obtém o tempo inicial
    QueryPerformanceCounter(&start);
    int N_rochas;
    int comando=0;
    int n_sondas = MAX_SONDAS;
    L_Sondas ListaSonda;
    DadosSonda sondai;

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

        FLVazia_S(&ListaSonda);
        for (int i = 0; i < n_sondas; i++) {
            InicializaSonda(&sondai, (i + 1), MAX_WEIGHT); // Inicializa uma nova sonda com compartimento igual a 40
            LInsere_S(&ListaSonda, &sondai); // Insere a sonda na lista
        }


        if (fscanf(arquivo, "%d", &N_rochas) != 1 || N_rochas <= 0)
        {
            fprintf(stderr, "Número de rochas inválido no arquivo.\n");
            fclose(arquivo);
            return 1;
        }

        rocha *rochas = (rocha *)malloc(N_rochas * sizeof(rocha));
        if (rochas == NULL)
        {
            fprintf(stderr, "Erro ao alocar memória.\n");
            fclose(arquivo);
            return 1;
        }

        for (int i = 0; i < N_rochas; i++)
        {
            if (fscanf(arquivo, "%d %d", &rochas[i].peso, &rochas[i].valor) != 2)
            {
                fprintf(stderr, "Erro ao ler os dados do arquivo.\n");
                free(rochas);
                fclose(arquivo);
                return 1;
            }
        }

        fclose(arquivo);

        resolverSondas(&ListaSonda, n_sondas, rochas, N_rochas);

        // Obtém o tempo final
        QueryPerformanceCounter(&end);
        double tempoReal = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
        printf("Tempo Real Gasto: %.6f segundos\n", tempoReal);

        free(rochas);
        return 0;
    }
    else if (comando == 2){
        FLVazia_S(&ListaSonda);
        for (int i = 0; i < n_sondas; i++) {
            InicializaSonda(&sondai, (i + 1), MAX_WEIGHT); // Inicializa uma nova sonda com compartimento igual a 40
            LInsere_S(&ListaSonda, &sondai); // Insere a sonda na lista
        }

    
        printf("Insira o numero de rochas: ");
        if (scanf("%d", &N_rochas) != 1 || N_rochas <= 0)
        {
            fprintf(stderr, "Numero de rochas invalido.\n");
            return 1;
        }

        rocha *rochas = (rocha *)malloc(N_rochas * sizeof(rocha));
        if (rochas == NULL)
        {
            fprintf(stderr, "Erro ao alocar memória.\n");
            return 1;
        }

        for (int i = 0; i < N_rochas; i++)
        {
            printf("Insira o peso e valor da rocha %d (separados por espaco): ", i + 1);
            if (scanf("%d %d", &rochas[i].peso, &rochas[i].valor) != 2)
            {
                fprintf(stderr, "Entrada inválida.\n");
                free(rochas);
                return 1;
            }
        }

        resolverSondas(&ListaSonda, n_sondas, rochas, N_rochas);

        // Obtém o tempo final
        QueryPerformanceCounter(&end);
        double tempoReal = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
        printf("Tempo Real Gasto: %.6f segundos\n", tempoReal);

        free(rochas);
        return 0;
    }
}
