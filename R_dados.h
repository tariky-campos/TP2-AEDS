#ifndef R_DADOS_H
#define R_DADOS_H


typedef struct R_dados{
    int peso, valor;
}R_dados;

///////// Operacoes

int knapsack(R_dados items[], int n, int capacity, int selecionados[], int usados[]);
void ordenarArray(int array[], int tamanho);
void resolverSondas(R_dados items[], int n, int capacidade, int sondas);

#endif