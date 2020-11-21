#include <stdio.h>
#include <stdlib.h>     /* malloc */
#include <string.h>
#include "lex.yy.c"     /* El Scanner */

/* Ya definido dentro de lex.yy.c
typedef enum {
    KEYWORD,
    IDENTIFIER,
    LITERAL,
    OPERATOR,
    PUNTUACTOR,
    COMMENT,
    LEXICALERROR,
    PREPROCESSOR
} TOKEN;
*/

char * colores[] = {
    "cyan",     // KEYWORD      0
    "white",    // IDENTIFIER   1
    "green",    // LITERAL      2
    "yellow",   // OPERATOR     3
    "magenta",  // PUNTUACTOR    4
    "gray",     // COMMENT      5
    "red",      // LEXICALERROR 6
    "orange"    // PREPROCESSOR 7
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
    0,      // LEXICALERROR 6
    0       // PREPROCESSOR 7
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
        case KEYWORD:           return "KEYWORD";
        case IDENTIFIER:        return "IDENTIFIER";
        case LITERAL:           return "LITERAL";
        case OPERATOR:          return "OPERATOR";
        case PUNTUACTOR:        return "PUNTUATOR";
        case COMMENT:           return "COMMENT";
        case PREPROCESSOR:      return "PREPROCESSOR";
        default:                return "LEXICALERROR";
    }
}

