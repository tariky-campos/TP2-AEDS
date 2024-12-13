#ifndef SONDA_H
#define SONDA_H

#include "compartimento.h"

#define MAXCAP 40

typedef struct {
    int idSonda;
    int capacidade;
    int pesoAtual;
    int valorAtual;
    L_Compart CompartimentoR;
} DadosSonda;

void InicializaSonda(DadosSonda *sonda, int idSonda);
void ImprimeSonda(DadosSonda *sonda);
void LimpaSonda(DadosSonda *sonda);
int AdicionaRocha(DadosSonda *sonda, ROcha novaRocha);

#endif
