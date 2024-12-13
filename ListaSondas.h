#ifndef LISTASONDAS_H
#define LISTASONDAS_H

#include "SondaEspacial.h"

typedef DadosSonda item;
typedef struct Celula* Apontador_S;

typedef struct Celula {
    item chave;
    struct Celula* pProxx;
}Celula_S;

typedef struct{
    Celula_S itemSonda;
    Apontador_S pprimeira, pultima;
}L_Sondas;

void iniciaListaSonda(L_Sondas* pLista);
void insereSonda(L_Sondas* plista, DadosSonda xSonda);
void retiraSonda(L_Sondas* plista);
void ImprimeListaSondas(L_Sondas* plista);



#endif