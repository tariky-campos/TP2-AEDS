#ifndef ROCHA_H
#define ROCHAL_H

typedef struct
{
    int peso;
    int valor;
} rocha;

void InicializaRocha(rocha *r, int peso, int valor);
int getpeso(rocha *r);
int getvalor(rocha *r);

void setpeso(rocha *r, int peso);
void setvalor(rocha *r, int valor);

#endif

