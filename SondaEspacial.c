#include <stdio.h>
#include <stdlib.h>
#include "SondaEspacial.h"

DadosSonda inicializaSonda(DadosSonda* sonda){
    
    setIdentificadorSonda(sonda, MVG);
    sonda->capacidadeSonda = 40;
    sonda->valorSonda = 0;
    sonda->pesoAtual = 0;
    MVG++;
    return *sonda;
}
void setIdentificadorSonda(DadosSonda* sonda, int identificador){
    sonda->identificadorSonda = identificador;
}
void set_CapacidadeSonda(DadosSonda* sonda, float capacidadeSonda){
    sonda->capacidadeSonda = capacidadeSonda;
}
void set_Valor(DadosSonda* sonda, float vel){
    sonda->valorSonda = vel;
}
void imprimeSonda(DadosSonda sonda) {
    printf("Sonda %d:", sonda.identificadorSonda);
    printf("Capacidade: %.2f ", sonda.capacidadeSonda);
    printf("Peso atual: %.2f ", sonda.pesoAtual);
    printf("Valor: %.2f ", sonda.valorSonda);
    printf("\n");
}
