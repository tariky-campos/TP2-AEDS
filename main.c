#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "L_Sondas.h"
#define MAX_SONDAS 3
#define MAX_WEIGHT 40

int main()
{
    int pesomax = MAX_WEIGHT;
    int N_rochas = 0;
    int n_sondas = MAX_SONDAS;

    L_Sondas ListaSonda;
    DadosSonda sondai;

    // Variáveis para medir o tempo
    clock_t inicio, fim;
    double tempo_execucao;

    // Início da medição de tempo
    inicio = clock();

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
    for (int i = 0; i < n_sondas; i++)
    {
        InicializaSonda(&sondai, (i + 1), MAX_WEIGHT); // Inicializa uma nova sonda com compartimento igual a 40
        LInsere_S(&ListaSonda, &sondai);               // Insere a sonda na lista
    }

    if (fscanf(arquivo, "%d", &N_rochas) != 1 || N_rochas <= 0)
    {
        fprintf(stderr, "Numero de rochas invalido no arquivo.\n");
        fclose(arquivo);
        return 1;
    }

    rocha *rochas = (rocha *)malloc(sizeof(rocha) * N_rochas);
    for (int i = 0; i < N_rochas; i++)
    {
        if (fscanf(arquivo, "%d %d", &rochas[i].peso, &rochas[i].valor) != 2)
        {
            fprintf(stderr, "Erro ao ler os dados do arquivo.\n");
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    int max_combinacoes = 1;
    for (int i = 0; i < N_rochas; i++)
    {
        max_combinacoes *= 2; // Multiplicação iterativa para 2^n
    }

    int **combinacoes = malloc(max_combinacoes * sizeof(int *)); // Para armazenar todas as combinações
    int *combinacao_atual = malloc(N_rochas * sizeof(int));
    int count = 0;

    gerar_combinacoes(0, N_rochas, rochas, combinacao_atual, combinacoes, &count);

    int *melhor_combinacao_indices = malloc(N_rochas * sizeof(int));
    int *usadas = calloc(N_rochas, sizeof(int)); // Vetor para rastrear rochas usadas

    colocar_na_sonda(&ListaSonda, combinacoes, max_combinacoes, N_rochas,
                     rochas, pesomax, melhor_combinacao_indices, usadas);

    // Libera memória
    for (int i = 0; i < max_combinacoes; i++)
    {
        free(combinacoes[i]);
    }
    free(combinacoes);
    free(combinacao_atual);
    free(melhor_combinacao_indices);
    free(usadas);
    // Fim da medição de tempo
    fim = clock();

// Calcula o tempo de execução (em segundos)
    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;

// Exibe o tempo de execução
    printf("\nTempo de execucao: %f segundos\n", tempo_execucao);


}

