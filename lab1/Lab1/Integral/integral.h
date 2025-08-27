#ifndef INTEGRAL_H
#define INTEGRAL_H

typedef double (*func_ptr)(double x);

double soma_riemann(func_ptr f, double inicio, double fim, int subdivisoes);
double regra_trapezio(func_ptr f, double inicio, double fim, int subdivisoes);
double regra_simpson(func_ptr f, double inicio, double fim, int subdivisoes);
double regra_quadratura(func_ptr f, double inicio, double fim, int subdivisoes);
double regra_gauss_legendre(func_ptr f, double inicio, double fim, int subdivisoes);

#endif // INTEGRAL_H
