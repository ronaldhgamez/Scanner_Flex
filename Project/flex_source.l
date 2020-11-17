%{
typedef enum {
    ID, KEYWORD, OPERATOR, LITERALCONSTANT, COMMENT, STRINGLITERAL, CHAR,
	PUNTUATOR, CHARCONSTANT, WHITESPACE, LEXICALERROR
} TOKEN;
%}

/* Cualquier caracter en blanco (tabs, salto linea, espacios)*/
/* si le mando s es white espace?*/
WHITESPACE 	\s+

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
OCTAL		0[0-7]{1,11}

/* Base 16: Comienzan con 0x o 0X seguido de uno o mas numeros del 0-9 o de a-f */
HEXADECIMAL	0(X|x)[0-9a-fA-F]+

/* Secuencia de letras, digitos, y underscores. Primer caracter no puede ser digito. Puede nombrarse "_" solamente. */
ID      	(_*[a-zA-Z]|_[0-9a-zA-Z]*)[a-zA-Z0-9_]*

/* Caracter */
CHAR		'([^\\]|(\\(n|t|r|b|0|'|\\)))'
/* Cadena de caracteres */
CHARS		\"([^\"\\]|\\{2}||(\\(n|t|r|b|0|'|\\)))*\"
	
	/* Comments */
COMMENT1		\/*\*(.|\s)*\*\/

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

/* OTHER OPERATORS */
OTHERS		\{|<%|\}|%>|\(|\)|\?|:

/* Member access operators */
ACCESS		\[|<:|\]|:>|\.|->

%%
	/* Caracteres Blancos */
{WHITESPACE}	/* Ignora espacios en blanco */

	/* Comentarios */
{COMMENT1}|{COMMENT2} 	printf("\nA fucking comment: %s (%d)", yytext, atoi(yytext));

	/* KEYWORDS */
auto        printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
break       printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
case        printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
char        printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
const       printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
continue    printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
default     printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
do          printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
double      printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
else        printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
enum        printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
extern      printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
float       printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
for         printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
goto        printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
if          printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
inline      printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
int         printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
long        printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
register    printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
restrict    printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
return      printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
short       printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
signed		printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
sizeof		printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
static		printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
struct		printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
switch		printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
typedef		printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
union		printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
unsigned	printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
void		printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
volatile	printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
while		printf("\nA KEYWORD: %s (%d)", yytext, atoi(yytext));
	/* EXIT */
out         return 1;

	/* Identificadores: PD: se valida despues de las palabras reservadas */
{ID}       		printf("\nAn ID: %s (%d)", yytext, atoi(yytext));

	/*{CHAR}			printf("A CHAR: %s (%d)", yytext, atoi(yytext));
	{CHARS}			printf("A STRING OF CHARS: %s (%d)", yytext, atoi(yytext));*/

	/* OCTAL */
{OCTAL}			printf("\nAN OCTAL NUMBER: %s (%d)", yytext, atoi(yytext));

	/* HEXADECIMAL */
{HEXADECIMAL}	printf("\nAN HEXADECIMAL NUMBER: %s (%d)", yytext, atoi(yytext));

	/* Numeros reales */
{CONST_REAL1}|{CONST_REAL2}|{CONST_REAL3}		printf("A constant REALES: %s (%d)", yytext, atoi(yytext));

	/* Operadores del lenguaje */
{ARITHMETIC}	printf("\nAN Arithmetic OPERATOR: %s (%d)", yytext, atoi(yytext));
{ASSIGNMENT}	printf("\nAN ASSIGNMENT OPERATOR: %s (%d)", yytext, atoi(yytext));
{COMPARISON}	printf("\nA COMPARISON OPERATOR: %s (%d)", yytext, atoi(yytext));
{INC_DRE}		printf("\nAN INCDRE OPERATOR: %s (%d)", yytext, atoi(yytext));
{LOGICAL}		printf("\nA LOGICAL OPERATOR: %s (%d)", yytext, atoi(yytext));
{OTHERS}		printf("\nOTHER OPERATOR: %s (%d)", yytext, atoi(yytext));
{ACCESS}		printf("\nAN ACCESS OPERATOR: %s (%d)", yytext, atoi(yytext));


	/* .				printf("\nLexical error: %s (%d)", yytext, atoi(yytext));*/

%%

int main(int argc, char** argv) {
	extern FILE *yyin, *yyout;

    /* open the source file in read mode */
    yyin = fopen(argv[1], "r"); 
  	
	/* open the output file in write mode */
    yyout=fopen("output.txt","w"); 
    
	yylex();
	return 0;
}

int yywrap() {
    return 1; 
}
