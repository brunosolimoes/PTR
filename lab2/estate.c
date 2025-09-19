#include <math.h>
#include "estate.h"

//--------------------------Calcula o movimento do robô---------------------------//
//------------------ẋ(t) = [sin(x3) 0; cos(x3) 0; 0 1] * u(t)---------------------//
//---------------------------A entrada u(t) = [v, w]^T----------------------------//
void compRobMove(RobotPosition *position, ControlInput *input, double deltaTime) {
    
    //Atualiza a posição (xc, yc) usando a velocidade linear v e a orientação θ
    position->posX += deltaTime * input->velLinV * cos(position->angTeta);
    position->posY += deltaTime * input->velLinV * sin(position->angTeta);
    
    //Atualiza a orientação θ usando a velocidade angular w
    position->angTeta += deltaTime * input->velAngW;
}