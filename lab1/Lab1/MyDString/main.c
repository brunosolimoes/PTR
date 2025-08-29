/*
laboratorio 01 -> MyDString
Bruno de Moura Solimões - 22051316
*/

#include <stdio.h>
#include "MyDString.h"

int main() {
  //----------------Criando as strings----------------//
  MyDString* name = newString("Bruno Solimoes");
  MyDString* simb = charToString('!');
  MyDString* age = intToString(24);
  MyDString* myFutureWealth = longToString(9000000000L);
  MyDString* radomFloatNumber = floatToString(25.007f);
  MyDString* copName = copString(name);
  //--------------------------------------------------//
  
  //--------------Imprimindo as strings---------------//
  printf("Nome do cara que quer se formar esse periodo: %s\n", $(name));
  printf("O simbolo do grau do desespero: %s\n", $(simb));
  printf("Idade atual dele: %s\n", $(age));
  printf("O quando ele quer deixar de heranca: %s\n", $(myFutureWealth));
  printf("25 filmes do 007: %s\n", $(radomFloatNumber));
  printf("Copia do nome: %s\n", $(copName));
  //--------------------------------------------------//

  //--------------Concatenando Dstrings---------------//
  concatString(name, simb); 
  printf("Concatenando nome e simbolo: %s\n", $(name));
  //--------------------------------------------------//

  //------Exibindo o tamanho da Dstring saudacao------//
  printf("Tamanho do nome atualmente: %zu\n", lenString(name));
  //--------------------------------------------------//
  
  //------------Liberando a memória alocada-----------//
  free(name->bufStr);
  free(name);
  free(simb->bufStr);
  free(simb);
  free(age->bufStr);
  free(age);
  free(myFutureWealth->bufStr);
  free(myFutureWealth);
  free(radomFloatNumber->bufStr);
  free(radomFloatNumber);
  free(copName->bufStr);
  free(copName);
  //--------------------------------------------------//
  
  return 0;
}
