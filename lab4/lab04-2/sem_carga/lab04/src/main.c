#include "estate.h"
#include "simulation_model.h"
#include "simulation.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

bool executando = true;

void finalizarExecucao(int sig) {
    (void)sig; // Evita o aviso de parâmetro não utilizado
    executando = false; // Marca que o programa deve parar
    printf("Execução finalizada!\n");
}

int main() {
    signal(SIGINT, finalizarExecucao);

    inicializarArquivoTempoJitter();

    configurarParametros();

    DadosCompartilhados dadosCompartilhados;
    inicializarDadosCompartilhados(&dadosCompartilhados);

    BufferArmazenamento bufferArmazenamento;
    inicializarBuffer(&bufferArmazenamento);

    // Inicializa arquivos de saída
    FILE *arquivoSimulacao = fopen("data/tempo_e_jitter.txt", "w");
    FILE *arquivoStorage = fopen("data/pos_or_log.txt", "w");
    FILE *arquivoYmx = fopen("data/registro_ymx.txt", "w");
    FILE *arquivoYmy = fopen("data/registro_ymy.txt", "w");
    FILE *arquivoRef = fopen("data/registro_ref.txt", "w");

    if (!arquivoSimulacao || !arquivoStorage || !arquivoYmx || !arquivoYmy || !arquivoRef) {
        perror("Erro ao abrir arquivos de saída");
        exit(EXIT_FAILURE);
    }

    fprintf(arquivoSimulacao, "Thread, Chamada, T(k), Jitter(k)\n");
    fprintf(arquivoStorage, "Tempo, Posicao X, Posicao Y, Orientacao\n");
    fprintf(arquivoYmx, "Tempo, ymx\n");
    fprintf(arquivoYmy, "Tempo, ymy\n");
    fprintf(arquivoRef, "Tempo, Xref, Yref\n");

    double ultimoTempoSimulacao = 0.0;
    int chamadaSimulacao = 0;

    for (double tempoAtual = 0; tempoAtual <= TEMPO_FINAL && executando; tempoAtual += PASSO_TEMPO) {
        struct timespec inicio;
        clock_gettime(CLOCK_REALTIME, &inicio);
        double tempoAtualSistema = inicio.tv_sec + inicio.tv_nsec / 1e9;

        // Simulação
        registrarTempoEJitter("Simulacao", ++chamadaSimulacao, PASSO_TEMPO, tempoAtualSistema, &ultimoTempoSimulacao);
        computeRobotEstate(&dadosCompartilhados.estado, dadosCompartilhados.entrada, PASSO_TEMPO);

        // Controle e coleta
        dadosCompartilhados.entrada = entradaSistema(tempoAtual);
        double saida = calcularSaida(dadosCompartilhados.estado);
        DadosAmostragem amostra = {tempoAtual, dadosCompartilhados.estado.posX, dadosCompartilhados.estado.posY,
                                   dadosCompartilhados.estado.orientacao, saida, 0.0, 0.0, 0.0};

        if (bufferArmazenamento.indice < TAMANHO_BUFFER) {
            bufferArmazenamento.amostras[bufferArmazenamento.indice++] = amostra;
        }

        // Armazenamento
        while (bufferArmazenamento.indice > 0) {
            DadosAmostragem amostra = bufferArmazenamento.amostras[--bufferArmazenamento.indice];
            fprintf(arquivoStorage, "%lf, %lf, %lf, %lf\n", amostra.tempo, amostra.posX, amostra.posY, amostra.orientacao);
        }

        // Modelo X e Y
        atualizarValor(&dadosCompartilhados.ymx, dadosCompartilhados.xref, PARAM_OMEGA);
        atualizarValor(&dadosCompartilhados.ymy, dadosCompartilhados.yref, PARAM_OMEGA);

        fprintf(arquivoYmx, "%.2f, %.4f\n", tempoAtual, dadosCompartilhados.ymx);
        fprintf(arquivoYmy, "%.2f, %.4f\n", tempoAtual, dadosCompartilhados.ymy);

        // Referências
        calcularReferencias(tempoAtual, &dadosCompartilhados.xref, &dadosCompartilhados.yref);
        fprintf(arquivoRef, "%.2f, %.4f, %.4f\n", tempoAtual, dadosCompartilhados.xref, dadosCompartilhados.yref);
	
	struct timespec ts;
        ts.tv_sec = (time_t)PASSO_TEMPO;  // A parte inteira em segundos
        ts.tv_nsec = (long)((PASSO_TEMPO - ts.tv_sec) * 1e9);  // A parte decimal em nanosegundos
        clock_nanosleep(CLOCK_MONOTONIC, 0, &ts, NULL);
    }

    fclose(arquivoSimulacao);
    fclose(arquivoStorage);
    fclose(arquivoYmx);
    fclose(arquivoYmy);
    fclose(arquivoRef);

    finalizarArquivoTempoJitter();
    destruirRecursos(&bufferArmazenamento, &dadosCompartilhados);

    return EXIT_SUCCESS;
}
