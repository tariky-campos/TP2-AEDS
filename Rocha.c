#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include  "Rocha.h"

void InicializaRocha(rocha *r, int peso, int valor){
    setpeso(r, peso);
    setvalor(r, valor);
}
void setpeso(rocha *r, int peso){
    r->peso = peso;
}
void setvalor(rocha *r, int valor){
    r->valor = valor;
}

int getpeso(rocha *r){
    return r->peso;
}
int getvalor(rocha *r){
    return r->valor;
}
