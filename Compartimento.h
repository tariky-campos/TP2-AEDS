#ifndef COMPARTIMENTO_H
#define COMPARTIMENTO_H

#include "Rocha.h"
#define MAX 100

typedef struct {
    Rocha vetor[MAX];
    int tamanho;
} L_Compart;

void ini_LISTAC(L_Compart* lista);
void insere_Rocha(L_Compart* lista, float valor, float peso, int usada);
void remove_Rocha(L_Compart* lista, int indice);
void ImprimeCompartimento(L_Compart* lista);
void avaliaCombinacao(L_Compart* lista, int combinacao, float* valorTotal, float* pesoTotal);
void melhor_rocha(L_Compart* lista);
void marcaRochasUsadas(L_Compart* lista, int combinacao);

#endif