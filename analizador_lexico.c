#include "analizador_lexico.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

static FILE *sourceFile;
extern Token currentToken;

const char *keywords[] = {"program", "var", "begin", "end", "integer", "real", "boolean", "if", "then", "else", "while", "do", "for", "to", "downto", "repeat", "until", "procedure", "function", "write", "writeln", "read", "readln"};
const char *operators[] = {":=", "+", "-", "*", "/", "=", "<>", "<", "<=", ">", ">=", "and", "or", "not"};

void initLexer(const char *filename) {
    sourceFile = fopen(filename, "r");
    if (!sourceFile) {
        perror("Error al abrir el archivo");
        return;
    }
}

int isKeyword(const char *word) {
    for (size_t i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int isOperator(const char *op) {
    for (size_t i = 0; i < sizeof(operators) / sizeof(operators[0]); i++) {
        if (strcmp(op, operators[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

Token getNextToken() {
    int c;
    while ((c = fgetc(sourceFile)) != EOF) {
        if (isspace(c)) continue;

        if (isalpha(c)) {
            int i = 0;
            do {
                currentToken.text[i++] = c;
                c = fgetc(sourceFile);
            } while (isalnum(c) && i < (int)(sizeof(currentToken.text) - 1));
            ungetc(c, sourceFile);
            currentToken.text[i] = '\0';
            currentToken.type = isKeyword(currentToken.text) ? TOKEN_KEYWORD : TOKEN_ID;
            return currentToken;
        }

        if (isdigit(c)) {
            int i = 0;
            do {
                currentToken.text[i++] = c;
                c = fgetc(sourceFile);
            } while (isdigit(c) && i < (int)(sizeof(currentToken.text) - 1));
            ungetc(c, sourceFile);
            currentToken.text[i] = '\0';
            currentToken.type = TOKEN_NUM;
            return currentToken;
        }

        if (c == ',' || c == ';' || c == ':' || c == '.') {
            currentToken.type = TOKEN_SYMBOL;
            snprintf(currentToken.text, sizeof(currentToken.text), "%c", c);
            return currentToken;
        }

        currentToken.text[0] = c;
        currentToken.text[1] = '\0';
        currentToken.type = TOKEN_SYMBOL;
        return currentToken;
    }
    currentToken.type = TOKEN_EOF;
    strcpy(currentToken.text, "EOF");
    return currentToken;
}

void closeLexer() {
    if (sourceFile) fclose(sourceFile);
}
