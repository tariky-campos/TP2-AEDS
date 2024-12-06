#ifndef DADOSSONDA_H
#define DADOSSONDA_H
#include "Compartimento.h"


typedef struct
{
    int idSonda;    
    L_Compart Compar_Rocha;
    float capacidade;    
} DadosSonda;

void InicializaSonda(DadosSonda *sonda, int idSonda, float capacidade);

int getId(DadosSonda *sonda);
float getCapacidade(DadosSonda *sonda);

void setId(DadosSonda *sonda, int id);
void setCapacidade(DadosSonda *sonda, float capacidade);
#endif