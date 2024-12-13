#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sonda.h"

void InicializaSonda(DadosSonda *sonda, int id, int capacidade)
{
    setId(sonda, id);
    setCapacidade(sonda, capacidade);
    FLVazia_R(&sonda->Compar_Rocha);
}

int getId(DadosSonda *sonda)
{
    return sonda->idSonda;
}
int getCapacidade(DadosSonda *sonda)
{
    return sonda->capacidade;
}

void setId(DadosSonda *sonda, int id)
{
    sonda->idSonda = id;
}
void setCapacidade(DadosSonda *sonda, int capacidade)
{
    sonda->capacidade = capacidade;
}