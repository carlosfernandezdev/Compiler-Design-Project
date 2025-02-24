#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ASTNode *newNode(TokenType type, const char *value, ASTNode *left, ASTNode *right, ASTNode *extra) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = type;  // ✅ Ahora usamos 'type'
    strncpy(node->value, value, sizeof(node->value) - 1);
    node->value[sizeof(node->value) - 1] = '\0';
    node->left = left;
    node->right = right;
    node->extra = extra;
    return node;
}

