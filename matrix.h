/*
  Autor: Bruno de Moura Solimões - 22051316
  dataInicio:28/03/2025
  dataFim:
*/

define typedef matrix Matrix;

//Criar matriz
Matrix createMatrix(int ordem);

//Deletar matriz
bool deletMatrix(Matrix *mat);

//obter a ordem da matriz
int ordenMatrix(Matrix *mat)

//Obter o determinante da matriz
double detMatrix(Matrix *mat);

//Cria uma segunda matriz que é o inverso da recebida
Matrix invertMatrix(Matrix *mat);

//Cria uma segunda matriz que é a transposta da recebida
Matrix transportMatrix(Matrix *mat);

//Preencher a matriz por inteira com os primeiro valores recebidos de um vetor, preenche linha por linha 
void fillMatrix(Matrix *mat, double *values)
