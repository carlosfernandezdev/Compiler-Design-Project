#include "analizador_lexico.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char *input;
Token currentToken;

void initLexer(const char *source) {
    input = source;
    nextToken();
}

void nextToken() {
    while (*input == ' ') input++;

    if (isdigit(*input)) { 
        int i = 0;
        while (isdigit(*input)) currentToken.text[i++] = *input++;
        currentToken.text[i] = '\0';
        currentToken.type = TOKEN_NUM;
        return;
    }

    if (isalpha(*input)) { 
        int i = 0;
        while (isalnum(*input)) currentToken.text[i++] = *input++;
        currentToken.text[i] = '\0';

        if (strcmp(currentToken.text, "begin") == 0) currentToken.type = TOKEN_BEGIN;
        else if (strcmp(currentToken.text, "end") == 0) currentToken.type = TOKEN_END;
        else if (strcmp(currentToken.text, "if") == 0) currentToken.type = TOKEN_IF;
        else if (strcmp(currentToken.text, "while") == 0) currentToken.type = TOKEN_WHILE;
        else if (strcmp(currentToken.text, "var") == 0) currentToken.type = TOKEN_VAR;
        else currentToken.type = TOKEN_ID;
        return;
    }

    if (*input == ':') { 
        if (*(input + 1) == '=') {
            strcpy(currentToken.text, ":=");
            currentToken.type = TOKEN_ASSIGN;
            input += 2;
            return;
        }
    }

    if (*input == ';') { 
        currentToken.text[0] = *input++;
        currentToken.text[1] = '\0';
        currentToken.type = TOKEN_SEMICOLON;
        return;
    }

    currentToken.type = TOKEN_EOF;
}

Token getCurrentToken() {
    return currentToken;
}