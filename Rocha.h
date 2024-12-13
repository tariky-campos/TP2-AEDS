#ifndef ROCHA_H
#define ROCHAL_H

typedef struct
{
    int id;
    int peso;
    int valor;
} rocha;

void InicializaRocha(rocha *r,int id, int peso, int valor);
int getid(rocha *r);
int getpeso(rocha *r);
int getvalor(rocha *r);

void setid(rocha *r, int id);
void setpeso(rocha *r, int peso);
void setvalor(rocha *r, int valor);

#endif

