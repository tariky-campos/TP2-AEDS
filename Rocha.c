#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include  "rocha.h"

void InicializaRocha(ROcha *r, int peso, int valor){
    setpeso(r, peso);
    setvalor(r, valor);
}
void setpeso(ROcha *r, int peso){
    r->peso = peso;
}
void setvalor(ROcha *r, int valor){
    r->valor = valor;
}

int getpeso(ROcha *r){
    return r->peso;
}
int getvalor(ROcha *r){
    return r->valor;
}