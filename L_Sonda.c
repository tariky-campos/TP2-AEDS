#include <stdio.h>
#include <stdlib.h>
#include "L_Sonda.h"

void ini_LISTASONDA(L_Sondas* pLista){ // com cabeça inicia com celula chave.
    pLista->pprimeiro = (apontador) malloc(sizeof(celulaSonda));
    pLista->pultimo = pLista->pprimeiro;
    pLista->pprimeiro->pProxSonda = NULL;
}
void insereSonda(L_Sondas* pLista, DadosSonda xSonda){
    pLista->pultimo->pProxSonda = (apontador) malloc(sizeof(celulaSonda));
    pLista->pultimo = pLista->pultimo->pProxSonda;
    pLista->pultimo->chaveSonda = xSonda;
    pLista->pultimo->pProxSonda = NULL;

}
void retiraSonda(L_Sondas* plista){
    int idRetira;
    celulaSonda* atual = plista->pprimeiro;
    celulaSonda* anterior = NULL;

    printf("Digite o ID da sonda para ser retirada: ");
    scanf("%d", &idRetira);

    while (atual != NULL && atual->chaveSonda.identificadorSonda != idRetira)
    {
        anterior = atual;
        atual = atual->pProxSonda;
    }
     if (atual == NULL) { //Olha se a sonda existe mesmo, se não, retorna uma mensagem
        printf("Sonda não existe com esse ID: %d\n", idRetira);
        return;// encerra codigo
    } 
    if(anterior == NULL){
        plista->pprimeiro = atual->pProxSonda; //remove primeira
    } else {
        anterior->pProxSonda = atual->pProxSonda; // remove meio ou fim
    }
    free(atual);
    printf("Sonda Removida :)\n");
}

void ImprimeListaSondas(L_Sondas* plista){

    celulaSonda* atual = plista->pprimeiro->pProxSonda;

    while(atual != NULL){

        imprimeSonda(atual->chaveSonda);
        atual = atual->pProxSonda;
    }
}
