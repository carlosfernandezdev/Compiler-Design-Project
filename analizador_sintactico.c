#include "analizador_sintactico.h"
#include "ast.h"
#include "analizador_lexico.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern Token currentToken; // ✅ Se corrigió la declaración de currentToken

void nextToken();
ASTNode *parseExpr();
ASTNode *parseStatement();
ASTNode *parseBlock();

void nextToken() {
    currentToken = getNextToken();  // Avanza al siguiente token
    printf("[DEBUG] Token actual: %s (%s)\n",
           currentToken.type == TOKEN_KEYWORD ? "KEYWORD" :
           currentToken.type == TOKEN_ID ? "ID" : "OTRO",
           currentToken.text);
}

ASTNode *parseExpr() {
    if (currentToken.type == TOKEN_NUM || currentToken.type == TOKEN_ID) {
        ASTNode *node = newNode(currentToken.type, currentToken.text, NULL, NULL, NULL);
        nextToken();
        return node;
    }
    return NULL;
}

ASTNode *parseStatement() {
    if (strcmp(currentToken.text, "program") == 0) {
        nextToken();
        if (currentToken.type == TOKEN_ID) {
            nextToken();
            if (currentToken.type == TOKEN_SYMBOL && strcmp(currentToken.text, ";") == 0) {
                printf("[DEBUG] Se encontró ';', avanzando al siguiente token.\n");
                nextToken();
                return newNode(TOKEN_ID, "program", NULL, NULL, NULL);
            }
        }
        return NULL;
    }

    if (strcmp(currentToken.text, "var") == 0) {
        printf("[DEBUG] Se encontró 'var', procesando declaración de variables.\n");
        nextToken();
        ASTNode *varList = NULL, *lastVar = NULL, *typeNode = NULL;

        while (currentToken.type == TOKEN_ID) {
            ASTNode *newVar = newNode(TOKEN_ID, currentToken.text, NULL, NULL, NULL);
            if (!varList) varList = newVar;
            else lastVar->right = newVar;
            lastVar = newVar;
            nextToken();

            while (currentToken.type == TOKEN_SYMBOL && strcmp(currentToken.text, ",") == 0) {
                nextToken();
                if (currentToken.type == TOKEN_ID) {
                    ASTNode *extraVar = newNode(TOKEN_ID, currentToken.text, NULL, NULL, NULL);
                    lastVar->right = extraVar;
                    lastVar = extraVar;
                    nextToken();
                } else return NULL;
            }

            if (currentToken.type == TOKEN_SYMBOL && strcmp(currentToken.text, ":") == 0) {
                nextToken();
                if (currentToken.type == TOKEN_ID) {
                    typeNode = newNode(TOKEN_ID, currentToken.text, NULL, NULL, NULL);
                    nextToken();
                    if (currentToken.type == TOKEN_SYMBOL && strcmp(currentToken.text, ";") == 0) {
                        nextToken();
                    } else return NULL;
                } else return NULL;
            } else return NULL;
        }
        return newNode(TOKEN_ID, "var_decl", varList, typeNode, NULL);
    }
    return NULL;
}
