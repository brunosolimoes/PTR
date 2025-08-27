#include "estate.h"
#include "simulation_model.h"
#include "simulation.h"
#include "matrix.h"
#include <math.h>
#include <stdio.h> 

// Função para calcular o movimento do robô usando nova lógica
void computeRobotEstate(EstadoRobo *estate, double angVel, double deltaTime) {
  const double constLinearVel = 1.0; // Velocidade linear fixa

  // Atualiza posição usando componentes do movimento
  estate->posX += deltaTime * constLinearVel * cos(estate->orientacao); // Corrigido para 'orientation'
  estate->posY += deltaTime * constLinearVel * sin(estate->orientacao); // Corrigido para 'orientation'

  // Atualiza orientação do ângulo
  estate->orientacao += deltaTime * angVel; 
}

Matrix* criaMatrizTransformacao(double orient) {
    Matrix* matriz = initialize_matrix(2, 2);
    matriz->data[0][0] = cos(orient);
    matriz->data[0][1] = -RAIO * sin(orient);
    matriz->data[1][0] = sin(orient);
    matriz->data[1][1] = RAIO * cos(orient);
    return matriz;
}

// Função para calcular a inversa da matriz de transformação
Matrix* criaMatrizTransformacaoInv(double orient) {
    Matrix* matriz = criaMatrizTransformacao(orient);
    Matrix* matrizInv = invert_matrix(matriz);
    destroy_matrix(matriz);
    return matrizInv;
}

// Função para calcular o controle a partir da velocidade
void calcCtrl(EstadoRobo *est, double vel[2], double ctrl[2]) {
    Matrix* matrizInv = criaMatrizTransformacaoInv(est->orientacao); 
    if (!matrizInv) {
        printf("Erro: Matriz não é invertível.\n");
        return;
    }

    // Cria a matriz de velocidade (coluna) e matriz de controle
    Matrix* velMatrix = initialize_matrix(2, 1);
    velMatrix->data[0][0] = vel[0];
    velMatrix->data[1][0] = vel[1];
    
    Matrix* ctrlMatrix = multiply_matrices(matrizInv, velMatrix);

    // Preenche o vetor controle com os valores calculados
    ctrl[0] = ctrlMatrix->data[0][0];
    ctrl[1] = ctrlMatrix->data[1][0];

    // Libera a memória das matrizes
    destroy_matrix(matrizInv);
    destroy_matrix(velMatrix);
    destroy_matrix(ctrlMatrix);
}
