#ifndef SIMULATION_MODEL_H
#define SIMULATION_MODEL_H

extern double PARAM_ALPHA1;
extern double PARAM_ALPHA2;

#define PARAM_BETA 0.5
#define PARAM_OMEGA 0.6

#include <stdio.h>

typedef struct {
  double posX;
  double posY;
  double orientacao;
} EstadoRobo;

extern double entradaSistema(double tempo);
void calcularSinalControle(double saida[2], double refX, double refY, double sinalControle[2]);
void calcularReferencias(double tempo, double *xref, double *yref);
FILE *inicializarRegistro(const char *nomeArquivo, const char *cabecalho);
void atualizarValor(double *valor, double referencia, double parametro);
void *simulacaoModeloX(void *arg);
void *simulacaoModeloY(void *arg);
void *gerarReferencia(void *arg);

#endif /* SIMULATION_MODEL_H */
