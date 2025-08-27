#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <math.h>
#include <sys/time.h>
#include "impressao.h"
#include "matrix.h"
#include "dstring.h"
#include "integral.h"
#include "model.h"

typedef struct {
    float t;
    struct timeval last_call_time;
    double *periods;
    double *jitters;
    int call_count;
    double ideal_period;
} ThreadArgs;

double seno(double x) {
    return sin(x);
}

double coss(double x) {
    return cos(x);
}

void escrever_saida(FILE *f, Vetor *seno, Vetor *cosseno, Vetor *angulo) {
    // Imprimir o cabeçalho com vírgulas
    fprintf(f, "seno,cosseno,angulo\n");

    // Iterar sobre os vetores e imprimir os valores lado a lado
    while (seno != NULL || cosseno != NULL || angulo != NULL) {
        // Imprimir os valores ou deixar vazio se o vetor já tiver terminado
        if (seno != NULL) {
            fprintf(f, "%.5f,", seno->dado);
            seno = seno->prox;
        } else {
            fprintf(f, ",");
        }

        if (cosseno != NULL) {
            fprintf(f, "%.5f,", cosseno->dado);
            cosseno = cosseno->prox;
        } else {
            fprintf(f, ",");
        }

        if (angulo != NULL) {
            fprintf(f, "%.5f", angulo->dado);
            angulo = angulo->prox;
        }

        fprintf(f, "\n"); // Fim da linha
    }
}

pthread_mutex_t lock;
Matrix *u, *estado, *xt, *yt, *yf, *ym, *i, *auxy;
volatile sig_atomic_t running = 1;
Vetor *vetor_seno, *vetor_cosseno, *vetor_angulo;
const float D = 0.6;

void update_metrics(ThreadArgs *args) {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);

    if (args->call_count > 0) {
        double elapsed_time = (current_time.tv_sec - args->last_call_time.tv_sec) +
                              (current_time.tv_usec - args->last_call_time.tv_usec) / 1e6;
        args->periods[args->call_count - 1] = elapsed_time;
        args->jitters[args->call_count - 1] = fabs(elapsed_time - args->ideal_period);
    }

    args->last_call_time = current_time;
    args->call_count++;
}

void *tarefa1(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    Integral *integral_angulo;

    struct timeval start_time;
    gettimeofday(&start_time, NULL); // Marca o tempo inicial da thread 1

    while (running) {
        // Verifica o tempo desde o início da thread
        struct timeval current_time;
        gettimeofday(&current_time, NULL);
        double elapsed_time = (current_time.tv_sec - start_time.tv_sec) + 
                              (current_time.tv_usec - start_time.tv_usec) / 1e6;

        if (elapsed_time >= 20.0) {
            running = 0; // Para a execução da thread 1 após 20 segundos
            printf("Thread 1 foi interrompida após %.2f segundos.\n", elapsed_time); // Mensagem para debug
            break; // Termina o loop explicitamente
        }        

        // Atualiza as métricas de tempo
        printf("Tempo: %.6f\n", args->t);
        update_metrics(args);

        // Bloqueia a execução da thread para evitar condições de corrida
        pthread_mutex_lock(&lock);
        integral_angulo = inicializa_integral(getControlSignalK, args->t, args->t + 0.03, 100);
        u->data[0][1] = computa_integral(integral_angulo);
        vetor_angulo = adicionar_nodo(vetor_angulo, u->data[0][1]);
        args->t += 0.03;
        pthread_mutex_unlock(&lock);

        libera_integral(integral_angulo);
        printf("Seno: %.6f, Cosseno: %.6f, Angulo: %.6f\n", yf->data[0][0], yf->data[1][0], yf->data[2][0]);
        vetor_seno = adicionar_nodo(vetor_seno, yf->data[0][0]);
        vetor_cosseno = adicionar_nodo(vetor_cosseno, yf->data[1][0]);

        // Aguarda um pouco antes de rodar novamente
        usleep(30000);  // 30 ms
        args->t = args->t + 0.03;
    }
    return NULL;
}

void *tarefa2(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    Integral *integral_seno, *integral_cosseno;
    Matrix *auxsoma, *auxprod;
    while (running) {
	printf("Entrou thread B: Tempo: %.2f\n", args->t);
        update_metrics(args);

        pthread_mutex_lock(&lock);
        integral_seno = inicializa_integral(seno, args->t, args->t + 0.05, 100);
        integral_cosseno = inicializa_integral(coss, args->t, args->t + 0.05, 100);
        estado->data[0][0] = computa_integral(integral_seno);
        estado->data[1][0] = computa_integral(integral_cosseno);
        xt = multiply_matrices(estado, u);
        auxy->data[0][0] = 0.5 * D * coss(args->t);
        auxy->data[1][1] = 0.5 * D * seno(args->t);
        auxprod = multiply_matrices(auxy, xt);
        auxsoma = sum_matrices(xt, auxprod);
        destroy_matrix(yf);
        yf = auxsoma;
        vetor_seno = adicionar_nodo(vetor_seno, yt->data[0][0]);
        vetor_cosseno = adicionar_nodo(vetor_cosseno, yt->data[1][0]);
        pthread_mutex_unlock(&lock);

        destroy_matrix(auxprod);
        libera_integral(integral_seno);
        libera_integral(integral_cosseno);

        args->t += 0.05;
        usleep(50000);
    }
    return NULL;
}

