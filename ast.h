#ifndef AST_H
#define AST_H

#include "tokens.h"

typedef struct ASTNode {
    TokenType type;
    char value[64];
    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *extra;
} ASTNode;

extern ASTNode *newNode(TokenType type, const char *value, ASTNode *left, ASTNode *right, ASTNode *extra);

#endif // AST_H
