#ifndef MODEL_H
#define MODEL_H

#define ROBOT_DIAMETER 0.3

//--------------Definição das estruturas de dados----------------//
//------------Estado e orientação do robô--------------//
typedef struct {
    double posX;      // Posição x do centro
    double posY;      // Posição y do centro
    double angTeta;   // Ângulo do robô
} RobotPosition;

//------------Entrada de controle do robô--------------//
typedef struct {
    double velLinV;   // Velocidade linear
    double velAngW;   // Velocidade angular
} ControlInput;

//----------Posição do ponto frontal do robô-----------//
typedef struct {
    double frontX;    // Posição x do ponto frontal
    double frontY;    // Posição y do ponto frontal
} RobotOutput;


//------------------A entrada u(t)---------------------//
ControlInput getControlInput(double t);


//------------------A saída yf(t)----------------------//
RobotOutput getRobotFrontPoint(RobotPosition *pos);


#endif /* MODEL_H */