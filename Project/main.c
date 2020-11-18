#include <stdio.h>
#include <stdlib.h>     /* malloc */
#include <string.h>
// #include "lex.yy.c"     /* El Scanner */

char * comandos[] = {
    "pdflatex latex.tex",           // comando para generar el pdf
    "evince -f presentation.pdf"    // comando para abrir el pdf generado en pantalla completa
};

typedef enum {
    KEYWORD,
    IDENTIFIER,
    LITERAL,
    OPERATOR,
    PUNTUATOR,
    COMMENT,
    LEXICALERROR
} TOKEN;

char * colores[] = {
    "cyan",     // KEYWORD      0
    "white",    // IDENTIFIER   1
    "lime",     // LITERAL      2
    "yellow",   // OPERATOR     3
    "magenta",  // PUNTUATOR    4
    "gray",     // COMMENT      5
    "NordRed"   // LEXICALERROR 6
};

typedef struct {
    TOKEN token;
    char * lexema;
} REG_EXPRESSION;


int main(int argc, char** argv) {
    
    if (argc == 1) {
        printf("\nAviso: No se ha recibido ningun fuente de C desde la linea de comandos. Ingrese un fuente para comenzar el analisis.\n\n");
        return -1;
    }
    if (argc != 2) {
        printf("\nIngrese solo el nombre del archivo C.\n\n");
        return -1;
    }

    // Copia del nombre del archivo
    char *nameFile = (char*) malloc(100);
    strcpy(nameFile, argv[1]);
    int size = strlen(nameFile);

    // WRONG BY TYPE (.c)
    if (nameFile[size - 1] != 'c' || nameFile[size - 2] != '.') {
        printf("\nError: El nombre del archivo ingresado no es un fuente del lenguaje C. Intente nuevamente.\n\n");
        return -1;
    }

    FILE * file;
    if ((file = fopen(nameFile, "r")) == NULL) {
        printf("\nError: El archivo con nombre %s no existe. Intente nuevamente.\n\n", nameFile);
        return -1;
    }

    fclose(file);

    printf("\nfuente: \"%s\"", nameFile);
    printf("\ncant: \"%d\"", size);

    return 0;
}
