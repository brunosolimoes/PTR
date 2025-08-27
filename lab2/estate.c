#include "model.h"
#include <math.h>

// Função para calcular o movimento do robô usando nova lógica
void computeRobotEstate(RobotState *estate, double angVel, double deltaTime) {
  const double constLinearVel = 1.0; // Velocidade linear fixa

  // Atualiza posição usando componentes do movimento
  estate->x += deltaTime * constLinearVel * cos(estate->ang);
  estate->y += deltaTime * constLinearVel * sin(estate->ang);

  // Atualiza orientação do ângulo
  estate->ang += deltaTime * angVel;
}