void imprimir() {
    struct NodoToken *aux = ListaTokens;
    puts("-----------------------------------------------------");
    while(aux != NULL) {
        printf("Token: %s    |   Lexema: %s    |   Size:  %d \n", getTipo(aux->token), aux->lexema, aux->size);
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
    printf("\n%s: %d", getTipo(6), histograma[6]);
    printf("\n%s: %d", getTipo(7), histograma[7]);
    printf("\n\n");
}

void insertar(TOKEN tok, char *lex, int size) {

    struct NodoToken *nuevo = (struct NodoToken*) malloc(sizeof(struct NodoToken));
    nuevo->sig = NULL;

    nuevo->token = tok;
    nuevo->size = size;
    nuevo->lexema = (char*)malloc(strlen(lex) * sizeof(char));
    // nuevo->lexema = (char*) malloc(1); /* reserva memoria */
    //nuevo->lexema = (char*)malloc(sizeof(char)*50);
    //nuevo->lexema = (char*)calloc(strlen(lex), sizeof(char));
    //strcpy(nuevo->lexema, lex);
    nuevo->lexema = lex;

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

// You must free the result if result is non-NULL.
char *str_replace(char *orig, char *rep, char *with) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    // sanity checks and initialization
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}

// Remplaza cualquier caractares especial de LaTex para poderlo imprimir en beamer
char *preparar(char *str) {
    str = str_replace(str, "\\", "\\textbackslash "); // Debe ser primero para evitar errores
    str = str_replace(str, "{", "\\{");
    str = str_replace(str, "}", "\\}");
    str = str_replace(str, "&", "\\&");
    str = str_replace(str, "%", "\\%");
    str = str_replace(str, "$", "\\$");
    str = str_replace(str, "#", "\\#");
    str = str_replace(str, "_", "\\_");
    str = str_replace(str, "~", "\\textasciitilde ");
    str = str_replace(str, "^", "\\textasciicircum ");
    return str;
}

/**
 * Each time your program calls yylex, it returns the next token (an integer token code).
 */
TOKEN getNextToken() {
    int tok = yylex();
    return tok;
}

void scanner() {
    TOKEN token = getNextToken();
    while(token != EOF) {
        
        // Remplaza cualquier caractares especial de LaTex para poderlo imprimir en beamer
        char *lexema = preparar(yytext);

        // yylen: Longitud del lexema
        insertar(token, lexema, yyleng);
        histograma[token] += 1; // Suma la aparicion del token
        token = getNextToken();
    }
}

/**
 * Se encarga de generar el fuente latex para mostrar el histograma.
 * Utiliza los datos del arreglo histograma[]
 */
void fuenteLatex() {

    FILE * temp;
    temp = fopen ("histograma.tex", "w"); // Genera el archivo
    

    // GENERAR SLIDES CON EL CODIGO
    fprintf(temp, "\\justifying \\small \n\n");

    struct NodoToken *aux = ListaTokens;
    ////int i = 1;
    while(aux != NULL) {
        // \textcolor{Aqui va el Color}{Aquí va el Texto}
        fprintf(temp, "\\textcolor{%s}{%s} ", colores[aux->token], aux->lexema);
        ////if(i == 4) {
            fprintf(temp, "\n");
            ///i = 0;
        ////}
        ///i++;
        aux = aux->sig;
    }

    fprintf(temp, "\n\n");

    
    // Codigo del histograma
    fprintf(temp, "\n\n");
    fprintf(temp, "\\begin{frame}{Histograma Tokens Usados} \n");
    fprintf(temp, "\\begin{tikzpicture}[scale=0.75] %% tamaño \n");
    fprintf(temp, "\\begin{axis}[xbar,tick align=outside, \n");
    fprintf(temp, "    width=12.5cm,       %% largo \n");
    fprintf(temp, "    height=9cm,       %% altura \n");
    fprintf(temp, "    bar width={13pt},   %% grosor linea \n");
    fprintf(temp, "    enlargelimits=0.08, %% cercania a linea \n");
    fprintf(temp, "    nodes near coords, \n");
    fprintf(temp, "    nodes near coords align=horizontal, \n");
    fprintf(temp, "    point meta=x * 1, %% The displayed number. \n");
    fprintf(temp, "    xlabel=\\textbf{Frecuencia de Tokens usados}, \n");
    fprintf(temp, "    ytick={0,...,7}, \n");
    fprintf(temp, "    yticklabels={ \n");
    fprintf(temp, "        \\textcolor{cyan}{\\textbf{KEYWORD}},         %% POSITION 0 \n");
    fprintf(temp, "        \\textcolor{white}{\\textbf{IDENTIFIER}},     %% POSITION 1 \n");
    fprintf(temp, "        \\textcolor{green}{\\textbf{LITERAL}},        %% POSITION 2 \n");
    fprintf(temp, "        \\textcolor{yellow}{\\textbf{OPERATOR}},      %% POSITION 3 \n");
    fprintf(temp, "        \\textcolor{magenta}{\\textbf{PUNTUACTOR}},   %% POSITION 4 \n");
    fprintf(temp, "        \\textcolor{gray}{\\textbf{COMMENT}},         %% POSITION 5 \n");
    fprintf(temp, "        \\textcolor{red}{\\textbf{LEXICALERROR}},     %% POSITION 6 \n");
    fprintf(temp, "        \\textcolor{orange}{\\textbf{PREPROCESSOR}}   %% POSITION 7 \n");
    fprintf(temp, "    }] \n");
    fprintf(temp, "\\addplot \n");
    fprintf(temp, "[draw=teal,fill=teal!75] \n");
    fprintf(temp, "coordinates {(%d,0) (%d,1) (%d,2) (%d,3) (%d,4) (%d,5) (%d,6) (%d,7)}; \n", histograma[0], 
    histograma[1], histograma[2], histograma[3], histograma[4], histograma[5], histograma[6], histograma[7]);
    fprintf(temp, "\\end{axis}\n");
    fprintf(temp, "\\end{tikzpicture}\n");
    fprintf(temp, "\\end{frame}\n");
    
    fclose (temp);
}

int main(int argc, char** argv) {
    
    if (argc == 1) {
        printf("\nAviso: No se ha recibido ningun fuente de C desde la linea de comandos. Ingrese un fuente para comenzar el analisis.\n\n");
        return -1;
    }

    // hacer preproceso
    int preproceso = 0;
    if (argc > 2) {
        if(argv[2] == "p")
            preproceso = 1; // Para enviar el archivo a preproceso
        else {
            printf("\nComando %s no valido.\n\n", argv[2]);
            return -1;
        }
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
    fuenteLatex();
    fclose(yyin);

    // comando para generar el pdf
    system("pdflatex latex.tex");
    // Elimina archivos temporales basura
    system("rm histograma.aux latex.aux latex.log");
    system("rm latex.nav latex.out latex.snm latex.toc");

    imprimir();

    // abrir el PDF generado en pantalla completa
    system("evince latex.pdf");
    

    return 0;
}
