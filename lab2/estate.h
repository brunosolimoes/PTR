#ifndef ESTATE_H
#define ESTATE_H

#include "model.h"

// Declaração da função para calcular o movimento do robô
void computeRobotEstate(RobotState *estate, double angVel, double deltaTime);

#endif
