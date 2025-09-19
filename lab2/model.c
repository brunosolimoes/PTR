#include <math.h>
#include "model.h"

//---Implementação da função que calcula a entrada de controle u(t)---//
//------------------------Entrada u(t) = [v, w]-----------------------//

ControlInput getControlInput(double t) {
    ControlInput u;
    
    //Define a velocidade linear constante e a velocidade angular baseada no tempo
    u.velLinV = 1.0; 
    if (t < 10.0) {
        u.velAngW = 0.2 * M_PI;
    } else {
        u.velAngW = -0.2 * M_PI;
    }
    
    return u;
}

//--Implementação da função que calcula a posição do ponto frontal do robô--//
//---------y(t) = x(t) + [0.5 * D * cos(x3), 0.5 * D * sen(x3)]^T----//
RobotOutput getRobotFrontPoint(RobotPosition *pos) {
    RobotOutput y;
    
    //Calcula a posição do ponto frontal (xc + 0.5 * D * cos(theta), yc + 0.5 * D * sen(theta))
    y.frontX = pos->posX + 0.5 * ROBOT_DIAMETER * cos(pos->angTeta);
    y.frontY = pos->posY + 0.5 * ROBOT_DIAMETER * sin(pos->angTeta);
    
    return y;
}