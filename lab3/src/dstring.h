#ifndef DSTRING_H
#define DSTRING_H

typedef struct {
    char *dado;
    int tam;
} Dstring;

Dstring* criar_dstring(const char *string);
Dstring* atualizar_dado(Dstring* dstring, const char* string);
Dstring* concatenar_dstring(Dstring *dstring, const char *string);
void exibir_dstring(const Dstring *dstring);
void liberar_dstring(Dstring *dstring);

#endif
