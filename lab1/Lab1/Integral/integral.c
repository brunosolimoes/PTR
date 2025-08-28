#include "integral.h"
#include <math.h>

//---------------------Regra de Gauss-Legendre de 2 pontos---------------------//
double gaussLegendreRule(function f, double start, double end) {
    double result = 0.0;
    double weights[2] = {1.0, 1.0};
    double node[2] = {-1 / sqrt(3), 1 / sqrt(3)};
    double sum = 0.0;

    for (int i = 0; i < 2; i++) {
        double x = 0.5 * ((end - start) * node[i] + end + start);
        sum += weights[i] * f(x);
    }

    result = 0.5 * (end - start) * sum;

    return result;
}
//-----------------------------------------------------------------------------//

//-----------------------------Regra de Quadratura-----------------------------//
double quadratureRule(function f, double start, double end, int subdivisions) {
    double result = 0.0;
    double width = (end - start) / subdivisions;
    double sum = 0.0;

    for (int i = 0; i < subdivisions; i++) {
        double x = start + width * (i + 0.5);
        sum += f(x);
    }

    result = width * sum;

    return result;
}
//-----------------------------------------------------------------------------//

//------------------------------Regra do Trapézio------------------------------//
double trapezeRule(function f, double start, double end, int subdivisions) {
    double result = 0.0;
    double width = (end - start) / subdivisions;
    double sum = 0.5 * (f(start) + f(end));

    for (int i = 1; i < subdivisions; i++) {
        double x = start + width * i;
        sum += f(x);
    }

    result = width * sum;

    return result;
}
//-----------------------------------------------------------------------------//

//------------------------------Regra de Simpson-------------------------------//
double simpsonRule(function f, double start, double end, int subdivisions) {
    double result = 0.0;
    double width = (end - start) / subdivisions;
    double sum = f(start) + f(end);

    for (int i = 1; i < subdivisions; i++) {
        double x = start + width * i;
        sum += (i % 2 == 0) ? 2 * f(x) : 4 * f(x);
    }

    result = (width / 3) * sum;

    return result;
}
//-----------------------------------------------------------------------------//

//-------------------------------Soma de Riemann-------------------------------//
double riemannSum(function f, double start, double end, int subdivisions) {
    double sum = 0.0;
    double result = 0.0;
    double width = (end - start) / subdivisions;
    
    for (int i = 0; i < subdivisions; i++) {    
        double x = start + width * i;
        sum += f(x);
    }

    result = width * sum;

    return result;
}
//-----------------------------------------------------------------------------//
