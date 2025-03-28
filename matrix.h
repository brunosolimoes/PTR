/*
  Autor: Bruno de Moura Solimões - 22051316
  dataInicio:28/03/2025
  dataFim:
*/

typedef struct matrix Matrix;

//Criar matriz
Matrix createMatrix(int ordem);

//Deletar matriz
bool deletMatrix(Matrix *mat);

//Obter o determinante da matriz
double detMatrix(Matrix *mat);

//Cria uma segunda matriz que é o inverso da recebida
Matrix invertMatrix(Matrix *mat);

//Cria uma segunda matriz que é a transposta da recebida
Matrix transportMatrix(Matrix *mat);

//Preencher a matriz por inteira com os n => (ordem X ordem) primeiros valores recebidos de um vetor, preenche linha por linha 
bool fillMatrix(Matrix *mat, double *values);

//trocar o valor de uma posição especifica na matriz
void changeEspecValueMatrix(Matrix *mat, int lin, int col, double value);
