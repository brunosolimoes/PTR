#include <stdio.h>
#include <stdlib.h>
#include "impressao.h"

// Função que imprime todos os elementos da lista
void imprimir_vetor(const Vetor *lista) {
    if (!lista) {
        printf("Lista vazia!!!");
        return;
    }

    printf("[");
    const Vetor *atual = lista;
    while (atual) {
        printf("%.4f", atual->dado);
        if (atual->prox) {
            printf(" ");
        }
        atual = atual->prox;
    }
    printf("]");
}

// Função que adiciona um novo nodo à lista
Vetor* adicionar_nodo(Vetor *lista, double dado) {
    Vetor* novo_nodo = (Vetor*)malloc(sizeof(Vetor));
    if (!novo_nodo) {
        return lista; // Retorna a lista original se a alocação falhar
    }
    novo_nodo->dado = dado;
    novo_nodo->prox = NULL;

    if (!lista) {
        return novo_nodo; // Se a lista estiver vazia, retorna o novo nodo
    }

    Vetor* ultimo_nodo = lista;
    while (ultimo_nodo->prox) {
        ultimo_nodo = ultimo_nodo->prox;
    }
    ultimo_nodo->prox = novo_nodo; // Adiciona o novo nodo ao final da lista
    return lista;
}

void liberar_lista(Vetor *lista) {
    Vetor *atual = lista;
    while (atual) {
        Vetor *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
}
