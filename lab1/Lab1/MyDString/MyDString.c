#include "MyDString.h"
#include <stdio.h>
#include <string.h>

//---------------Retorna o tamanho da string------------------//
size_t lenString(const MyDString* s) {
    
    return s != NULL ? s->sizeStr : 0;
}
//------------------------------------------------------------//

//-----------------Retorna o valor da string------------------//
char* bufferString(const MyDString* s) {
    
    return s != NULL ? s->bufStr : NULL;
}
//------------------------------------------------------------//

//-----------------------Cria as strings-----------------------//
MyDString* newString(const char* s) {
    MyDString* string = (MyDString*) malloc(sizeof(MyDString));

    if (string != NULL) {
        string->sizeStr = strlen(s);
        string->bufStr = (char*) malloc(string->sizeStr + 1);

        if (string->bufStr != NULL) {
            strcpy(string->bufStr, s);

        } else {
            free(string);
            return NULL; 
        }
    }

    return string;
}
//------------------------------------------------------------//


//------------------Converte char em string-------------------//
MyDString* charToString(char c) {
    char string[2] = {c, '\0'};

    return newString(string);
}
//------------------------------------------------------------//

//----------------Converte inteiro em string------------------//
MyDString* intToString(int i) {
    char string[12];
    snprintf(string, sizeof(string), "%d", i);
    
    return newString(string);
}
//------------------------------------------------------------//

//-----------------Converte longo em string-------------------//
MyDString* longToString(long l) {
    char string[21];
    snprintf(string, sizeof(string), "%ld", l);
    
    return newString(string);
}
//------------------------------------------------------------//

//-----------------Converte float em string-------------------//
MyDString* floatToString(float f) {
    char string[64];
    snprintf(string, sizeof(string), "%f", f);
    
    return newString(string);
}
//------------------------------------------------------------//

//-----------Copia uma string em outra string nova-----------//
MyDString* copString(const MyDString* s) {
    
    return newString(s->bufStr);
}
//------------------------------------------------------------//

//------------------Concatena duas strings--------------------//
void concatString(MyDString* strA, const MyDString* strB) {

    if (strA != NULL && strB != NULL) {
        strA->sizeStr += strB->sizeStr;
        char* newBufferStr = realloc(strA->bufStr, strA->sizeStr + 1);
    
        if (newBufferStr != NULL) {
            strA->bufStr = newBufferStr;
            strcat(strA->bufStr, strB->bufStr);
        }
    }
}
//------------------------------------------------------------//