void sigHandler(int signo) {
    if (signo == SIGALRM) {
        running = 0;
    }
}

int main() {
    u = initialize_matrix(2, 1);
    estado = initialize_matrix(3, 2);
    xt = initialize_matrix(3, 1);
    yt = initialize_matrix(3, 1);
    yf = initialize_matrix(3, 1);
    auxy = initialize_matrix(3, 3);
    i = initialize_matrix(3, 3);

    vetor_seno = NULL;
    vetor_cosseno = NULL;
    vetor_angulo = NULL;

    float V1[2][1] = {{1}, {0}};
    float V2[3][2] = {{0, 0}, {0, 0}, {0, 1}};
    float V3[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    float V4[3][1] = {{0}, {0}, {0}};

    u = copy_matrix(u, 2, 1, V1);
    estado = copy_matrix(estado, 3, 2, V2);
    i = copy_matrix(i, 3, 3, V3);
    xt = copy_matrix(xt, 1, 1, V4);
    yt = copy_matrix(yt, 1, 1, V4);
    yf = copy_matrix(yf, 2, 1, V4);
    auxy = copy_matrix(auxy, 2, 1, V4);

    ThreadArgs *argt1 = (ThreadArgs *)malloc(sizeof(ThreadArgs));
    argt1->t = 0;
    argt1->ideal_period = 0.03;
    argt1->periods = (double *)malloc(1000 * sizeof(double));
    argt1->jitters = (double *)malloc(1000 * sizeof(double));
    argt1->call_count = 0;
    gettimeofday(&argt1->last_call_time, NULL);

    ThreadArgs *argt2 = (ThreadArgs *)malloc(sizeof(ThreadArgs));
    argt2->t = 0;
    argt2->ideal_period = 0.05;
    argt2->periods = (double *)malloc(1000 * sizeof(double));
    argt2->jitters = (double *)malloc(1000 * sizeof(double));
    argt2->call_count = 0;
    gettimeofday(&argt2->last_call_time, NULL);

    pthread_t thread_idA, thread_idB;

    pthread_mutex_init(&lock, NULL);

    signal(SIGALRM, sigHandler);
    alarm(10.9);

    if (pthread_create(&thread_idA, NULL, tarefa1, (void *)argt1) != 0) {
        fprintf(stderr, "Erro ao criar a thread 1.\n");
        return 1;
    }

    if (pthread_create(&thread_idB, NULL, tarefa2, (void *)argt2) != 0) {
        fprintf(stderr, "Erro ao criar a thread 2.\n");
        return 1;
    }

    pthread_join(thread_idA, NULL);
    pthread_join(thread_idB, NULL);

    pthread_mutex_destroy(&lock);

FILE *metric_file = fopen("data/dados_threads.txt", "w");

// Verifica se o arquivo foi aberto com sucesso
if (metric_file == NULL) {
    perror("Erro ao abrir o arquivo");
    return 1; // ou a ação de erro apropriada
}

// Escreve os dados da Thread 1
for (int i = 0; i < argt1->call_count - 1; i++) {
    fprintf(metric_file, "thread,1,%.6f,%.6f\n", argt1->periods[i], argt1->jitters[i]);
}

// Escreve os dados da Thread 2
for (int i = 0; i < argt2->call_count - 1; i++) {
    fprintf(metric_file, "thread,2,%.6f,%.6f\n", argt2->periods[i], argt2->jitters[i]);
}

fclose(metric_file);

    destroy_matrix(u);
    destroy_matrix(estado);
    destroy_matrix(xt);
    destroy_matrix(yt);
    destroy_matrix(yf);
    destroy_matrix(i);
    destroy_matrix(auxy);

    FILE *arquivo;
    arquivo = fopen("data/saida.txt", "w");

    escrever_saida(arquivo, vetor_seno, vetor_cosseno, vetor_angulo);

    liberar_lista(vetor_seno);
    liberar_lista(vetor_cosseno);
    liberar_lista(vetor_angulo);

    free(argt1->periods);
    free(argt1->jitters);
    free(argt1);

    free(argt2->periods);
    free(argt2->jitters);
    free(argt2);

    return 0;
}
