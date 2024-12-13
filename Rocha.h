#ifndef ROCHA_H
#define ROCHAL_H

typedef struct
{
    int peso;
    int valor;
} ROcha;

void InicializaRocha(ROcha *r, int peso, int valor);
int getpeso(ROcha *r);
int getvalor(ROcha *r);

void setpeso(ROcha *r, int peso);
void setvalor(ROcha *r, int valor);

#endif