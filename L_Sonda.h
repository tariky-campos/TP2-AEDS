#ifndef LISTASONDAS_H
#define LISTASONDAS_H

#include "Sonda.h"

typedef DadosSonda item;
typedef struct Celula* apontador;

typedef struct Celula {
    item chaveSonda;
    struct Celula* pProxSonda;
}celulaSonda;

typedef struct{
    celulaSonda itemSonda;
    apontador pprimeiro, pultimo;
}L_Sondas;

void ini_LISTASONDA(L_Sondas* pLista);
void insereSonda(L_Sondas* plista, DadosSonda xSonda);
void retiraSonda(L_Sondas* plista);
void ImprimeListaSondas(L_Sondas* plista);



#endif