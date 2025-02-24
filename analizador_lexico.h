#ifndef ANALIZADOR_LEXICO_H
#define ANALIZADOR_LEXICO_H

#include "tokens.h"

void initLexer(const char *filename);
Token getNextToken();
void closeLexer();

#endif // ANALIZADOR_LEXICO_H
