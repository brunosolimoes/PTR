#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "matrix.h"

// Cria uma nova matriz com linhas e colunas especificadas
Matrix* initialize_matrix(int rows, int cols) {
    Matrix* m = (Matrix*)malloc(sizeof(Matrix));
    m->rows = rows;
    m->cols = cols;
    m->data = (double**)malloc(rows * sizeof(double*));
    
    for (int i = 0; i < rows; i++) {
        m->data[i] = (double*)malloc(cols * sizeof(double));
    }
    
    return m;
}

// Libera a memória da matriz
void destroy_matrix(Matrix* matrix) {
    if (matrix) {
        for (int i = 0; i < matrix->rows; i++) {
            free(matrix->data[i]);
        }
        free(matrix->data);
        free(matrix);
    }
}

// Soma duas matrizes
Matrix* sum_matrices(Matrix* a, Matrix* b) {
    Matrix* result = initialize_matrix(a->rows, a->cols);
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            result->data[i][j] = a->data[i][j] + b->data[i][j];
        }
    }
    return result;
}

// Subtrai a matriz b da matriz a
Matrix* subtract_matrices(Matrix* a, Matrix* b) {
    Matrix* result = initialize_matrix(a->rows, a->cols);
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            result->data[i][j] = a->data[i][j] - b->data[i][j];
        }
    }
    return result;
}

// Multiplica duas matrizes
Matrix* multiply_matrices(Matrix* a, Matrix* b) {
    Matrix* result = initialize_matrix(a->rows, b->cols);
    
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            double sum = 0.0; // Inicializa a soma para cada elemento da matriz resultante
            for (int k = 0; k < a->cols; k++) {
                sum += a->data[i][k] * b->data[k][j];
            }
            result->data[i][j] = sum; // Atribui a soma ao elemento da matriz resultante
        }
    }
    
    return result;
}

// Multiplica a matriz por um escalar
Matrix* scale_matrix(Matrix* m, double scalar) {
    Matrix* result = initialize_matrix(m->rows, m->cols);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            result->data[i][j] = m->data[i][j] * scalar;
        }
    }
    return result;
}

// Transpõe a matriz
Matrix* transpose_matrix(Matrix* m) {
    Matrix* result = initialize_matrix(m->cols, m->rows);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            result->data[j][i] = m->data[i][j]; // Troca linhas por colunas
        }
    }
    return result;
}

// Calcula o determinante da matriz
double calculate_determinant(Matrix* m) {
    if (m->rows != m->cols) {
        return NAN; // Matriz não quadrada
    }
    if (m->rows == 1) {
        return m->data[0][0];
    }
    
    double det = 0.0;
    for (int j = 0; j < m->cols; j++) {
        // Cria uma submatriz removendo a primeira linha e a j-ésima coluna
        Matrix* submatrix = initialize_matrix(m->rows - 1, m->cols - 1);
        
        for (int row = 1; row < m->rows; row++) {
            for (int col = 0; col < m->cols; col++) {
                if (col < j) {
                    submatrix->data[row - 1][col] = m->data[row][col];
                } else if (col > j) {
                    submatrix->data[row - 1][col - 1] = m->data[row][col];
                }
            }
        }
        
        // Acumula o determinante usando a regra de Laplace
        det += (j % 2 == 0 ? 1 : -1) * m->data[0][j] * calculate_determinant(submatrix);
        destroy_matrix(submatrix);
    }
    return det;
}

// Calcula a matriz dos cofatores
Matrix* get_cofactor_matrix(Matrix* m) {
    Matrix* cof = initialize_matrix(m->rows, m->cols);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            Matrix* submatrix = initialize_matrix(m->rows - 1, m->cols - 1);
            for (int ii = 0; ii < m->rows; ii++) {
                for (int jj = 0; jj < m->cols; jj++) {
                    if (ii != i && jj != j) {
                        int dest_i = ii < i ? ii : ii - 1;
                        int dest_j = jj < j ? jj : jj - 1;
                        submatrix->data[dest_i][dest_j] = m->data[ii][jj];
                    }
                }
            }
            cof->data[i][j] = pow(-1, i + j) * calculate_determinant(submatrix);
            destroy_matrix(submatrix);
        }
    }
    return cof;
}

// Inverte a matriz
Matrix* invert_matrix(Matrix* m) {
    double det = calculate_determinant(m);
    if (det == 0) {
        return NULL; // Matriz não invertível
    }
    
    Matrix* cof = get_cofactor_matrix(m);
    Matrix* adj = transpose_matrix(cof);
    destroy_matrix(cof);
    
    Matrix* inv = scale_matrix(adj, 1.0 / det);
    destroy_matrix(adj);
    return inv;
}

// Imprime a matriz
void display_matrix(Matrix *m) {
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            printf("%f ", m->data[i][j]);
        }
        printf("\n");
    }
}
