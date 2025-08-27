#include "Dstring.h"
#include <stdio.h>
#include <string.h>

Dstring* criarDstringPtr(const char* str) {
    Dstring* dstr = (Dstring*)malloc(sizeof(Dstring));
    if (dstr != NULL) {
        dstr->length = strlen(str);
        dstr->buffer = (char*)malloc(dstr->length + 1);
        if (dstr->buffer != NULL) {
            strcpy(dstr->buffer, str);
        } else {
            free(dstr);
            return NULL; // Retorna NULL se a alocação falhar
        }
    }
    return dstr;
}

Dstring* criarDstringChar(char c) {
    char str[2] = {c, '\0'};
    return criarDstringPtr(str);
}

Dstring* criarDstringInt(int num) {
    char str[12];
    snprintf(str, sizeof(str), "%d", num);
    return criarDstringPtr(str);
}

Dstring* criarDstringLong(long num) {
    char str[21];
    snprintf(str, sizeof(str), "%ld", num);
    return criarDstringPtr(str);
}

Dstring* criarDstringFloat(float num) {
    char str[64];
    snprintf(str, sizeof(str), "%f", num);
    return criarDstringPtr(str);
}

Dstring* copiarDstring(const Dstring* dstr) {
    return criarDstringPtr(dstr->buffer);
}

void concatenarDstrings(Dstring* dest, const Dstring* src) {
    if (dest != NULL && src != NULL) {
        dest->length += src->length;
        char* new_buffer = realloc(dest->buffer, dest->length + 1);
        if (new_buffer != NULL) {
            dest->buffer = new_buffer;
            strcat(dest->buffer, src->buffer);
        }
    }
}

size_t obterTamanhoDstring(const Dstring* dstr) {
    return dstr != NULL ? dstr->length : 0;
}

char* obterBufferDstring(const Dstring* dstr) {
    return dstr != NULL ? dstr->buffer : NULL;
}
