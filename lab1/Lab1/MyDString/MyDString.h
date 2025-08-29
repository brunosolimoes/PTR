#ifndef MYDSTRING_H
#define MYDSTRING_H

#include <stdlib.h>

typedef struct {
  char* bufStr;
  size_t sizeStr;
} MyDString;

size_t lenString(const MyDString* s);
char* bufferString(const MyDString* s);
MyDString* newString(const char* s);
MyDString* charToString(char c);
MyDString* intToString(int i);
MyDString* longToString(long l);
MyDString* floatToString(float f);
MyDString* copString(const MyDString* s);
void concatString(MyDString* strA, const MyDString* strB);

#define $ bufferString

#endif // MYDSTRING_H
