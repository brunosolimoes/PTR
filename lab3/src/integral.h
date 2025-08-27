#ifndef INTEGRAL_H
#define INTEGRAL_H

// Ponteiro para a função que será integrada
typedef double (*FunctionPointer)(double);

typedef struct Integral {
    FunctionPointer funcao;
    double limite_inferior;
    double limite_superior;
    int num_particoes;
} Integral;

// Funções para inicializar, computar e liberar a integral
Integral* inicializa_integral(FunctionPointer funcao, double limite_inferior, double limite_superior, int num_particoes);
double computa_integral(Integral* integral);
void libera_integral(Integral* integral);

#endif
