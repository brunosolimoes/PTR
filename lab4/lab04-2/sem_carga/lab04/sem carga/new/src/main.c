#include "estate.h"
#include "simulation_model.h"
#include "simulation.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>

bool executando = true;

void finalizarExecucao(int sig) {
    (void)sig; // Evita o aviso de parâmetro não utilizado
    executando = false;
    printf("Execução finalizada!\n");
}

int main() {
    signal(SIGINT, finalizarExecucao);

    configurarParametros();

    DadosCompartilhados dados;
    inicializarDadosCompartilhados(&dados);

    BufferArmazenamento buffer;
    inicializarBuffer(&buffer);

    for (double tempoAtual = 0.0; tempoAtual <= TEMPO_FINAL && executando; tempoAtual += PASSO_TEMPO) {
        // Simulação do estado do robô
        computeRobotEstate(&dados.estado, dados.entrada, PASSO_TEMPO);

        // Controle e coleta de dados
        dados.entrada = entradaSistema(tempoAtual);
        double saida = calcularSaida(dados.estado);
        DadosAmostragem amostra = {tempoAtual, dados.estado.posX, dados.estado.posY,
                                   dados.estado.orientacao, saida, dados.ymx, dados.ymy, 0.0};
        if (buffer.indice < TAMANHO_BUFFER) {
            buffer.amostras[buffer.indice++] = amostra;
        }

        // Armazenamento em arquivo
        FILE *outputFile = fopen("pos_or_log.txt", "a");
        if (outputFile) {
            fprintf(outputFile, "%lf, %lf, %lf, %lf\n", amostra.tempo, amostra.posX, amostra.posY, amostra.orientacao);
            fclose(outputFile);
        }

        // Atualização do controle
        double v[2] = {0.0, 0.0};
        calcCtrl(&dados.estado, v, dados.controle);
        double y[2] = {dados.estado.posX, dados.estado.posY};
        calcularSinalControle(y, dados.ymx, dados.ymy, dados.comando);

        usleep(PASSO_TEMPO * 1e6); // Simula intervalo de tempo
    }

    printf("Encerrando execução.\n");
    destruirRecursos(&buffer, &dados);

    return EXIT_SUCCESS;
}
