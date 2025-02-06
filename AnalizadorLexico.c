#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LENGTH 100

typedef struct {
    char type[50];
    char value[MAX_TOKEN_LENGTH];
    int lineNumber;
} Token;

void analyzeFile(const char *filePath);
void analyzeLine(const char *line, int lineNumber);
char *getTokenType(const char *token);

const char *KEYWORDS[] = {"program", "begin", "end", "var", "integer", "real", "boolean", "if", "then", "else", "while", "do", "for", "to", "downto", "repeat", "until", "procedure", "function"};
const int KEYWORDS_COUNT = 18;

void analyzeFile(const char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (!file) {
        printf("Error: No se pudo abrir el archivo.\n");
        return;
    }
    
    char line[256];
    int lineNumber = 1;
    while (fgets(line, sizeof(line), file)) {
        if (strlen(line) > 1) {
            printf("Línea %d: %s", lineNumber, line);
            analyzeLine(line, lineNumber);
        }
        lineNumber++;
    }
    fclose(file);
}

void analyzeLine(const char *line, int lineNumber) {
    char token[MAX_TOKEN_LENGTH];
    int i = 0, j = 0;
    
    while (line[i] != '\0') {
        if (isalnum(line[i]) || line[i] == '_') {
            token[j++] = line[i];
        } else {
            if (j > 0) {
                token[j] = '\0';
                char *type = getTokenType(token);
                printf("  → Token: %s | Tipo: %s\n", token, type);
                j = 0;
            }
            if (!isspace(line[i])) {
                printf("  → Token: %c | Tipo: Símbolo\n", line[i]);
            }
        }
        i++;
    }
}

char *getTokenType(const char *token) {
    for (int i = 0; i < KEYWORDS_COUNT; i++) {
        if (strcmp(token, KEYWORDS[i]) == 0) {
            return "Palabra Clave";
        }
    }
    if (isdigit(token[0])) return "Número";
    return "Identificador";
}

int main() {
    char filePath[256];
    printf("Ingrese la ruta del archivo Pascal: ");
    scanf("%255s", filePath);
    analyzeFile(filePath);
    return 0;
}
