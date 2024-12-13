#include <stdio.h>
#include <stdlib.h>
#include "Sonda.h"
#include "compartimento.h"

// Inicializa uma sonda com um ID específico e configurações padrão
void InicializaSonda(DadosSonda *sonda, int idSonda) {
    sonda->idSonda = idSonda;
    sonda->capacidade = MAXCAP;
    sonda->pesoAtual = 0;
    sonda->valorAtual = 0;
    FLvazia(&sonda->CompartimentoR);  // Inicializa o compartimento vazio
}

// Adiciona uma rocha à sonda, verificando se há espaço suficiente
int AdicionaRocha(DadosSonda *sonda, ROcha novaRocha) {
    if (sonda->pesoAtual + novaRocha.peso <= sonda->capacidade) {
        if (LInsere(&sonda->CompartimentoR, novaRocha)) {
            sonda->pesoAtual += novaRocha.peso;
            sonda->valorAtual += novaRocha.valor;
            return 1; // Sucesso
        }
    }
    return 0; // Falha por falta de espaço ou erro na inserção
}

// Imprime informações detalhadas da sonda
void ImprimeSonda(DadosSonda *sonda) {
    printf("Sonda %d:\n", sonda->idSonda);
    printf("Capacidade: %d\n", sonda->capacidade);
    printf("Peso Atual: %d\n", sonda->pesoAtual);
    printf("Valor Total: %d\n", sonda->valorAtual);
    printf("Rochas no Compartimento:\n");
    LImprime(&sonda->CompartimentoR);
}

// Remove todas as rochas da sonda e redefine seus valores
void LimpaSonda(DadosSonda *sonda) {
    ROcha temp;
    while (!LEhVazia(&sonda->CompartimentoR)) {
        Lretira(&sonda->CompartimentoR, 0, &temp);
    }
    sonda->pesoAtual = 0;
    sonda->valorAtual = 0;
}
