#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "L_Sonda.h"
#include <time.h>

#define PESMAXIMO 40
int mMVG = 1;

int main(){

    clock_t inicio = clock();
    DadosSonda sondaaa;
    L_Sondas sondasL;
    L_Compart comp;
    int N_Sondas = 3;
    
    ini_LISTAC(&comp);
    ini_LISTASONDA(&sondasL);

    for(int i = 0;i < N_Sondas;i++){
        insereSonda(&sondasL, inicil_sonda(&sondaaa));
    }

    FILE *arq = NULL;
    arq = fopen("tst.txt", "r");
    if(arq == NULL){
        printf("ERRO!!!!");
        exit(0);
    }
    int nRochas; 
    float peso, valor;
    fscanf(arq, "%d", &nRochas);

    for(int i = 0; i<nRochas;i++){
        fscanf(arq,"%f %f", &peso, &valor);
        insere_Rocha(&comp, valor, peso, 0);
    }

    for(int i = 1; i < (N_Sondas+1); i++){
        printf("Sonda %d: ", i);
        melhor_rocha(&comp);
        printf("\n");
    }


    clock_t fim = clock();
    double tempo_decorrido = (double)(fim - inicio) / 1000000;
    printf("Tempo gasto: %.4f segundos\n", tempo_decorrido);
    printf("\n"); 


    return 0;
}