#include "Compartimento.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void ini_L_C(L_Compart* lista) {
    lista->tamanho = 0;
}

void insere_ROCHA(L_Compart* lista, float valor, float peso, int usada) {
    if (lista->tamanho >= MAX) {
        printf("Tamanho Max da lista\n");
        return;
    }
    Rocha novaRocha = {valor, peso, usada};
    lista->vetor[lista->tamanho] = novaRocha;
    lista->tamanho++;
    return;
}

void remove_ROCHA(L_Compart* lista, int indice) {
    if (indice < 0 || indice >= lista->tamanho) {
        printf("Sem rocha\n");
        return;
    }
    for (int i = indice; i < lista->tamanho - 1; i++) {
        lista->vetor[i] = lista->vetor[i + 1];
    }
    lista->tamanho--;
    return;
}

void ImprimeCompartimento(L_Compart* lista) {
    if (lista->tamanho == 0) {
        printf("Vazia\n");
        return;
    }
    printf("Lista de Rochas:\n");
    for (int i = 0; i < lista->tamanho; i++) {
        printf("Rocha Indice:%d  Valor: %.2f  Peso: %.2f usada: %d\n", i, lista->vetor[i].valorRocha, lista->vetor[i].pesoRocha, lista->vetor[i].usada);
    }
}

void avaliaCombinacao(L_Compart* lista, int combinacao, float* valorTotal, float* pesoTotal) { // aqui na forca bruta ele combina tudo com tudo olhando peso e valor
    *valorTotal = 0;
    *pesoTotal = 0;
    for (int i = 0; i < lista->tamanho; i++) {
        if (combinacao % (int)pow(2, i + 1) >= (int)pow(2, i) && lista->vetor[i].usada == 0) { // exeto a usada
            *valorTotal += lista->vetor[i].valorRocha;
            *pesoTotal += lista->vetor[i].pesoRocha;
        
        }
    }
}


void melhor_rocha(L_Compart* lista) {
    int melhorCombinacao = 0;
    float melhorValor = 0;
    float melhorPeso = 0;

    int totalCombinacoes = (int)pow(2, lista->tamanho); // 2^n tamanho de comparacoes necessarias 

    for (int combinacao = 0; combinacao < totalCombinacoes; combinacao++) {
        float valorAtual, pesoAtual;
        avaliaCombinacao(lista, combinacao, &valorAtual, &pesoAtual); // algoritmo que gera as combinacoes

        if (pesoAtual <= 40 && valorAtual > melhorValor) { // verificacao para escolher o melhor
            melhorValor = valorAtual;
            melhorCombinacao = combinacao;
            melhorPeso = pesoAtual;
            
        }
    }

    marcaRochasUsadas(lista, melhorCombinacao); // essa funcao atribui 1 ao campo "usado" da rocha para nao escolher a mesma rocha

    printf("Valor: %.0f, Peso: %0.f", melhorValor, melhorPeso);
    printf(" Solucao:");
    printf("[");
    for (int i = 0; i < lista->tamanho; i++) {
        if ((melhorCombinacao / (int)pow(2, i)) % 2 == 1) { // verificacao usando bit para ver se a combinacao faz parte da solucao
            printf(" %d ", i);
        }
    }
    printf("]");
}

void marcaRochasUsadas(L_Compart* lista, int combinacao) {
    for (int i = 0; i < lista->tamanho; i++) {
        // poe 1 no campo usado so se a rocha for usada na solucao
        if (combinacao % (int)pow(2, i + 1) >= (int)pow(2, i)) {
            lista->vetor[i].usada = 1;
        }
    }
}