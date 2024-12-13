#ifndef SONDAESPACIAL_H
#define SONDAESPACIAL_H
#include "Compartimento.h"
extern int mMVG;

typedef struct {
    int identificadorSonda;
    float capacidadeSonda;
    float valorSonda;
    float pesoAtual;
} DadosSonda;

DadosSonda inicil_sonda(DadosSonda* sonda); 
void imprimeSonda(DadosSonda sonda);
void setIdentificadorSonda(DadosSonda* sonda, int identificador);
void set_CapacidadeSonda(DadosSonda* sonda, float capacidadeSonda);
void set_Valor(DadosSonda* sonda, float vel);




#endif