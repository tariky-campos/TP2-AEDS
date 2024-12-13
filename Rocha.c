#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include  "Rocha.h"

void InicializaRocha(rocha *r,int id, int peso, int valor){
    setid(r, id);
    setpeso(r, peso);
    setvalor(r, valor);
}
void setid(rocha *r, int id){
    r->id = id;
}
void setpeso(rocha *r, int peso){
    r->peso = peso;
}
void setvalor(rocha *r, int valor){
    r->valor = valor;
}

int getid(rocha *r){
    return r->id;
}
int getpeso(rocha *r){
    return r->peso;
}
int getvalor(rocha *r){
    return r->valor;
}
