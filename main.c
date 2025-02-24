#include "analizador_lexico.h"
#include "analizador_sintactico.h"
#include "ast.h"
#include <stdio.h>
#include <string.h>


extern Token currentToken;

int main() {
    char ruta[256];

    printf("Ingrese la ruta del archivo .pas: ");
    fgets(ruta, sizeof(ruta), stdin);
    ruta[strcspn(ruta, "\n")] = 0;

    initLexer(ruta);
    nextToken();

    while (currentToken.type != TOKEN_EOF) {
        ASTNode *ast = parseStatement();
        if (ast) {
            // Imprimir AST si es necesario
        } else {
            printf("Error al analizar el código.\n");
            break;
        }
    }

    closeLexer();
    return 0;
}
