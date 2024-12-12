#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "L_Sondas.h"
#define MAX_SONDAS 3
#define MAX_WEIGHT 40


int main()
{
    int pesomax=MAX_WEIGHT;
    int N_rochas=0;
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

        rocha *rochas = (rocha*) malloc(sizeof(rocha) * N_rochas);
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
        for (int i = 0; i < N_rochas; i++) {
            max_combinacoes *= 2; // Multiplicação iterativa para 2^n
        }

        int **combinacoes = malloc(max_combinacoes * sizeof(int *)); // Para armazenar todas as combinações
        int *combinacao_atual = malloc(N_rochas * sizeof(int));
        int count = 0;

        gerar_combinacoes(0, N_rochas, rochas, combinacao_atual, combinacoes, &count);

        int *melhor_combinacao_indices = malloc(N_rochas * sizeof(int));
        int *usadas = calloc(N_rochas, sizeof(int)); // Vetor para rastrear rochas usadas

        for (int i = 0; i < 3; i++) { // Encontrar as 3 melhores combinações
            printf("\nMelhor combinação #%d:\n", i + 1);
            int valor = encontrar_melhor_combinacao(combinacoes, max_combinacoes, N_rochas, rochas, pesomax, melhor_combinacao_indices, usadas);
            if (valor == 0) {
                break; // Se não houver mais combinações válidas, para
            }
            marcar_rochas_usadas(N_rochas, melhor_combinacao_indices, usadas);
        }
                 // Libera memória
        for (int i = 0; i < max_combinacoes; i++) {
            free(combinacoes[i]);
        }
        free(combinacoes);
        free(combinacao_atual);
        free(melhor_combinacao_indices);
        free(usadas);
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
        rocha *rochas = (rocha*) malloc(sizeof(rocha) * N_rochas);
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
        int max_combinacoes = 1;
        for (int i = 0; i < N_rochas; i++) {
            max_combinacoes *= 2; // Multiplicação iterativa para 2^n
        }

        int **combinacoes = malloc(max_combinacoes * sizeof(int *)); // Para armazenar todas as combinações
        int *combinacao_atual = malloc(N_rochas * sizeof(int));
        int count = 0;

        gerar_combinacoes(0, N_rochas, rochas, combinacao_atual, combinacoes, &count);
        
        int *melhor_combinacao_indices = malloc(N_rochas * sizeof(int));
        int *usadas = calloc(N_rochas, sizeof(int)); // Vetor para rastrear rochas usadas

        for (int i = 0; i < 3; i++) { // Encontrar as 3 melhores combinações
            printf("\nMelhor combinação #%d:\n", i + 1);
            int valor = encontrar_melhor_combinacao(combinacoes, max_combinacoes, N_rochas, rochas, pesomax, melhor_combinacao_indices, usadas);
            if (valor == 0) {
                break; // Se não houver mais combinações válidas, para
            }
            marcar_rochas_usadas(N_rochas, melhor_combinacao_indices, usadas);
        }
         // Libera memória
        for (int i = 0; i < max_combinacoes; i++) {
            free(combinacoes[i]);
        }
        free(combinacoes);
        free(combinacao_atual);
        free(melhor_combinacao_indices);
        free(usadas);
    }
    return 0;
}
