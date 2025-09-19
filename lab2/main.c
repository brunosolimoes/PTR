/*
laboratorio 02 -> Controle e Simulação de um Robô Móvel
Bruno de Moura Solimões - 22051316
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#include "model.h"
#include "estate.h"

//-----------Estrutura para os dados compartilhados-----------//
typedef struct {
    RobotPosition x;  
    ControlInput u;
    RobotOutput y;
} SharedData;
//------------------------------------------------------------//

//---ariáveis globais para compartilhamento e sincronização---//
SharedData shared_data;
pthread_mutex_t data_mutex;
//------------------------------------------------------------//

//------------------Funções para as threads------------------//
void *thread_control_sampling(void *arg);
void *thread_simulation(void *arg);
//------------------------------------------------------------//

//---------Thread 1: Geração de controle e amostragem---------//
void *thread_control_sampling(void *arg) {
    
  FILE *output = fopen("resultados.txt", "w");
  
  if (!output) {
    perror("Erro ao abrir arquivo de resultados");
    return NULL;
  }
  fprintf(output, "Tempo,VelLinear(v),VelAngular(w),PosX_Frente(x),PosY_Frente(y)\n");

  const double totalTime = 20.0;
  const int sample_period_ms = 30;

  for (double time = 0.0; time <= totalTime; time += (double)sample_period_ms / 1000.0) {
  
    pthread_mutex_lock(&data_mutex);
        
    if (time < 10.0) {
      shared_data.u.velLinV = 1.0;
      shared_data.u.velAngW = 0.2 * M_PI;
    } else {
      shared_data.u.velLinV = 1.0;
      shared_data.u.velAngW = -0.2 * M_PI;
    }

    fprintf(output, "%lf,%lf,%lf,%lf,%lf\n", time, shared_data.u.velLinV, shared_data.u.velAngW, shared_data.y.frontX, shared_data.y.frontY);
        
    pthread_mutex_unlock(&data_mutex);
    usleep(sample_period_ms * 1000);

  }

  fclose(output);
  return NULL;
}
//------------------------------------------------------------//

//-----------------Thread 2: Simulação do modelo--------------//
void *thread_simulation(void *arg) {
  
  const int sim_period_ms = 50;  
  const double totalTime = 20.0;
    
    for (double time = 0.0; time <= totalTime; time += (double)sim_period_ms / 1000.0) {
        
      pthread_mutex_lock(&data_mutex);
      compRobMove(&shared_data.x, &shared_data.u, (double)sim_period_ms / 1000.0);
      shared_data.y = getRobotFrontPoint(&shared_data.x);
      pthread_mutex_unlock(&data_mutex);
      usleep(sim_period_ms * 1000);
    }

    return NULL;
}
//------------------------------------------------------------//

//-----------Função principal-----------//
int main() {
    pthread_t thread1, thread2;
    int status;
    
    //-------Inicializar os dados do robô-------//
    shared_data.u.velLinV = 0.0;
    shared_data.u.velAngW = 0.0;
    shared_data.x.posX = 0.0;
    shared_data.x.posY = 0.0;
    shared_data.x.angTeta = 0.0;
    shared_data.y.frontX = 0.0;
    shared_data.y.frontY = 0.0;

    //-------Inicializar o mutex-------//
    pthread_mutex_init(&data_mutex, NULL);

    //--------Criar as threads--------//
    status = pthread_create(&thread1, NULL, thread_control_sampling, NULL);
    if (status != 0) {
        printf("Erro na criação da Thread 1\n");
        return EXIT_FAILURE;
    }

    status = pthread_create(&thread2, NULL, thread_simulation, NULL);
    if (status != 0) {
        printf("Erro na criação da Thread 2\n");
        return EXIT_FAILURE;
    }

    //--------Aguardar o término das threads--------//
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    //--------Destruir o mutex--------//
    pthread_mutex_destroy(&data_mutex);

    return EXIT_SUCCESS;
}