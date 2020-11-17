#include <stdio.h>
#include "lex.yy.c"     /* El Scanner */

char * comandos[] = {
    "pdflatex latex.tex",           // comando para generar el pdf
    "evince -f presentation.pdf"    // comando para abrir el pdf generado en pantalla completa
};

typedef enum {
    ID, 
    KEYWORD, 
    OPERATOR, 
    LITERALCONSTANT, 
    COMMENT, 
    STRINGLITERAL, 
    CHAR,
	PUNTUATOR, 
    CHARCONSTANT, 
    WHITESPACE, 
    LEXICALERROR
} TOKEN;

/* Colores para cada tipo de token */
char * colores[] = {
    "NordBlue", 
    "NordOrange",       // palabras reservadas
    "NordGreen",        // para strings
    "NordYellow",
    "NordMagenta",
    "NordWhite",
    "NordBrightBlack",  // Comentarios
    "NordBrightCyan",
    "NordRed",
    "NordMagenta"
};

int main(int argc, char** argv) {

    return 0;
}
