#include "Rocha.h"
#include <stdio.h>
#include <stdlib.h>

void set_valor(Rocha* rocha, float valorRocha){
    rocha->valorRocha = valorRocha;
}

void set_pesoRocha(Rocha* rocha, float pesoRocha){
    rocha->pesoRocha = pesoRocha;
}

void set_usada(Rocha* rocha, int usada) {
    rocha->usada = usada;
}

void iniciaRocha(Rocha* rocha, float valorRocha, float pesoRocha, int usada){
    set_pesoRocha(rocha, pesoRocha);
    set_valor(rocha, valorRocha);
    set_usada(rocha, usada);
}

void imprimeRocha(Rocha rocha){
    printf("Valor Rocha rocha: %f\n", rocha.valorRocha);
    printf("Peso rocha: %f\n", rocha.pesoRocha);
    if (rocha.usada == 1) {
        printf("Usada\n");
    } else {
        printf("Disponivel\n");
    }
}