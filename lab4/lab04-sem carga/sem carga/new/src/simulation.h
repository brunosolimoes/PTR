#ifndef SIMULACAO_H
#define SIMULACAO_H
#include "simulation_model.h"

#include <pthread.h>
#include <stdbool.h>

#define PI 3.14159265358979323846
#define DIAMETRO 0.6
#define RAIO 0.3
#define PASSO_TEMPO 0.01
#define TEMPO_FINAL 20.0
#define TAXA_AMOSTRAGEM 30
#define TAMANHO_BUFFER 1000
#define PERIODO_AMOSTRAGEM (TAXA_AMOSTRAGEM * 1000)

typedef struct {
  double tempo;
  double posX, posY;
  double orientacao;
  double ymx, ymy;
  double xref, yref;
} DadosAmostragem;

typedef struct {
  EstadoRobo estado;
  double entrada;
  double ymx, ymy;
  double xref, yref;
  double controle[2];
  double comando[2];
  pthread_mutex_t mutex;
} DadosCompartilhados;

typedef struct {
  DadosAmostragem amostras[TAMANHO_BUFFER];
  int indice;
  pthread_mutex_t mutex;
  pthread_cond_t condicaoCheia;
  bool finalizado;
} BufferArmazenamento;

typedef struct {
  DadosCompartilhados *dados;
  BufferArmazenamento *buffer;
} ArgumentosThread;

double calcularSaida(EstadoRobo estado);
void *executarSimulacao(void *arg);
void *controleEColeta(void *arg);
double calcularSaida(EstadoRobo estado);
void inicializarBuffer(BufferArmazenamento *buffer);
void inicializarDadosCompartilhados(DadosCompartilhados *dados);
void destruirRecursos(BufferArmazenamento *buffer, DadosCompartilhados *dados);
void *storageThread(void *arg);
void *linearizacaoThread(void *arg);
void *controlThread(void *arg);
void criarThreadsPrincipais(pthread_t *threads, ArgumentosThread *args, BufferArmazenamento *buffer);
void criarThreadsAuxiliares(pthread_t *threads, DadosCompartilhados *dados);
void aguardarConclusaoThreads(pthread_t *threads, size_t quantidade);
void configurarParametros();

#endif /* SIMULACAO_H */
