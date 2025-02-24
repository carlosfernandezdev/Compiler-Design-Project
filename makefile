CC = gcc
CFLAGS = -Wall -Wextra

all: compiler

compiler: analizador_lexico.o analizador_sintactico.o ast.o main.o
	$(CC) $(CFLAGS) -o compiler analizador_lexico.o analizador_sintactico.o ast.o main.o

analizador_lexico.o: analizador_lexico.c analizador_lexico.h
	$(CC) $(CFLAGS) -c analizador_lexico.c

analizador_sintactico.o: analizador_sintactico.c analizador_sintactico.h analizador_lexico.h ast.h
	$(CC) $(CFLAGS) -c analizador_sintactico.c

ast.o: ast.c ast.h
	$(CC) $(CFLAGS) -c ast.c

main.o: main.c analizador_lexico.h analizador_sintactico.h ast.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o compiler
