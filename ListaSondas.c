#include <stdio.h>
#include <stdlib.h>
#include "ListaSondas.h"

void iniciaListaSonda(L_Sondas* pLista){ // com cabeça inicia com celula chave.
    pLista->pprimeira = (Apontador_S) malloc(sizeof(Celula_S));
    pLista->pultima = pLista->pprimeira;
    pLista->pprimeira->pProxx = NULL;
}
void insereSonda(L_Sondas* pLista, DadosSonda xSonda){
    pLista->pultima->pProxx = (Apontador_S) malloc(sizeof(Celula_S));
    pLista->pultima = pLista->pultima->pProxx;
    pLista->pultima->chave = xSonda;
    pLista->pultima->pProxx = NULL;

}
void retiraSonda(L_Sondas* plista){
    int idRetira;
    Celula_S* atual = plista->pprimeira;
    Celula_S* anterior = NULL;

    printf("Digite o ID da sonda para ser retirada: ");
    scanf("%d", &idRetira);

    while (atual != NULL && atual->chave.identificadorSonda != idRetira)
    {
        anterior = atual;
        atual = atual->pProxx;
    }
     if (atual == NULL) { //Olha se a sonda existe mesmo, se não, retorna uma mensagem
        printf("Sonda não existe com esse ID: %d\n", idRetira);
        return;// encerra codigo
    } 
    if(anterior == NULL){
        plista->pprimeira = atual->pProxx; //remove primeira
    } else {
        anterior->pProxx = atual->pProxx; // remove meio ou fim
    }
    free(atual);
    printf("Sonda Removida :)\n");
}

void ImprimeListaSondas(L_Sondas* plista){

    Celula_S* atual = plista->pprimeira->pProxx;

    while(atual != NULL){

        imprimeSonda(atual->chave);
        atual = atual->pProxx;
    }
}
