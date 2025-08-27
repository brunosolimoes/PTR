#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "model.h"

double getControlSignal(double time) {
    double controlOutput;

    if (time < 0) {
        controlOutput = 0;
    } else if (time < 10) {
        controlOutput = 1; // Valor de controle 1 para tempo < 10
    } else {
        controlOutput = -0.2 * M_PI; // Valor de controle -0.2 * M_PI para tempo > 10
    }

    return controlOutput;
}
