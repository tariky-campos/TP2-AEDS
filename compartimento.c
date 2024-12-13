#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Compartimento.h"

void FLVazia_R(L_Compart *pLista)
{
    pLista->pPrimeiro = (Apontador_R)malloc(sizeof(Celula_R));
    pLista->pUltimo = pLista->pPrimeiro;
    pLista->pPrimeiro->pProx = NULL;
}

int LEhVazia_R(L_Compart *pLista)
{
    return (pLista->pPrimeiro == pLista->pUltimo);
}

int LInsere_R(L_Compart *pLista, rocha *pRocha)
{
    pLista->pUltimo->pProx = (Apontador_R)malloc(sizeof(Celula_R));
    pLista->pUltimo = pLista->pUltimo->pProx;
    pLista->pUltimo->r = *pRocha;
    pLista->pUltimo->pProx = NULL;
    return 1;
}

void LImprime_R(L_Compart *pLista)
{

    Apontador_R pAux= NULL;
    pAux = pLista->pPrimeiro->pProx;
    while (pAux != NULL)
    {
        printf("Peso: %d\n", pAux->r.peso);
        printf("valor: %d\n", pAux->r.valor);
        pAux = pAux->pProx;
    }
}