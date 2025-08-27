#include "simulation.h"
#include "estate.h"
#include "simulation_model.h"

#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

static bool executando = true;

static FILE* arquivoTempoJitter = NULL;

double calcularSaida(EstadoRobo estado) {
  return estado.posX + (0.5 * DIAMETRO * cos(estado.orientacao));
}

void inicializarArquivoTempoJitter() {
    arquivoTempoJitter = fopen("data/tempo_e_jitter.txt", "w");
    if (!arquivoTempoJitter) {
        perror("Erro ao abrir arquivo para tempos e jitter");
        exit(EXIT_FAILURE);
    }
    fprintf(arquivoTempoJitter, "Thread, Chamada, T(k), Jitter(k)\n");
}

void finalizarArquivoTempoJitter() {
    if (arquivoTempoJitter) {
        fclose(arquivoTempoJitter);
    }
}

void registrarTempoEJitter(const char* threadNome, int chamada, double tempoIdeal, double tempoAtual, double* ultimoTempo) {
    double deltaTempo = tempoAtual - *ultimoTempo;
    double jitter = fabs(deltaTempo - tempoIdeal);

    // Atualiza o último tempo de execução
    *ultimoTempo = tempoAtual;

    // Escreve no arquivo
    if (arquivoTempoJitter) {
        fprintf(arquivoTempoJitter, "%s, %d, %.6f, %.6f\n", threadNome, chamada, deltaTempo, jitter);
    }
}

void* executarSimulacao(void* arg) {
    DadosCompartilhados* dados = (DadosCompartilhados*)arg;

    static double ultimoTempoSimulacao = 0.0; // Variável para armazenar o último tempo
    static int chamadaSimulacao = 0;         // Contador de chamadas da simulação

    for (double tempoAtual = 0; tempoAtual <= TEMPO_FINAL && executando; tempoAtual += PASSO_TEMPO) {
        // Obtém o tempo atual do sistema
        struct timespec inicio;
        clock_gettime(CLOCK_REALTIME, &inicio);
        double tempoAtualSistema = inicio.tv_sec + inicio.tv_nsec / 1e9;

        // Registra tempos e jitter
        registrarTempoEJitter("Simulacao", ++chamadaSimulacao, PASSO_TEMPO, tempoAtualSistema, &ultimoTempoSimulacao);

        // Execução da simulação
        pthread_mutex_lock(&dados->mutex);
        computeRobotEstate(&dados->estado, dados->entrada, PASSO_TEMPO);
        pthread_mutex_unlock(&dados->mutex);

        // Pausa para sincronização
        struct timespec ts;
        ts.tv_sec = (time_t)PASSO_TEMPO; 
        ts.tv_nsec = (long)((PASSO_TEMPO - ts.tv_sec) * 1e9); 
        clock_nanosleep(CLOCK_MONOTONIC, 0, &ts, NULL);
    }

    executando = false; // Finaliza o loop de outras threads
    return NULL;
}

void *controleEColeta(void *arg) {
    ArgumentosThread *args = (ArgumentosThread *)arg;
    DadosCompartilhados *dados = args->dados;
    BufferArmazenamento *buffer = args->buffer;

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

        struct timespec ts;
        ts.tv_sec = PERIODO_AMOSTRAGEM / 1000000;  // Parte inteira de PERIODO_AMOSTRAGEM em segundos
        ts.tv_nsec = (PERIODO_AMOSTRAGEM % 1000000) * 1000;  // Resto em nanosegundos
        clock_nanosleep(CLOCK_MONOTONIC, 0, &ts, NULL);;
    }

    pthread_mutex_lock(&buffer->mutex);
    buffer->finalizado = true;
    pthread_cond_broadcast(&buffer->condicaoCheia);
    pthread_mutex_unlock(&buffer->mutex);
    return NULL;
}

void inicializarBuffer(BufferArmazenamento *buffer) {
    buffer->amostras[0] = (DadosAmostragem){0};
    buffer->indice = 0;
    buffer->finalizado = false;
    pthread_mutex_init(&buffer->mutex, NULL);
    pthread_cond_init(&buffer->condicaoCheia, NULL);
}

void inicializarDadosCompartilhados(DadosCompartilhados *dados) {
    dados->estado = (EstadoRobo){0.0, 0.0, 0.0};
    dados->entrada = 0.0;
    pthread_mutex_init(&dados->mutex, NULL);
}

