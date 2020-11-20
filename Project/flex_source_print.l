%{
typedef enum {
    KEYWORD,
    IDENTIFIER,
    LITERAL,
    OPERATOR,
    PUNTUACTOR,
    COMMENT,
    LEXICALERROR
} TOKEN;
%}

/* Cualquier caracter en blanco (tabs, salto linea, espacios)*/
/* si le mando s es white espace?*/
WHITESPACE 	[ \t]*

	/* CONSTANTES */

/* Acepta hileras que pueden no tener numeros antes del punto decimal y que deben tener un numero despues del punto decimal. El e^n es opcional */
/* EJEMPLO:  -.2e+3  ,  +.4E12  ,  .3e-4  ,  -3.3e-4  ,   .56  */
CONST_REAL1	((\+?-?)|(-?\+?))?[0-9]*\.[0-9]+((e|E)(\+|-)?[0-9]+)?

/* Acepta hileras que deben tener un numero antes del punto decimal y que pueden pueden no traer un numero despues del punto decimal. El e^n es opcional */
/* EJEMPLO:  -3.e3  ,  +-22.32 ,  2.e+33  ,  0.e-1  ,  4.  */
CONST_REAL2 ((\+?-?)|(-?\+?))?[0-9]+\.[0-9]*((e|E)(\+|-)?[0-9]+)?

/* Constante real sin el punto decimal */
/* EJEMPLO:  -77e-3  ,  +-22e-3   ,  20  ,  -10  ,  3E3  ,   302E2   */
CONST_REAL3	((\+?-?)|(-?\+?))?[0-9]+((e|E)(\+|-)?[0-9]+)?

/* Numeros en base 8. Comienzan con 0 seguido de numeros entre 1-7. Longitud de 12 */
OCTAL		^(0[0-7]{1,11})$

/* Base 16: Comienzan con 0x o 0X seguido de uno o mas numeros del 0-9 o de a-f */
HEXADECIMAL	^(0(X|x)[0-9a-fA-F]+)$

/* Secuencia de letras, digitos, y underscores. Primer caracter no puede ser digito. Puede nombrarse "_" solamente. */
ID      	(_*[a-zA-Z]|_[0-9a-zA-Z]*)[a-zA-Z0-9_]*

/* Caracteres especiales: Secuencias de escape (digitos octales y hexadecimales) */
SPECIAL		(\\(a|b|f|n|r|t|v|\\|\'|\"|\?|0|x[0-9][0-9]|[0-3][0-7][0-7]|[0-7][0-7]?))
/* Caracter Simple: 'C' */
CHAR		'([^\\']|{SPECIAL})'
/* Cadena de caracteres: "Secuencia de caracteres" */
CHARS		\"([^\"\\]|\\{2}|{SPECIAL})*\"

	/* Comments */
	/* funciona enviandole desde consola todo el archivo \/+\*((\**[^\/])|(\**(\n)\/*))*\*\/+    */ 
	/* para pruebas \/*\*(.)*\*\/+ */
