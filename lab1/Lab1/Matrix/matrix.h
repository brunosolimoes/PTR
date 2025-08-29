// matrix.h
#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    int numRow;
    int numCol;
    double** data;
} Matrix;

Matrix* newMatrix(int numRow, int nmumCol);
void showMatrix(Matrix* mat);
void deletMatrix(Matrix* mat);
Matrix* sumMatrixs(Matrix* matA, Matrix* matB);
Matrix* subMatrixs(Matrix* matA, Matrix* matB);
Matrix* multMatrixs(Matrix* matA, Matrix* matB);
Matrix* multMatrixScale(Matrix* mat, double num);
Matrix* transpMatrix(Matrix* mat);
double detMatrix(Matrix* mat);
Matrix* coFactorMatrix(Matrix* mat);
Matrix* invMatrix(Matrix* mat);

#endif /* MATRIX_H */
