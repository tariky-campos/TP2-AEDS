#ifndef LISTASONDAS_H
#define LISTASONDAS_H
#include "Sonda.h"

typedef DadosSonda Tipo_Sonda;

typedef struct Celulas *Apontador_S;
typedef struct Celulas
{
    DadosSonda sonda;
    struct Celulas *pProx;
} Celula_S;

typedef struct
{
    Apontador_S pPrimeiro;
    Apontador_S pUltimo;
} L_Sondas;

void FLVazia_S(L_Sondas *ListaS);
int LInsere_S(L_Sondas *ListaS, DadosSonda *pSonda);
void Imprime_S(L_Sondas *ListaS);
void gerar_combinacoes(int index, int n, rocha *rochas, int *combinacao_atual, int **combinacoes, int *count);
int encontrar_melhor_combinacao(int **combinacoes, int total_combinacoes, int n, rocha *rochas, int pesomax, int *melhor_combinacao_indices, int *usadas);
void marcar_rochas_usadas(int n, int *melhor_combinacao_indices, int *usadas);
#endif