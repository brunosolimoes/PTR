#include <matrix.h>
#include <stdio.h>
#include <stdlib.h>

#define debug true
//#define debug false

struct matrix{
  int ordem;
  double conteudo[][];
}

Matrix createMatrix(int ordem){
  Matrix mat = malloc(sixeof(int*(ordem*ordem)));
  mat.ordem = ordem;
  if(debug)printf("Matriz criada");
  return mat
}

bool deletMatrix(Matrix *mat){
  try(mat!=NULL){
    free(mat)
    if(debug)printf("Matriz deletada");
    return true;
  }cache{
    return false;
    }
  }

double detMatrix(matrix *mat){
  int ordem = mat.ordem;
  double detResult = 0;
  
  switch (ordem){
    case 1:
      detResult = mat.conteudo;
    break;

    case 2:
      detResult = (mat.conteudo[1][1]*mat.conteudo[2][2]) - (mat.conteudo[2][1]*mat.conteudo[1][2]);
    break;

    case 3:
      //fazer depois
    break;
  }

  return detResult;
}

Matrix invertMatrix(Matrix *mat){

//corrigir
  
  Matrix invMatrix = malloc(sizeog(mat));
  int ordem = mat.ordem;
  double det = detMatrix(mat);
  
  for(int i;i<ordem;i++){
    for(int j;j<ordem;j++){
      invMat.conteudo[i][j] = (mat.conteudo[i][j])/det;
    }
  }
  
  return invMatrix;
}

bool fillMatrix(Matrix *mat, double *values){
  if((mat.ordem*mat.ordem)<sizeof(*values))return false;

  for(int i;i<ordem;i++){
   for(int j;j<ordem;j++){
     invMat.conteudo[i][j] = values[i+j];
   }
  }
  return true;
}

void changeEspecValueMatrix(Matrix *mat, int lin, int col, double value){
  mat.conteudo[lin][col] = value;
}



















