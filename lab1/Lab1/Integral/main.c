/*
laboratorio 01 -> Integral
Bruno de Moura Solimões - 22051316
*/

#include <stdio.h>
#include <math.h>
#include "integral.h"


//----------------Nova função para teste, seno de x: f(x) = sin(x)----------------//
double f(double x) {
  return sin(x);
}
//--------------------------------------------------------------------------------//

//-----------------Testando a Regra de Gauss-Legendre de 2 pontos-----------------//
void gaussLegendreRuleTest() {

  // Pi/2 (integral de 0 a pi/2 de sin(x) dá 1)
  double start = 0;
  double end = 3.14159265359 / 2; 
  
  printf("Teste da Regra de Gauss-Legendre: %f", gaussLegendreRule(f, start, end));
  printf("\n-----------------------------------------\n\n");
}
//------------------------------------------------------------------------------//

//-------------------------Testando a regra de Quadratura-----------------------//
void quadratureRuleTest() {
  
  // Pi/2 (integral de 0 a pi/2 de sin(x) dá 1)
  double start = 0;
  double end = 3.14159265359 / 2; 
  int subdivisions = 1000;

  printf("Teste da Regra de Quadratura: %f", quadratureRule(f, start, end, subdivisions));
  printf("\n-----------------------------------------\n\n");
}
//------------------------------------------------------------------------------//

//---------------------------Testando a Regra do Trapézio-----------------------//
void trapezeRuleTest() {

  // Pi/2 (integral de 0 a pi/2 de sin(x) dá 1)
  double start = 0;
  double end = 3.14159265359 / 2; 
  int subdivisions = 1000;

  printf("Teste da Regra do Trapézio: %f", trapezeRule(f, start, end, subdivisions));
  printf("\n-----------------------------------------\n\n");
}
//------------------------------------------------------------------------------//

//-------------------------Testando a regra de Simpson--------------------------//
void simpsonRuleTest() {

  // Pi/2 (integral de 0 a pi/2 de sin(x) dá 1)
  double start = 0;
  double end = 3.14159265359 / 2; 
  int subdivisions = 1000;

  printf("Teste da Regra de Simpson: %f", simpsonRule(f, start, end, subdivisions));
  printf("\n-----------------------------------------\n\n");
}
//------------------------------------------------------------------------------//

//---------------------------Testando a soma de Riemann-------------------------//
void riemannSumTest() {

  // Pi (integral de 0 a pi de sin(x) dá 2)
  double start = 0;
  double end = 3.14159265359; 
  int subdivisions = 1000;

  printf("Teste da Soma de Riemann: %f", riemannSum(f, start, end, subdivisions));
  printf("\n-----------------------------------------\n\n");
}
//------------------------------------------------------------------------------//

int main() {

  gaussLegendreRuleTest();
  quadratureRuleTest();
  trapezeRuleTest();
  simpsonRuleTest();
  riemannSumTest();
  return 0;
}
