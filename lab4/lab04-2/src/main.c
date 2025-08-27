#include "estate.h"
#include "simulation_model.h"
#include "simulation.h"

#include <pthread.h>
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

    inicializarArquivoTempoJitter(); // Inicializa o arquivo

    configurarParametros();

    DadosCompartilhados dadosCompartilhados;
    inicializarDadosCompartilhados(&dadosCompartilhados);

    BufferArmazenamento bufferArmazenamento;
    inicializarBuffer(&bufferArmazenamento);

    ArgumentosThread args = {.dados = &dadosCompartilhados, .buffer = &bufferArmazenamento};

    pthread_t threadsPrincipais[4];
    criarThreadsPrincipais(threadsPrincipais, &args, &bufferArmazenamento);

    pthread_t threadsAuxiliares[3];
    criarThreadsAuxiliares(threadsAuxiliares, &dadosCompartilhados);

    aguardarConclusaoThreads(threadsPrincipais, 4);
    aguardarConclusaoThreads(threadsAuxiliares, 3);

    finalizarArquivoTempoJitter(); // Finaliza o arquivo

    destruirRecursos(&bufferArmazenamento, &dadosCompartilhados);

    return EXIT_SUCCESS;
}