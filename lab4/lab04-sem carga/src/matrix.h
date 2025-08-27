// matrix.h
#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    int rows;
    int cols;
    double** data;
} Matrix;

Matrix* initialize_matrix(int rows, int cols);
void destroy_matrix(Matrix* matrix);
void display_matrix(Matrix* m);
Matrix* sum_matrices(Matrix* m1, Matrix* m2);
Matrix* subtract_matrices(Matrix* m1, Matrix* m2);
Matrix* multiply_matrices(Matrix* m1, Matrix* m2);
Matrix* scale_matrix(Matrix* m, double scalar);
Matrix* transpose_matrix(Matrix* m);
double calculate_determinant(Matrix* m);
Matrix* invert_matrix(Matrix* m);
Matrix* copy_matrix(Matrix* matriz1, int rows, int cols, float matriz2[][cols]);

#endif /* MATRIX_H */
