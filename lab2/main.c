#include "estate.h"
#include "model.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI_CONST 3.14159265358979323846
#define ROBOT_DIAMETER 0.6

int main() {
  FILE *output = fopen("resultados.txt", "w");
  if (!output) {
    perror("Erro ao abrir arquivo de resultados");
    return EXIT_FAILURE;
  }

  fprintf(output, "Tempo,Controle(u),PosX(x),PosY(y),Orientacao(theta)\n");

  const double totalTime = 20.0, deltaT = 0.01;
  RobotState estate = {0.0, 0.0, 0.0}; // Estado inicial do robô

  for (double time = 0; time <= totalTime; time += deltaT) {
    double control = getControlSignal(time); // Sinal de controle em tempo atual
    computeRobotEstate(&estate, control, deltaT); // Atualiza estado do robô
    fprintf(output, "%lf,%lf,%lf,%lf,%lf\n", time, control,
            estate.x, estate.y, estate.ang);
  }

  fclose(output);
  return EXIT_SUCCESS;
}
