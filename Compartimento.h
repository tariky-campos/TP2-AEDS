#ifndef Compartimento_h
#define Compartimento_h
#include <stdio.h>
#include "rocha.h"

typedef struct {
    ROcha rocha[1000];
    int primeiro;
    int ultimo;
}L_Compart;



void FLvazia(L_Compart* lista_s);
int LEhVazia(L_Compart* lista_s);
int LInsere(L_Compart* lista_s, ROcha x);
int Lretira(L_Compart* lista_s, int p, ROcha *px);
void LImprime(L_Compart* pLista);

#endif