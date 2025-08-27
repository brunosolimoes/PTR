#include "integral.h"
#include <math.h>

// Soma de Riemann
double soma_riemann(func_ptr f, double inicio, double fim, int subdivisoes) {
    double largura = (fim - inicio) / subdivisoes;
    double soma = 0.0;

    for (int i = 0; i < subdivisoes; i++) {
        double x = inicio + largura * i;
        soma += f(x);
    }

    return largura * soma;
}

// Regra do Trapézio
double regra_trapezio(func_ptr f, double inicio, double fim, int subdivisoes) {
    double largura = (fim - inicio) / subdivisoes;
    double soma = 0.5 * (f(inicio) + f(fim));

    for (int i = 1; i < subdivisoes; i++) {
        double x = inicio + largura * i;
        soma += f(x);
    }

    return largura * soma;
}

// Regra de Simpson
double regra_simpson(func_ptr f, double inicio, double fim, int subdivisoes) {
    double largura = (fim - inicio) / subdivisoes;
    double soma = f(inicio) + f(fim);

    for (int i = 1; i < subdivisoes; i++) {
        double x = inicio + largura * i;
        soma += (i % 2 == 0) ? 2 * f(x) : 4 * f(x);
    }

    return (largura / 3) * soma;
}

// Regra de Quadratura
double regra_quadratura(func_ptr f, double inicio, double fim, int subdivisoes) {
    double largura = (fim - inicio) / subdivisoes;
    double soma = 0.0;

    for (int i = 0; i < subdivisoes; i++) {
        double x = inicio + largura * (i + 0.5);
        soma += f(x);
    }

    return largura * soma;
}

// Regra de Gauss-Legendre
double regra_gauss_legendre(func_ptr f, double inicio, double fim, int subdivisoes) {
    double pesos[2] = {1.0, 1.0};
    double nos[2] = {-1 / sqrt(3), 1 / sqrt(3)};
    double soma = 0.0;

    for (int i = 0; i < 2; i++) {
        double x = 0.5 * ((fim - inicio) * nos[i] + fim + inicio);
        soma += pesos[i] * f(x);
    }

    return 0.5 * (fim - inicio) * soma;
}
