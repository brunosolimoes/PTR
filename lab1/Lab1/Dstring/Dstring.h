#ifndef DSTRING_H
#define DSTRING_H

#include <stdlib.h>

typedef struct {
  char* buffer;
  size_t length;
} Dstring;

Dstring* criarDstringPtr(const char* str);
Dstring* criarDstringChar(char c);
Dstring* criarDstringInt(int num);
Dstring* criarDstringLong(long num);
Dstring* criarDstringFloat(float num);
Dstring* copiarDstring(const Dstring* dstr);
void concatenarDstrings(Dstring* dest, const Dstring* src);
size_t obterTamanhoDstring(const Dstring* dstr);
char* obterBufferDstring(const Dstring* dstr);

#define $ obterBufferDstring

#endif // DSTRING_H
