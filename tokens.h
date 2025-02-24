#ifndef TOKENS_H
#define TOKENS_H

typedef enum {
    TOKEN_EOF,
    TOKEN_ID,
    TOKEN_NUM,
    TOKEN_ASSIGN,
    TOKEN_SYMBOL,
    TOKEN_KEYWORD,
    TOKEN_OPERATOR
} TokenType;

typedef struct {
    TokenType type;
    char text[64];
} Token;

#endif // TOKENS_H
