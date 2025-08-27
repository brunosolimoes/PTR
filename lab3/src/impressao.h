#ifndef IMPRESSAO_H
#define IMPRESSAO_H

typedef struct vetor {
    double dado;
    struct vetor *prox;
} Vetor;

void imprimir_vetor(const Vetor *lista);
Vetor* adicionar_nodo(Vetor *lista, double valor);
void liberar_lista(Vetor *lista);

#endif
