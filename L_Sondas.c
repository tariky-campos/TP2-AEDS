#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "L_Sondas.h"

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