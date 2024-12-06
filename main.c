#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "R_dados.h"
#define MAX_WEIGHT 40

int main()
{
    struct timeval inicio, fim;
    gettimeofday(&inicio, NULL);

    int comando, N_rochas, capacidade = MAX_WEIGHT, sondas = 3;

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
            printf("Erro ao abrir o arquivo.\n");
            return 1;
        }

        if (fscanf(arquivo, "%d", &N_rochas) != 1 || N_rochas <= 0)
        {
            fprintf(stderr, "Número de rochas inválido no arquivo.\n");
            fclose(arquivo);
            return 1;
        }

        R_dados *itens = (R_dados *)malloc(N_rochas * sizeof(R_dados));
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

        resolverSondas(itens, N_rochas, capacidade, sondas);

        free(itens);
    }
    else if (comando == 2)
    {
        printf("Insira o número de rochas: ");
        if (scanf("%d", &N_rochas) != 1 || N_rochas <= 0)
        {
            fprintf(stderr, "Número de rochas inválido.\n");
            return 1;
        }

        R_dados *itens = (R_dados *)malloc(N_rochas * sizeof(R_dados));
        if (itens == NULL)
        {
            fprintf(stderr, "Erro ao alocar memória.\n");
            return 1;
        }

        for (int i = 0; i < N_rochas; i++)
        {
            printf("Insira o peso e valor da rocha %d (separados por espaço): ", i + 1);
            if (scanf("%d %d", &itens[i].peso, &itens[i].valor) != 2)
            {
                fprintf(stderr, "Entrada inválida.\n");
                free(itens);
                return 1;
            }
        }

        resolverSondas(itens, N_rochas, capacidade, sondas);

        free(itens);
    }

    gettimeofday(&fim, NULL);
    double tempoReal = (fim.tv_sec - inicio.tv_sec) + (fim.tv_usec - inicio.tv_usec) / 1000000.0;
    printf("Tempo Real Gasto: %.2f segundos\n", tempoReal);

    return 0;
}
