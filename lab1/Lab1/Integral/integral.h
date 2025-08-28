#ifndef INTEGRAL_H
#define INTEGRAL_H

typedef double (*function)(double x);

double gaussLegendreRule(function f, double start, double end);
double quadratureRule(function f, double start, double end, int subdivisions);
double trapezeRule(function f, double start, double end, int subdivisions);
double simpsonRule(function f, double start, double end, int subdivisions);
double riemannSum(function f, double start, double end, int subdivisions);

#endif // INTEGRAL_H
