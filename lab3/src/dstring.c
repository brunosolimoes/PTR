#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dstring.h"

Dstring* criar_dstring(const char *string) {
    Dstring *nova_dstring = (Dstring *)malloc(sizeof(Dstring));
    
    if (nova_dstring) {
        if (string) {
            nova_dstring->tam = strlen(string);
            nova_dstring->dado = (char *)malloc((nova_dstring->tam + 1) * sizeof(char));
            if (nova_dstring->dado) {
                strcpy(nova_dstring->dado, string);
            }
        } else {
            nova_dstring->tam = 0;
            nova_dstring->dado = NULL;
        }
    }
    
    return nova_dstring;
}

Dstring* atualizar_dado(Dstring* dstring, const char* string) {
    if (dstring && string) {
        free(dstring->dado);
        dstring->tam = strlen(string);
        dstring->dado = (char*)malloc((dstring->tam + 1) * sizeof(char));
        if (dstring->dado) {
            strcpy(dstring->dado, string);
        }
    }
    return dstring;
}

Dstring* concatenar_dstring(Dstring *dstring, const char *string) {
    if (dstring && string) {
        int novo_tam = dstring->tam + strlen(string);
        
        char *novo_dado = (char *)realloc(dstring->dado, (novo_tam + 1) * sizeof(char));
        if (novo_dado) {
            strcat(novo_dado, string);
            dstring->dado = novo_dado;
            dstring->tam = novo_tam;
        }
    }
    return dstring;
}

void exibir_dstring(const Dstring *dstring) {
    if (dstring && dstring->dado) {
        printf("%s\n", dstring->dado);
    }
}

void liberar_dstring(Dstring *dstring) {
    if (dstring) {
        free(dstring->dado);
        free(dstring);
    }
}