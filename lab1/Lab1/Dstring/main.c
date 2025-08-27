/*
Aluno: Matheus Carvalho Reges
Matrícula: 22152027

Trabalho: lab1 - PTR - Dstring
*/

#include <stdio.h>
#include "Dstring.h"

int main() {
  // Criando as Dstrings com novos valores
  Dstring* saudacao = criarDstringPtr("Oi");
  Dstring* simbolo = criarDstringChar('?');
  Dstring* idade = criarDstringInt(25);
  Dstring* populacao = criarDstringLong(7800000000L);
  Dstring* pi = criarDstringFloat(3.14f);
  Dstring* copia_saudacao = copiarDstring(saudacao);

  // Exibindo as Dstrings
  printf("saudacao: %s\n", $(saudacao)); // criarDstringPtr
  printf("simbolo: %s\n", $(simbolo)); // criarDstringChar
  printf("idade: %s\n", $(idade)); // criarDstringInt
  printf("populacao: %s\n", $(populacao)); // criarDstringLong
  printf("pi: %s\n", $(pi)); // criarDstringFloat
  printf("copia_saudacao: %s\n", $(copia_saudacao)); // copiarDstring
  
  // Concatenando Dstrings
  concatenarDstrings(saudacao, simbolo); 
  printf("Após a concatenação, saudacao: %s\n", $(saudacao));
  
  // Exibindo o tamanho da Dstring saudacao
  printf("Tamanho de saudacao: %zu\n", obterTamanhoDstring(saudacao));

  // Liberando a memória alocada
  free(saudacao->buffer);
  free(saudacao);
  free(simbolo->buffer);
  free(simbolo);
  free(idade->buffer);
  free(idade);
  free(populacao->buffer);
  free(populacao);
  free(pi->buffer);
  free(pi);
  free(copia_saudacao->buffer);
  free(copia_saudacao);

  return 0;
}
