#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ListaSondas.h"
#include <time.h>

#define PESO_MAXIMO 40
int MVG = 1;

int main(){

    clock_t inicio = clock();
    DadosSonda sonda1;
    L_Sondas sondasL;
    L_Compart compartimentoL;
    int qntdSondas = 3;
    
    ini_L_C(&compartimentoL);
    iniciaListaSonda(&sondasL);

    for(int i = 0;i < qntdSondas;i++){
        insereSonda(&sondasL, inicializaSonda(&sonda1));
    }

    FILE *arq = NULL;
    arq = fopen("tst.txt", "r");
    if(arq == NULL){
        printf("falha leitura");
        exit(0);
    }
    int nRochas; 
    float peso, valor;
    fscanf(arq, "%d", &nRochas);

    for(int i = 0; i<nRochas;i++){
        fscanf(arq,"%f %f", &peso, &valor);
        insere_ROCHA(&compartimentoL, valor, peso, 0);
    }

    for(int i = 1; i < (qntdSondas+1); i++){
        printf("Sonda %d: ", i);
        melhor_rocha(&compartimentoL);
        printf("\n");
    }


    clock_t fim = clock();
    double tempo_decorrido = (double)(fim - inicio) / 1000000;
    printf("Tempo gasto: %f segundos\n", tempo_decorrido);
    printf("\n"); 

    
    return 0;
}