%{
typedef enum {
    ID, KEYWORD, OPERATOR, LITERALCONSTANT, LEXICALERROR
} TOKEN;
%}

	/* CONSTANTES: NUMEROS REALES */

/* Acepta hileras que pueden no tener numeros antes del punto decimal y que deben tener un numero despues del punto decimal. El e^n es opcional */
/* EJEMPLO:  -.2e+3  ,  +.4E12  ,  .3e-4  ,  -3.3e-4  ,   .56  */
CONST_REAL1	((\+?-?)|(-?\+?))?[0-9]*\.[0-9]+((e|E)(\+|-)?[0-9]+)?

/* Acepta hileras que deben tener un numero antes del punto decimal y que pueden pueden no traer un numero despues del punto decimal. El e^n es opcional */
/* EJEMPLO:  -3.e3  ,  +-22.32 ,  2.e+33  ,  0.e-1  ,  4.  */
CONST_REAL2

/* Constante real sin el punto decimal */
/* EJEMPLO:  -77e-3  ,  +-22e-3   ,  20  ,  -10  ,  3E3  ,   302E2   */
CONST_REAL3	((\+?-?)|(-?\+?))?[0-9]+((e|E)(\+|-)?[0-9]+)?

/* Numeros en base 8 */
OCTAL		0[0-7]{1,11}
/* Números en base 16*/
HEXADECIMAL	0(X|x)[0-9A-Fa-f]+
/* Secuencia de letras, digitos, y underscores. Primer caracter no puede ser digito */
ID      	_*[a-zA-Z][a-zA-Z0-9_]*

/* Comments */
COMMENT		\/*\*(.|\s)*\*\/
/* No admite line breaks */
NORMALCOM	\/{2,}.*	

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

	/* KEYWORDS */
auto        printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
break       printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
case        printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
char        printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
const       printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
continue    printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
default     printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
do          printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
double      printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
else        printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
enum        printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
extern      printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
float       printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
for         printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
goto        printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
if          printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
inline      printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
int         printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
long        printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
register    printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
restrict    printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
return      printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
short       printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
signed		printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
sizeof		printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
static		printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
struct		printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
switch		printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
typedef		printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
union		printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
unsigned	printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
void		printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
volatile	printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
while		printf("A KEYWORD: %s (%d)", yytext, atoi(yytext));
	/* EXIT */
out         return 1;

	/* Identificadores: PD: se valida despues de las palabras reservadas */
{ID}       		printf("An ID: %s (%d)", yytext, atoi(yytext));

	/* Numeros reales */
{CONST_REAL1}|{CONST_REAL2}|{CONST_REAL3}		printf("A constant REALES: %s (%d)", yytext, atoi(yytext));

	/* Comentarios */
{COMMENT}|{NORMALCOM} 	printf("A fucking comment: %s (%d)", yytext, atoi(yytext));

	/* Operadores del lenguaje */
{ARITHMETIC}	printf("AN Arithmetic OPERATOR: %s (%d)", yytext, atoi(yytext));
{ASSIGNMENT}	printf("AN ASSIGNMENT OPERATOR: %s (%d)", yytext, atoi(yytext));
{COMPARISON}	printf("A COMPARISON OPERATOR: %s (%d)", yytext, atoi(yytext));
{INC_DRE}		printf("AN INCDRE OPERATOR: %s (%d)", yytext, atoi(yytext));
{LOGICAL}		printf("A LOGICAL OPERATOR: %s (%d)", yytext, atoi(yytext));
{OTHERS}		printf("OTHER OPERATOR: %s (%d)", yytext, atoi(yytext));
{ACCESS}		printf("AN ACCESS OPERATOR: %s (%d)", yytext, atoi(yytext));


.				printf("Lexical error: %s (%d)", yytext, atoi(yytext));

%%
int main(int argc, char** argv) {
	yylex();
	return 0;
}
