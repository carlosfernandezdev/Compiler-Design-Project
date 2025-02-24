#ifndef ANALIZADOR_SINTACTICO_H
#define ANALIZADOR_SINTACTICO_H

#include "analizador_lexico.h"
#include "ast.h"

extern Token currentToken;

void nextToken();
ASTNode *parseStatement();
ASTNode *parseBlock();

#endif // ANALIZADOR_SINTACTICO_H
