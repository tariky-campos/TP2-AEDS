#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compartimento.h"



void FLvazia(L_Compart* comp){
    comp->primeiro = 0;
    comp->ultimo = comp->primeiro;
};

int LEhVazia(L_Compart* comp){
    return(comp->primeiro == comp->ultimo);
};

int LInsere(L_Compart* comp, ROcha x){
    if(comp->ultimo == 1000)
        return 0;
    comp->rocha[comp->ultimo++] = x;
    return 1;
};
int Lretira(L_Compart* comp, int p, ROcha *px){
    int cont;
    if(LEhVazia(comp) || p >= comp->ultimo || p < 0)
        return 0;
    
    *px = comp->rocha[p];
    for(cont = p+1; cont <= comp->ultimo; cont++){
        comp->rocha[cont - 1] = comp->rocha[cont];
    }
    return 1;
};


void LImprime(L_Compart* pLista)
{
 int i;
 for (i = pLista->primeiro; i < pLista->ultimo; i++)
 printf(" %d %d\n", pLista->rocha[i].peso, pLista->rocha[i].valor);
} 