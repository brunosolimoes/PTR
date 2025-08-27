#include <stdlib.h>
#include "integral.h"

Integral* inicializa_integral(FunctionPointer funcao, double limite_inferior, double limite_superior, int num_particoes) {
    Integral* integral = (Integral*)malloc(sizeof(Integral));
    if (integral) {
        integral->funcao = funcao;
        integral->limite_inferior = limite_inferior;
        integral->limite_superior = limite_superior;
        integral->num_particoes = num_particoes;
    }
    return integral;
}

// Calcula a integral pelo método do trapézio
double computa_integral(Integral* integral) {
    double largura = (integral->limite_superior - integral->limite_inferior) / integral->num_particoes;
    double soma_total = 0.0;
    double x_inicial, x_final, altura;

    for (int i = 0; i < integral->num_particoes; i++) {
        x_inicial = integral->limite_inferior + i * largura;
        x_final = x_inicial + largura;
        altura = 0.5 * (integral->funcao(x_inicial) + integral->funcao(x_final));
        soma_total += altura * largura;
    }

    return soma_total;
}

// Libera a memória associada à integral
void libera_integral(Integral* integral) {
    if (integral) {
        free(integral);
    }
}