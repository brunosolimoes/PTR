/*
Aluno: Matheus Carvalho Reges
Matrícula: 22152027

Trabalho: lab1 - PTR - integral
*/

// main.c

#include <stdio.h>
#include "integral.h"
#include <math.h>

// Nova função para teste: f(x) = sin(x)
double f(double x) {
  return sin(x); // Função seno
}

void teste_soma_riemann() {
  double inicio = 0;
  double fim = 3.14159265359; // Pi (integral de 0 a pi de sin(x) dá 2)
  int subdivisoes = 1000;

  printf("Teste da Soma de Riemann: %f\n\n", soma_riemann(f, inicio, fim, subdivisoes));
}

void teste_regra_trapezio() {
  double inicio = 0;
  double fim = 3.14159265359 / 2; // Pi/2 (integral de 0 a pi/2 de sin(x) dá 1)
  int subdivisoes = 1000;

  printf("Teste da Regra do Trapézio: %f\n\n", regra_trapezio(f, inicio, fim, subdivisoes));
}

void teste_regra_simpson() {
  double inicio = 0;
  double fim = 3.14159265359 / 2; // Pi/2 (integral de 0 a pi/2 de sin(x) dá 1)
  int subdivisoes = 1000;

  printf("Teste da Regra de Simpson: %f\n\n", regra_simpson(f, inicio, fim, subdivisoes));
}

void teste_regra_quadratura() {
  double inicio = 0;
  double fim = 3.14159265359 / 2; // Pi/2 (integral de 0 a pi/2 de sin(x) dá 1)
  int subdivisoes = 1000;

  printf("Teste da Regra de Quadratura: %f\n\n", regra_quadratura(f, inicio, fim, subdivisoes));
}

void teste_regra_gauss_legendre() {
  double inicio = 0;
  double fim = 3.14159265359 / 2; // Pi/2 (integral de 0 a pi/2 de sin(x) dá 1)
  int subdivisoes = 2; // O método de Gauss-Legendre de 2 pontos não depende de subdivisões

  printf("Teste da Regra de Gauss-Legendre: %f\n\n", regra_gauss_legendre(f, inicio, fim, subdivisoes));
}

int main() {
  teste_soma_riemann();
  teste_regra_trapezio();
  teste_regra_simpson();
  teste_regra_quadratura();
  teste_regra_gauss_legendre();

  return 0;
}
