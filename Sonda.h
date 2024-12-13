#ifndef DADOSSONDA_H
#define DADOSSONDA_H
#include "Compartimento.h"


typedef struct
{
    int idSonda;    
    L_Compart Compar_Rocha;
    int capacidade;    
} DadosSonda;

void InicializaSonda(DadosSonda *sonda, int idSonda, int capacidade);

int getId(DadosSonda *sonda);
int getCapacidade(DadosSonda *sonda);

void setId(DadosSonda *sonda, int id);
void setCapacidade(DadosSonda *sonda, int capacidade);
#endif