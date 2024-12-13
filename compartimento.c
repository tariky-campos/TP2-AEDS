#include "Compartimento.h" // Inclui o cabeçalho que define o tipo L_Compart e Rocha
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Inicializa uma lista de rochas, configurando o tamanho inicial como 0
void ini_LISTAC(L_Compart* lista) {
    lista->tamanho = 0;
}

// Insere uma nova rocha na lista
void insere_Rocha(L_Compart* lista, float valor, float peso, int usada) {
    if (lista->tamanho >= MAX) { // Verifica se a lista já atingiu o tamanho máximo
        printf("Tamanho Max da lista\n");
        return;
    }
    // Cria uma nova rocha com os valores fornecidos
    Rocha novaRocha = {valor, peso, usada};
    lista->vetor[lista->tamanho] = novaRocha; // Adiciona a nova rocha na lista
    lista->tamanho++; // Incrementa o tamanho da lista
    return;
}

// Remove uma rocha da lista, deslocando os elementos subsequentes
void remove_Rocha(L_Compart* lista, int indice) {
    if (indice < 0 || indice >= lista->tamanho) { // Valida o índice
        printf("Sem rocha\n");
        return;
    }
    // Move os elementos seguintes para "cobrir" o espaço do elemento removido
    for (int i = indice; i < lista->tamanho - 1; i++) {
        lista->vetor[i] = lista->vetor[i + 1];
    }
    lista->tamanho--; // Decrementa o tamanho da lista
    return;
}

// Imprime as rochas presentes na lista
void ImprimeCompartimento(L_Compart* lista) {
    if (lista->tamanho == 0) { // Verifica se a lista está vazia
        printf("Vazia\n");
        return;
    }
    printf("Lista de Rochas:\n");
    // Percorre a lista e imprime os dados de cada rocha
    for (int i = 0; i < lista->tamanho; i++) {
        printf("Rocha Indice:%d  Valor: %.0f  Peso: %.0f usada: %d\n", 
               i, 
               lista->vetor[i].valorRocha, 
               lista->vetor[i].pesoRocha, 
               lista->vetor[i].usada);
    }
}

// Avalia uma combinação específica de rochas, calculando valor e peso totais
void avaliaCombinacao(L_Compart* lista, int combinacao, float* valorTotal, float* pesoTotal) {
    *valorTotal = 0;
    *pesoTotal = 0;
    // Percorre todas as rochas da lista
    for (int i = 0; i < lista->tamanho; i++) {
        // Verifica se a rocha faz parte da combinação e não foi usada
        if (combinacao % (int)pow(2, i + 1) >= (int)pow(2, i) && lista->vetor[i].usada == 0) {
            *valorTotal += lista->vetor[i].valorRocha; // Soma o valor da rocha
            *pesoTotal += lista->vetor[i].pesoRocha;  // Soma o peso da rocha
        }
    }
}

// Determina a melhor combinação de rochas com base no valor total e peso máximo
void melhor_rocha(L_Compart* lista) {
    int melhorCombinacao = 0; // Armazena a melhor combinação encontrada
    float melhorValor = 0;   // Valor máximo da combinação
    float melhorPeso = 0;    // Peso correspondente à melhor combinação

    int totalCombinacoes = (int)pow(2, lista->tamanho); // Número total de combinações possíveis (2^n)

    for (int combinacao = 0; combinacao < totalCombinacoes; combinacao++) {
        float valorAtual, pesoAtual;
        // Avalia a combinação atual
        avaliaCombinacao(lista, combinacao, &valorAtual, &pesoAtual);

        // Verifica se a combinação atende aos critérios: peso <= 40 e valor é o maior encontrado
        if (pesoAtual <= 40 && valorAtual > melhorValor) {
            melhorValor = valorAtual;
            melhorCombinacao = combinacao;
            melhorPeso = pesoAtual;
        }
    }

    // Marca as rochas da melhor combinação como usadas
    marcaRochasUsadas(lista, melhorCombinacao);

    // Imprime o resultado final
    printf("Valor: %.0f, Peso: %.0f", melhorValor, melhorPeso);
    printf(" Solucao: ");
    printf("(");
    // Identifica as rochas que fazem parte da solução
    for (int i = 0; i < lista->tamanho; i++) {
        if ((melhorCombinacao / (int)pow(2, i)) % 2 == 1) { 
            printf(" %d ", i);
        }
    }
    printf(")");
}

// Marca as rochas da combinação como usadas (campo 'usada' = 1)
void marcaRochasUsadas(L_Compart* lista, int combinacao) {
    for (int i = 0; i < lista->tamanho; i++) {
        // Se a rocha faz parte da combinação, marca como usada
        if (combinacao % (int)pow(2, i + 1) >= (int)pow(2, i)) {
            lista->vetor[i].usada = 1;
        }
    }
}