COMMENT1		\/+\*((\**[^\/])|(\**(\n)\/*))*\*\/+

/* Comentario normal: // No admite line breaks */
COMMENT2		\/{2,}.*

/* Arithmetic Operators */
ARITHMETIC \+|-|\*|\/|%|~|&|\||\^|<<|>>

/* Assignment Operators */
ASSIGNMENT =|\+=|-=|\*=|\/=|%=|&=|\|=|\^=|<<=|>>=

/* Comparison Operators */
COMPARISON ==|!=|<|>|>=|<=

/* Increment and decrement operators */
INC_DRE		\+\+|--

/* Logical operators */
LOGICAL		!|&&|\|\|

/* PUNTUACTOR OPERATORS */
PUNTUACTORS		\{|<%|\}|%>|\(|\)|\[|<:|\]|:>|,|;|\.\.\.|#|:|\?

/* Member access operators */
ACCESS		\.|->

%%
	/* Caracteres Blancos printf("WHITESPACE \"%s\"\n", yytext); */
	
{WHITESPACE}	/* Ignora espacios en blanco */

	/* Comentarios */
{COMMENT1}|{COMMENT2} 	printf("COMMENT: \"%s\"\n", yytext);

	/* KEYWORDS */
auto        printf("KEYWORD: \"%s\"\n", yytext);
break       printf("KEYWORD: \"%s\"\n", yytext);
case        printf("KEYWORD: \"%s\"\n", yytext);
char        printf("KEYWORD: \"%s\"\n", yytext);
const       printf("KEYWORD: \"%s\"\n", yytext);
continue    printf("KEYWORD: \"%s\"\n", yytext);
default     printf("KEYWORD: \"%s\"\n", yytext);
do          printf("KEYWORD: \"%s\"\n", yytext);
double      printf("KEYWORD: \"%s\"\n", yytext);
else        printf("KEYWORD: \"%s\"\n", yytext);
enum        printf("KEYWORD: \"%s\"\n", yytext);
extern      printf("KEYWORD: \"%s\"\n", yytext);
float       printf("KEYWORD: \"%s\"\n", yytext);
for         printf("KEYWORD: \"%s\"\n", yytext);
goto        printf("KEYWORD: \"%s\"\n", yytext);
if          printf("KEYWORD: \"%s\"\n", yytext);
inline      printf("KEYWORD: \"%s\"\n", yytext);
int         printf("KEYWORD: \"%s\"\n", yytext);
long        printf("KEYWORD: \"%s\"\n", yytext);
register    printf("KEYWORD: \"%s\"\n", yytext);
restrict    printf("KEYWORD: \"%s\"\n", yytext);
return      printf("KEYWORD: \"%s\"\n", yytext);
short       printf("KEYWORD: \"%s\"\n", yytext);
signed		printf("KEYWORD: \"%s\"\n", yytext);
sizeof		printf("KEYWORD: \"%s\"\n", yytext);
static		printf("KEYWORD: \"%s\"\n", yytext);
struct		printf("KEYWORD: \"%s\"\n", yytext);
switch		printf("KEYWORD: \"%s\"\n", yytext);
typedef		printf("KEYWORD: \"%s\"\n", yytext);
union		printf("KEYWORD: \"%s\"\n", yytext);
unsigned	printf("KEYWORD: \"%s\"\n", yytext);
void		printf("KEYWORD: \"%s\"\n", yytext);
volatile	printf("KEYWORD: \"%s\"\n", yytext);
while		printf("KEYWORD: \"%s\"\n", yytext);

	/* Identificadores: PD: se valida despues de las palabras reservadas */
{ID}       		printf("ID: \"%s\"\n", yytext);

{CHARS}			printf("CHARS: \"%s\"\n", yytext);
{CHAR}			printf("CHAR: \"%s\"\n", yytext);

	/* OCTAL */
{OCTAL}			printf("OCTAL: \"%s\"\n", yytext);

	/* HEXADECIMAL */
{HEXADECIMAL}	printf("HEXADECIMAL: \"%s\"\n", yytext);

	/* Numeros reales */
{CONST_REAL1}		printf("REAL1: \"%s\"\n", yytext);
{CONST_REAL2}		printf("REAL2: \"%s\"\n", yytext);
{CONST_REAL3}		printf("REAL3: \"%s\"\n", yytext);

	/* Operadores del lenguaje */
{ARITHMETIC}	printf("Arithmetic OPERATOR: \"%s\"\n", yytext);
{ASSIGNMENT}	printf("ASSIGNMENT OPERATOR: \"%s\"\n", yytext);
{COMPARISON}	printf("COMPARISON OPERATOR: \"%s\"\n", yytext);
{INC_DRE}		printf("INCDRE OPERATOR: \"%s\"\n", yytext);
{LOGICAL}		printf("LOGICAL OPERATOR: \"%s\"\n", yytext);
{PUNTUACTORS}	printf("PUNTUACTORS: \"%s\"\n", yytext);
{ACCESS}		printf("ACCESS OPERATOR: \"%s\"\n", yytext);
	
	/* ERRORES LEXICOS */
	/*.				printf("LEXICALERROR: \"%s\"\n", yytext); */

%%


int main(int argc, char** argv) {
	extern FILE *yyin;

    /* open the source file in read mode */
    yyin = fopen(argv[1], "r"); 
    
	yylex();
	return 0;
}


int yywrap() {
    return 1; 
}
