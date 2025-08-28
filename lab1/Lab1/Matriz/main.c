/*
laboratorio 01 -> Matriz
Bruno de Moura Solimões - 22051316
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

//----------Função de teste da função de soma de matrizes-----------//
void sumMatrixsTest(Matrix* m1, Matrix* m2) {
  Matrix* sum = sumMatrixs(m1, m2);
  if (sum == NULL) {
    printf("ERRO:\n - Erro ao criar a matriz resultado da soma.\n\n");
    return;
  }
  printf("----------Matriz soma das matrizes----------");
  showMatrix(sum); 
  deletMatrix(sum);
}
//--------------------------------------------------------------------------------//

//----------Função de teste da função de subtrair de matrizes-----------//
void subMatrixsTest(Matrix* m1, Matrix* m2) {
  Matrix* dif = subMatrixs(m1, m2);
  if (dif == NULL) {
    printf("ERRO:\n - Erro ao criar a matriz resultado da diferenca.\n");
    return;
  }
  printf("----------Matriz diferença das matrizes:----------");
  showMatrix(dif);
  deletMatrix(dif);
}
//--------------------------------------------------------------------------------//

//----------Função de teste da função de multiplação entre matrizes-----------//
void multMatrixsTest(Matrix* m1, Matrix* m2) {
  Matrix* prod = multMatrixs(m1, m2);
  if (prod == NULL) {
    printf("ERRO:\n - Erro ao criar a matriz resultado do produto matricial.\n");
    return;
  }
  printf("----------Produto das matrizes:----------");
  showMatrix(prod); 
  deletMatrix(prod);
}
//--------------------------------------------------------------------------------//


//--------Função de teste da função de multiplação entre matriz e escalar---------//
void multMatrixScaleTest(Matrix* m1, double num) {
  Matrix* prod = multMatrixScale(m1, num);
  if (prod == NULL) {
    printf("ERRO:\n - Erro ao criar a matriz resultado do produto escalar.\n");
    return;
  }
  printf("----------Produto da matriz pelo escalar:----------");
  showMatrix(prod); 
  deletMatrix(prod);
}
//--------------------------------------------------------------------------------//

//--------Função de teste da função que retorna o determinante da matriz----------//
double detMatrixTest(Matrix* mat) {
  double det = detMatrix(mat);
  printf("----------Calculo do determiante da matriz:----------");
  showMatrix(mat);
  printf("Determinante: ");
  if (isnan(det) || isinf(det)) {
    printf("ERRO: - Erro ao calcular determinante da matriz.");
    printf("\n-----------------------------------------\n\n");
  } else {
    printf("%f\n", det);
    printf("\n-----------------------------------------\n\n");
  } 

  return det;
}
//--------------------------------------------------------------------------------//

//------------------Função de teste da função que inverte a matriz----------------//
Matrix* invMatrixTest(Matrix* m) {
  Matrix* inv = invMatrix(m);
  if (inv == NULL) {
    printf("ERRO:\n - Erro ao inverter a matriz.\n");
  } else {
    printf("----------Matriz inversa da matriz recebida:----------");
    showMatrix(inv);
  }
  return inv;
}
//--------------------------------------------------------------------------------//


int main() {
  
  Matrix* m1 = newMatrix(3, 3);
  m1->data[0][0] = 1;
  m1->data[0][1] = 2;
  m1->data[0][2] = 3;
  m1->data[1][0] = 0;
  m1->data[1][1] = 1;
  m1->data[1][2] = 4;
  m1->data[2][0] = 5;
  m1->data[2][1] = 6;
  m1->data[2][2] = 0;
  
  Matrix* m2 = newMatrix(3, 3);
  m2->data[0][0] = 7;
  m2->data[0][1] = 8;
  m2->data[0][2] = 9;
  m2->data[1][0] = 1;
  m2->data[1][1] = 0;
  m2->data[1][2] = 1;
  m2->data[2][0] = 2;
  m2->data[2][1] = 3;
  m2->data[2][2] = 4;

  Matrix* m3 = newMatrix(3, 3);
  m2->data[0][0] = 3;
  m2->data[0][1] = 1;
  m2->data[0][2] = 9;
  m2->data[1][0] = 0;
  m2->data[1][1] = 5;
  m2->data[1][2] = 6;
  m2->data[2][0] = 2;
  m2->data[2][1] = 2;
  m2->data[2][2] = 8;

  Matrix* m4 = newMatrix(3, 3);
  m2->data[0][0] = 7;
  m2->data[0][1] = 5;
  m2->data[0][2] = 2;
  m2->data[1][0] = 2;
  m2->data[1][1] = 9;
  m2->data[1][2] = 3;
  m2->data[2][0] = 5;
  m2->data[2][1] = 3;
  m2->data[2][2] = 1;

  sumMatrixsTest(m1, m2);
  subMatrixsTest(m4, m2);
  multMatrixsTest(m2, m3);
  multMatrixScaleTest(m3, 7);
  detMatrixTest(m1);
  
  Matrix* invM1 = test_invert_matrix(m1);
  if (invM1) {
    deletMatrix(invM1);
  }

  Matrix* invM1 = test_invert_matrix(m1);
  if (invM1) {
    deletMatrix(invM1);
  }

  deletMatrix(m1);
  deletMatrix(m2);
  deletMatrix(m3);
  deletMatrix(m4);
  
  return 0;
}
