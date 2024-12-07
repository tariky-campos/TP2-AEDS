#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "L_Sondas.h"
#define MAX_SONDAS 3
#define MAX_WEIGHT 40


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
            fprintf(stderr, "Numero de rochas invalido no arquivo.\n");
            fclose(arquivo);
            return 1;
        }

        rocha *rochas = (rocha *)malloc(N_rochas * sizeof(rocha));
        if (rochas == NULL)
        {
            fprintf(stderr, "Erro ao alocar memoria.\n");
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
        printf("Tempo Real Gasto: %.2f segundos\n", tempoReal);

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
            fprintf(stderr, "Erro ao alocar memoria.\n");
            return 1;
        }

        for (int i = 0; i < N_rochas; i++)
        {
            printf("Insira o peso e valor da rocha %d (separados por espaco): ", i + 1);
            if (scanf("%d %d", &rochas[i].peso, &rochas[i].valor) != 2)
            {
                fprintf(stderr, "Entrada invalida.\n");
                free(rochas);
                return 1;
            }
        }

        resolverSondas(&ListaSonda, n_sondas, rochas, N_rochas);

        // Obtém o tempo final
        QueryPerformanceCounter(&end);
        double tempoReal = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
        printf("Tempo Real Gasto: %.2f segundos\n", tempoReal);

        free(rochas);
        return 0;
    }
}
