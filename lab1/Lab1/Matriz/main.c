/*
Aluno: Matheus Carvalho Reges
Matrícula: 22152027

Trabalho: lab1 - PTR - matrix
*/

// main.c

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "matrix.h"

//================== Funções de teste para as funções criadas em matrix.c =======================
void test_sum_matrices(Matrix* m1, Matrix* m2) {
  Matrix* sum = sum_matrices(m1, m2);
  if (sum == NULL) {
    printf("Erro ao criar a matriz de soma.\n");
    return;
  }
  printf("Soma das matrizes:\n\n");
  display_matrix(sum); 
  destroy_matrix(sum);
}

void test_subtract_matrices(Matrix* m1, Matrix* m2) {
  Matrix* diff = subtract_matrices(m1, m2);
  if (diff == NULL) {
    printf("Erro ao criar a matriz de diferença.\n");
    return;
  }
  printf("Diferença das matrizes:\n\n");
  display_matrix(diff); 
  destroy_matrix(diff);
}

void test_multiply_matrices(Matrix* m1, Matrix* m2) {
  Matrix* prod = multiply_matrices(m1, m2);
  if (prod == NULL) {
    printf("Erro ao criar a matriz de produto.\n");
    return;
  }
  printf("Produto das matrizes:\n\n");
  display_matrix(prod); 
  destroy_matrix(prod);
}

double test_calculate_determinant(Matrix* m) {
  double det = calculate_determinant(m);
  if (isnan(det) || isinf(det)) {
    printf("Cálculo do determinante falhou.\n");
  } else {
    printf("Determinante da matriz: %f\n", det);
  }
  return det;
}

Matrix* test_invert_matrix(Matrix* m) {
  Matrix* inv = invert_matrix(m);
  if (inv == NULL) {
    printf("A matriz não é invertível.\n");
  } else {
    printf("Inversa da matriz:\n\n");
    display_matrix(inv); 
  }
  return inv;
}

//================== Função main onde são testadas as funções acima =======================
int main() {
  // Criando uma matriz 3x3
  Matrix* m1 = initialize_matrix(3, 3);
  m1->data[0][0] = 1;
  m1->data[0][1] = 2;
  m1->data[0][2] = 3;
  m1->data[1][0] = 0;
  m1->data[1][1] = 1;
  m1->data[1][2] = 4;
  m1->data[2][0] = 5;
  m1->data[2][1] = 6;
  m1->data[2][2] = 0;

  // Criando outra matriz 3x3
  Matrix* m2 = initialize_matrix(3, 3);
  m2->data[0][0] = 7;
  m2->data[0][1] = 8;
  m2->data[0][2] = 9;
  m2->data[1][0] = 1;
  m2->data[1][1] = 0;
  m2->data[1][2] = 1;
  m2->data[2][0] = 2;
  m2->data[2][1] = 3;
  m2->data[2][2] = 4;

  // Aplicando as funções de teste para as operações entre as matrizes m1 e m2
  test_sum_matrices(m1, m2);
  printf("\n-------------------\n");
  test_subtract_matrices(m1, m2);
  printf("\n-------------------\n");
  test_multiply_matrices(m1, m2);
  printf("\n-------------------\n");
  test_calculate_determinant(m1);
  printf("\n-------------------\n");
  Matrix* inv = test_invert_matrix(m1);
  if (inv) {
    destroy_matrix(inv);
  }

  // Liberando memória
  destroy_matrix(m1);
  destroy_matrix(m2);

  return 0;
}
