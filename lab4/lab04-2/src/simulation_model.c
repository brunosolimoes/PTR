#include "simulation_model.h"
#include "estate.h"
#include "simulation.h"
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PARAM_BETA 0.5
#define PARAM_OMEGA 0.6

double PARAM_ALPHA1 = 3.0;
double PARAM_ALPHA2 = 3.0;

double entradaSistema(double tempo) {
  if (tempo < 0) return 0;
  return (tempo < 10) ? 1 : -0.2 * M_PI;
}

void calcularReferencias(double tempo, double *xref, double *yref) {
    *xref = sin(PARAM_BETA * tempo);
    *yref = cos(PARAM_OMEGA * tempo);
}

FILE *inicializarRegistro(const char *nomeArquivo, const char *cabecalho) {
    FILE *arquivo = fopen(nomeArquivo, "a");
    if (arquivo != NULL) {
        fprintf(arquivo, "%s\n", cabecalho);
    } else {
        perror("Erro ao abrir arquivo");
    }
    return arquivo;
}

void atualizarValor(double *valor, double referencia, double parametro) {
    *valor = referencia * parametro; // Exemplo de cálculo
}

void calcularSinalControle(double saida[2], double refX, double refY, double sinalControle[2]) {
  //erro= ref - saida
  sinalControle[0] = PARAM_ALPHA1 * (refX - saida[0]);
  sinalControle[1] = PARAM_ALPHA2 * (refY - saida[1]);
}

void *simulacaoModeloX(void *arg) {
  DadosCompartilhados *dados = (DadosCompartilhados *)arg;
  FILE *arquivoLog = inicializarRegistro("data/registro_ymx.txt", "Tempo, ymx");
  if (!arquivoLog) {
    return NULL;
  }
  for (double tempoAtual = 0; tempoAtual <= TEMPO_FINAL; tempoAtual += 0.05) {
    pthread_mutex_lock(&dados->mutex);

    // Atualiza o valor de ymx com base no modelo
    atualizarValor(&dados->ymx, dados->xref, PARAM_OMEGA);

    fprintf(arquivoLog, "%.2f, %.4f\n", tempoAtual, dados->ymx);

    pthread_mutex_unlock(&dados->mutex);

    struct timespec ts;
    ts.tv_sec = 0;  // 0 segundos
    ts.tv_nsec = 50000 * 1000; 
    clock_nanosleep(CLOCK_MONOTONIC, 0, &ts, NULL);
  }

  fclose(arquivoLog);

  return NULL;
}

void *simulacaoModeloY(void *arg) {
  DadosCompartilhados *dados = (DadosCompartilhados *)arg;
  FILE *arquivoLog = inicializarRegistro("data/registro_ymy.txt", "Tempo, ymy");
  if (!arquivoLog) {
    return NULL;
  }

  for (double tempoAtual = 0; tempoAtual <= TEMPO_FINAL; tempoAtual += 0.05) {
    pthread_mutex_lock(&dados->mutex);

    // Atualiza o valor de ymy com base no modelo
    atualizarValor(&dados->ymy, dados->yref, PARAM_OMEGA);

    fprintf(arquivoLog, "%.2f, %.4f\n", tempoAtual, dados->ymy);

    pthread_mutex_unlock(&dados->mutex);

    struct timespec ts;
    ts.tv_sec = 0;  // 0 segundos
    ts.tv_nsec = 50000 * 1000; 
    clock_nanosleep(CLOCK_MONOTONIC, 0, &ts, NULL);;
  }
  fclose(arquivoLog);
  printf("Finalizado!");
  return NULL;
}

void *gerarReferencia(void *arg) {
  DadosCompartilhados *dados = (DadosCompartilhados *)arg;
  FILE *arquivoLog = inicializarRegistro("data/registro_ref.txt", "Tempo, Xref, Yref");
  if (!arquivoLog) {
    return NULL; // Se o arquivo não foi aberto corretamente, saia da função
  }

  for (double tempoAtual = 0; tempoAtual <= TEMPO_FINAL; tempoAtual += 0.12) {
        pthread_mutex_lock(&dados->mutex);

        // Utiliza a função auxiliar para calcular xref e yref
        calcularReferencias(tempoAtual, &dados->xref, &dados->yref);

        fprintf(arquivoLog, "%.2f, %.4f, %.4f\n", tempoAtual, dados->xref, dados->yref);

        pthread_mutex_unlock(&dados->mutex);

    struct timespec ts;
    ts.tv_sec = 0;  // 0 segundos
    ts.tv_nsec = 120000 * 1000; 
    clock_nanosleep(CLOCK_MONOTONIC, 0, &ts, NULL);;
    }

  fclose(arquivoLog);
  return NULL;
}
