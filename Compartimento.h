#ifndef COMPARTIMENTO_H
#define COMPARTIMENTO_H
#include "Rocha.h"

typedef struct CelulaRocha *Apontador_R;
typedef struct CelulaRocha
{
    rocha r;
    struct CelulaRocha *pProx;
} Celula_R;

typedef struct
{
    Apontador_R pPrimeiro;
    Apontador_R pUltimo;
} L_Compart;

void FLVazia_R(L_Compart *pLista);
int LEhVazia_R(L_Compart *pLista);
void LImprime_R(L_Compart *pLista);
int LInsere_R(L_Compart *pLista, rocha *pRocha);


#endif