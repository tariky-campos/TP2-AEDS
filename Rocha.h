#ifndef ROCHA_H
#define ROCHA_H


typedef struct{
    float valorRocha;
    float pesoRocha;
    int usada;
} Rocha;

void set_valor(Rocha* rocha, float valorRocha);
void set_pesoRocha(Rocha* rocha, float pesoRocha);
void set_usada(Rocha* rocha, int usada);
void iniciaRocha(Rocha* rocha, float valorRocha, float pesoRocha, int usada);
void imprimeRocha(Rocha rocha);

#endif