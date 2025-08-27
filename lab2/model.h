#ifndef MODEL_H
#define MODEL_H

typedef struct {
  double x;          // Posição x do centro de massa
  double y;          // Posição y do centro de massa
  double ang; // Ângulo de orientação do robô
} RobotState;

extern double getControlSignal(double time);

#endif /* MODEL_H */
