#include <stdio.h>
#include <stdlib.h>     /* malloc */
#include <string.h>
#include "lex.yy.c"     /* El Scanner */

char * comandos[] = {
    "pdflatex latex.tex",           // comando para generar el pdf
    "evince -f presentation.pdf"    // comando para abrir el pdf generado en pantalla completa
};

/* Ya definido dentro de flex_source.l
typedef enum {
    KEYWORD,
    IDENTIFIER,
    LITERAL,
    OPERATOR,
    PUNTUACTOR,
    COMMENT,
    LEXICALERROR
} TOKEN;
*/

char * colores[] = {
    "cyan",     // KEYWORD      0
    "white",    // IDENTIFIER   1
    "lime",     // LITERAL      2
    "yellow",   // OPERATOR     3
    "magenta",  // PUNTUACTOR    4
    "gray",     // COMMENT      5
    "NordRed"   // LEXICALERROR 6
};

/**
 * Para llevar un conteo de las veces que aparece el token y poder generar el histograma con los datos
 */
int histograma[] = {
    0,      // KEYWORD      0
    0,      // IDENTIFIER   1
    0,      // LITERAL      2
    0,      // OPERATOR     3
    0,      // PUNTUATOR    4
    0,      // COMMENT      5
    0       // LEXICALERROR 6
};

struct NodoToken {
    TOKEN token;
    char * lexema;  // Tamaño del lexema: guardado en yytext
    int size;       // Tamaño del lexema: guardado en yyleng
    struct NodoToken *sig;
};

/**
 * LISTA PARA ALMACENAR LOS TOKENS EN MEMORIA CON SU INFORMACIÓN
 */
struct NodoToken *ListaTokens = NULL;


char* getTipo(TOKEN token) {
    switch (token) {
        case KEYWORD:       return "KEYWORD";
        case IDENTIFIER:    return "IDENTIFIER";
        case LITERAL:       return "LITERAL";
        case OPERATOR:      return "OPERATOR";
        case PUNTUACTOR:    return "PUNTUATOR";
        case COMMENT:       return "COMMENT";
        default:            return "LEXICALERROR";
    }
}


void imprimir() {
    struct NodoToken *aux = ListaTokens;
    puts("-----------------------------------------------------");
    while(aux != NULL) {
        printf("Lexema: %s    |   Token: %s    |   Size:  %d \n", aux->lexema, getTipo(aux->token), aux->size);
        puts("-----------------------------------------------------");
        aux = aux->sig;
    }

    printf("\nHistograma:\n");
    printf("\n%s: %d", getTipo(0), histograma[0]);
    printf("\n%s: %d", getTipo(1), histograma[1]);
    printf("\n%s: %d", getTipo(2), histograma[2]);
    printf("\n%s: %d", getTipo(3), histograma[3]);
    printf("\n%s: %d", getTipo(4), histograma[4]);
    printf("\n%s: %d", getTipo(5), histograma[5]);
    printf("\n%s: %d\n", getTipo(6), histograma[6]);
}

void insertar(TOKEN tok, char *lex, int size) {

    struct NodoToken *nuevo = (struct NodoToken*) malloc(sizeof(struct NodoToken));
    nuevo->sig = NULL;

    nuevo->lexema = (char*) malloc(100); /* reserva memoria */
    strcpy(nuevo->lexema, lex);
    nuevo->token = tok;

    /* inserción en la lista */
    if (ListaTokens == NULL)
        ListaTokens = nuevo;
    else {
        struct NodoToken *aux = ListaTokens;

        while(aux->sig != NULL) {
            aux = aux->sig;
        }
        aux->sig = nuevo;
    }
}

/**
 * Each time your program calls yylex, it returns the next token (an integer token code).
 */
TOKEN getNextToken() {
    int tok = yylex();
    return tok;
}

void scanner() {
    TOKEN token;
    while(token = getNextToken() != 0) {
        insertar(token, yytext, yyleng);
        histograma[token] += 1; // Suma la aparicion del token
    }
}

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

    /* preproceso deberia crearme un nuevo file */

    // yylex reads from the file stored in variable yyin
    // It is up to you to open a file for reading and store it into yyin before you call yylex.
    extern FILE *yyin;

    /* open the source file in read mode */
    yyin = fopen(argv[1], "r");

    scanner();
    imprimir();

    // fclose(yyin);

    return 0;
}