void destruirRecursos(BufferArmazenamento *buffer, DadosCompartilhados *dados) {
    pthread_mutex_destroy(&dados->mutex);
    pthread_mutex_destroy(&buffer->mutex);
    pthread_cond_destroy(&buffer->condicaoCheia);
}

void *storageThread(void *arg) {
    BufferArmazenamento *buffer = (BufferArmazenamento *)arg;
    FILE *outputFile = fopen("data/pos_or_log.txt", "w");
    if (!outputFile) {
        perror("Erro ao abrir arquivo de saída");
        return NULL;
    }

    fprintf(outputFile, "Tempo, Posicao X, Posicao Y, Orientacao\n");

    while (true) {
        pthread_mutex_lock(&buffer->mutex);
        while (buffer->indice == 0 && !buffer->finalizado) {
            pthread_cond_wait(&buffer->condicaoCheia, &buffer->mutex);
        }

        if (buffer->indice == 0 && buffer->finalizado) {
            pthread_mutex_unlock(&buffer->mutex);
            break;
        }

        while (buffer->indice > 0) {
            DadosAmostragem amostra = buffer->amostras[--buffer->indice];
            fprintf(outputFile, "%lf, %lf, %lf, %lf\n", amostra.tempo, amostra.posX, amostra.posY, amostra.orientacao);
        }

        fflush(outputFile);
        pthread_mutex_unlock(&buffer->mutex);
    }

    fclose(outputFile);
    printf("ENCERRADO. SUCESSO\n");
    return NULL;
}

// Função para realizar cálculos de linearização
void *linearizacaoThread(void *arg) {
    DadosCompartilhados *dados = (DadosCompartilhados *)arg;
    double v[2] = {0.0, 0.0};

    while (executando) {
        pthread_mutex_lock(&dados->mutex);
        calcCtrl(&dados->estado, v, dados->controle);
        pthread_mutex_unlock(&dados->mutex);
        struct timespec ts;
	ts.tv_sec = 0;  
	ts.tv_nsec = 40000 * 1000; 
	clock_nanosleep(CLOCK_MONOTONIC, 0, &ts, NULL);
    }
    return NULL;
}

// Função para cálculo e aplicação de sinal de controle
void *controlThread(void *arg) {
    DadosCompartilhados *dados = (DadosCompartilhados *)arg;

    while (executando) {
        pthread_mutex_lock(&dados->mutex);
        double y[2] = {dados->estado.posX, dados->estado.posY};
        calcularSinalControle(y, dados->ymx, dados->ymy, dados->comando);
        pthread_mutex_unlock(&dados->mutex);
        struct timespec ts;
	ts.tv_sec = 0;  
	ts.tv_nsec = 50000 * 1000; 
	clock_nanosleep(CLOCK_MONOTONIC, 0, &ts, NULL);;
    }
    return NULL;
}

void criarThreadsPrincipais(pthread_t *threads, ArgumentosThread *args, BufferArmazenamento *buffer) {
    pthread_create(&threads[0], NULL, executarSimulacao, args->dados);
    pthread_create(&threads[1], NULL, controleEColeta, args);
    pthread_create(&threads[2], NULL, storageThread, buffer);
    pthread_create(&threads[3], NULL, linearizacaoThread, args->dados);
}

void criarThreadsAuxiliares(pthread_t *threads, DadosCompartilhados *dados) {
    pthread_create(&threads[0], NULL, simulacaoModeloX, dados);
    pthread_create(&threads[1], NULL, simulacaoModeloY, dados);
    pthread_create(&threads[2], NULL, gerarReferencia, dados);
}

void aguardarConclusaoThreads(pthread_t *threads, size_t quantidade) {
    for (size_t i = 0; i < quantidade; i++) {
        pthread_join(threads[i], NULL);
    }
}

void configurarParametros() {
    char desejaMudar;
    printf("ALPHA1 atual é %lf. Deseja mudar? (s/n): ", PARAM_ALPHA1);
    scanf(" %c", &desejaMudar);
    if (desejaMudar == 's' || desejaMudar == 'S') {
        printf("Digite o novo valor para ALPHA1: ");
        scanf("%lf", &PARAM_ALPHA1);
    }

    printf("ALPHA2 atual é %lf. Deseja mudar? (s/n): ", PARAM_ALPHA2);
    scanf(" %c", &desejaMudar);
    if (desejaMudar == 's' || desejaMudar == 'S') {
        printf("Digite o novo valor para ALPHA2: ");
        scanf("%lf", &PARAM_ALPHA2);
    }
}



