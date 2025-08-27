#ifndef ESTATE_H
#define ESTATE_H

#include "simulation_model.h"
#include "matrix.h"
#include <math.h>

void computeRobotEstate(EstadoRobo *estate, double angVel, double deltaTime);
Matrix* criaMatrizTransformacao(double orient);
Matrix* criaMatrizTransformacaoInv(double orient);
void calcCtrl(EstadoRobo *est, double vel[2], double ctrl[2]);
#endif