#include <stdio.h>
#include <stdlib.h>
#include "L_Sondas.h"

void avaliarCombinacao(ROcha pares[], int n, int indices[], int *pesoTotal, int *valorTotal);
void gerarCombinacoes(ROcha pares[], int n, int capacidade, ROcha **combinacoesValidas, int *tamanho, int usados[]);
ROcha encontrarMaiorValor(ROcha combinacoes[], int tamanho, int *melhorIndices, ROcha pares[], int n);