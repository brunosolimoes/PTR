#include "simulation.h"
#include "estate.h"
#include "simulation_model.h"

#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

static bool executando = true;
static double ultimoTempo = 0.0; // Variável para armazenar o último tempo registrado

double calcularSaida(EstadoRobo estado) {
  return estado.posX + (0.5 * DIAMETRO * cos(estado.orientacao));
}

void *executarSimulacao(void *arg) {
    DadosCompartilhados *dados = (DadosCompartilhados *)arg;
    for (double tempoAtual = 0; tempoAtual <= TEMPO_FINAL && executando; tempoAtual += PASSO_TEMPO) {
        pthread_mutex_lock(&dados->mutex);
        computeRobotEstate(&dados->estado, dados->entrada, PASSO_TEMPO);
        pthread_mutex_unlock(&dados->mutex);

        usleep(PASSO_TEMPO * 1e6);
    }
    executando = false; // Finaliza o loop de outras threads
    return NULL;
}

void *controleEColeta(void *arg) {
    ArgumentosThread *args = (ArgumentosThread *)arg;
    DadosCompartilhados *dados = args->dados;
    BufferArmazenamento *buffer = args->buffer;

    FILE *outputFile = fopen("data/tempo_e_jitter.txt", "w");
    if (!outputFile) {
        perror("Erro ao abrir arquivo de tempo e jitter");
        return NULL;
    }

    // Cabeçalho do arquivo
    fprintf(outputFile, "Tempo, Periodo, Jitter\n");

    for (double tempoAtual = 0; tempoAtual <= TEMPO_FINAL && executando; tempoAtual += TAXA_AMOSTRAGEM / 1e3) {
        pthread_mutex_lock(&dados->mutex);
        dados->entrada = entradaSistema(tempoAtual);
        double saida = calcularSaida(dados->estado);
        DadosAmostragem amostra = {tempoAtual, dados->estado.posX, dados->estado.posY,
                                   dados->estado.orientacao, saida, 0.0, 0.0, 0.0};
        pthread_mutex_unlock(&dados->mutex);

        pthread_mutex_lock(&buffer->mutex);
        if (buffer->indice < TAMANHO_BUFFER) {
            buffer->amostras[buffer->indice++] = amostra;
        }
        pthread_cond_signal(&buffer->condicaoCheia);
        pthread_mutex_unlock(&buffer->mutex);

        // Cálculo do período e jitter
        if (ultimoTempo != 0.0) {
            double periodo = tempoAtual - ultimoTempo; // Período real
            double jitter = fabs(periodo - (TAXA_AMOSTRAGEM / 1000.0)); // Jitter
            fprintf(outputFile, "%lf, %lf, %lf\n", tempoAtual, periodo, jitter);
        }

        ultimoTempo = tempoAtual; // Atualiza o último tempo registrado

        usleep(PERIODO_AMOSTRAGEM);
    }

    pthread_mutex_lock(&buffer->mutex);
    buffer->finalizado = true;
    pthread_cond_broadcast(&buffer->condicaoCheia);
    pthread_mutex_unlock(&buffer->mutex);

    fclose(outputFile); // Fecha o arquivo ao final da coleta
    return NULL;
}

// Outras funções permanecem inalteradas
