#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

//--Cria uma nova matriz recebendo linhas e colunas como parametro---//
Matrix* newMatrix(int numRow, int numCol) {
    Matrix* mat = (Matrix*)malloc(sizeof(Matrix));
    if (!mat) return NULL;

    mat->numRow = numRow;
    mat->numCol = numCol;

    mat->data = (double**)malloc(numRow * sizeof(double*));

    if (!mat->data) {
        free(mat);
        return NULL;
    }

    for (int i = 0; i < numRow; i++) {
        mat->data[i] = (double*)calloc(numCol, sizeof(double));
        
        if (!mat->data[i]) {
        
            for (int j = 0; j < i; j++) free(mat->data[j]);

            free(mat->data);
            free(mat);
            return NULL;
        }
    }

    return mat;
}

//-------------------------------------------------------------------//

//--------------------------Imprime a matriz-------------------------//
void showMatrix(Matrix *mat) {
    
    printf("\n");

    for (int row = 0; row < mat->numRow; row++) {
        for (int col = 0; col < mat->numCol; col++) {

            printf("%f ", mat->data[row][col]);
        }

        printf("\n-----------------------------------------\n\n");
    }
}
//-------------------------------------------------------------------//

//--------------------------Deleta a matriz--------------------------//
void deletMatrix(Matrix* mat) {

    if (mat) {
        for (int row = 0; row < mat->numRow; row++) {

            free(mat->data[row]);
        }

        free(mat->data);
        free(mat);
    }
}
//-------------------------------------------------------------------//

//--Cria uma nova matriz resultado da soma da matrizA com a matrizB--//
Matrix* sumMatrixs(Matrix* matA, Matrix* matB) {
    Matrix* matSum = newMatrix(matA->numRow, matA->numCol);

    for (int row = 0; row < matA->numRow; row++) {
        for (int col = 0; col < matA->numCol; col++) {
            
            matSum->data[row][col] = matA->data[row][col] + matB->data[row][col];
        }
    }
    return matSum;
}
//-------------------------------------------------------------------//


//Cria uma nova matriz resultado da subtração da matrizA com a matrizB//
Matrix* subMatrixs(Matrix* matA, Matrix* matB) {
    Matrix* matSub = newMatrix(matA->numRow, matA->numCol);

    for (int row = 0; row < matA->numRow; row++) {
        for (int col = 0; col < matA->numCol; col++) {
            
            matSub->data[row][col] = matA->data[row][col] - matB->data[row][col];
        }
    }
    return matSub;
}
//-------------------------------------------------------------------//


//Cria uma nova matriz resultado do produto da matrizA com a matrizB-//
Matrix* multMatrixs(Matrix* matA, Matrix* matB) {
    Matrix* matProd = newMatrix(matA->numRow, matB->numCol);
    
    for (int row = 0; row < matA->numRow; row++) {
        for (int col = 0; col < matB->numCol; col++) {
            double sum = 0.0;
            
            for (int k = 0; k < matA->numCol; k++) {            
                sum += matA->data[row][k] * matB->data[k][col];
            }
            
            matProd->data[row][col] = sum;
        }
    }
    
    return matProd;
}
//-------------------------------------------------------------------//


//-----------------Multiplica a matriz por um escalar----------------//
Matrix* multMatrixScale(Matrix* mat, double num) {
    Matrix* newMat = newMatrix(mat->numRow, mat->numCol);
    
    for (int row = 0; row < mat->numRow; row++) {
        for (int col = 0; col < mat->numCol; col++) {
            
            newMat->data[row][col] = mat->data[row][col] * num;
        }
    }
    return newMat;
}
//-------------------------------------------------------------------//


//-------------------------Transpõe a matriz-------------------------//
Matrix* transpMatrix(Matrix* mat) {
    Matrix* matTransp = newMatrix(mat->numCol, mat->numRow);
    
    for (int row = 0; row < mat->numRow; row++) {
        for (int col = 0; col < mat->numCol; col++) {
    
            matTransp->data[col][row] = mat->data[row][col];
        }
    }
    return matTransp;
}
//-------------------------------------------------------------------//


//------------------Calcula o determinante da matriz-----------------//
double detMatrix(Matrix* mat) {
    
    if (mat->numRow != mat->numCol) {
        return NAN;
    }
    
    if (mat->numRow == 1) {
        return mat->data[0][0];
    }
    
    double det = 0.0;
    
    for (int colJ = 0; colJ < mat->numCol; colJ++) {
       
        Matrix* submatrix = newMatrix(mat->numRow - 1, mat->numCol - 1);
        
        for (int row = 1; row < mat->numRow; row++) {
            for (int col = 0; col < mat->numCol; col++) {
                if (col < colJ) {
    
                    submatrix->data[row - 1][col] = mat->data[row][col];
    
                } else if (col > colJ) {
                    
                    submatrix->data[row - 1][col - 1] = mat->data[row][col];
                }
            }
        }
        

        det += (colJ % 2 == 0 ? 1 : -1) * mat->data[0][colJ] * detMatrix(submatrix);
        deletMatrix(submatrix);

    }
    return det;
}
//-------------------------------------------------------------------//


//-------------------Calcula a matriz dos cofatores------------------//
Matrix* coFactorMatrix(Matrix* mat) {
    Matrix* cof = newMatrix(mat->numRow, mat->numCol);

    for (int row = 0; row < mat->numRow; row++) {
        for (int col = 0; col < mat->numCol; col++) {
            Matrix* submatrix = newMatrix(mat->numRow - 1, mat->numCol - 1);

            for (int rowI = 0; rowI < mat->numRow; rowI++) {
                for (int colJ = 0; colJ < mat->numCol; colJ++) {
                    if (rowI != row && colJ != col) {

                        int dest_i = rowI < row ? rowI : rowI - 1;
                        int dest_j = colJ < col ? colJ : colJ - 1;
                        submatrix->data[dest_i][dest_j] = mat->data[rowI][colJ];

                    }
                }
            }

            cof->data[row][col] = pow(-1, row + col) * detMatrix(submatrix);
            deletMatrix(submatrix);

        }
    }

    return cof;
}
//-------------------------------------------------------------------//


//-------------------------Inverte a matriz-------------------------//
Matrix* invMatrix(Matrix* mat) {
    double det = detMatrix(mat);

    if (det == 0) {
        return NULL; 
    }
    
    Matrix* cof = coFactorMatrix(mat);
    Matrix* adj = transpMatrix(cof);
    Matrix* inv = multMatrixScale(adj, 1.0 / det);
    
    deletMatrix(cof);
    deletMatrix(adj);
    
    return inv;
}
//-------------------------------------------------------------------//
