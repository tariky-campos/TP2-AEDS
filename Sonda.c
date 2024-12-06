#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sonda.h"

void InicializaSonda(DadosSonda *sonda, int id, float capacidade)
{
    setId(sonda, id);
    setCapacidade(sonda, capacidade);
    FLVazia_R(&sonda->Compar_Rocha);
}

int getId(DadosSonda *sonda)
{
    return sonda->idSonda;
}
float getCapacidade(DadosSonda *sonda)
{
    return sonda->capacidade;
}

void setId(DadosSonda *sonda, int id)
{
    sonda->idSonda = id;
}
void setCapacidade(DadosSonda *sonda, float capacidade)
{
    sonda->capacidade = capacidade;
}