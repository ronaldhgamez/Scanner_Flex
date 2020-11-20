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
{COMMENT1}|{COMMENT2} 	return COMMENT;

	/* KEYWORDS */
auto        			return KEYWORD;
break       			return KEYWORD;
case        			return KEYWORD;
char        			return KEYWORD;
const       			return KEYWORD;
continue    			return KEYWORD;
default     			return KEYWORD;
do          			return KEYWORD;
double      			return KEYWORD;
else        			return KEYWORD;
enum        			return KEYWORD;
extern      			return KEYWORD;
float       			return KEYWORD;
for         			return KEYWORD;
goto        			return KEYWORD;
if          			return KEYWORD;
inline      			return KEYWORD;
int         			return KEYWORD;
long        			return KEYWORD;
register    			return KEYWORD;
restrict    			return KEYWORD;
return      			return KEYWORD;
short       			return KEYWORD;
signed					return KEYWORD;
sizeof					return KEYWORD;
static					return KEYWORD;
struct					return KEYWORD;
switch					return KEYWORD;
typedef					return KEYWORD;
union					return KEYWORD;
unsigned				return KEYWORD;
void					return KEYWORD;
volatile				return KEYWORD;
while					return KEYWORD;

	/* Identificadores: PD: se valida despues de las palabras reservadas */
{ID}       				return IDENTIFIER;

{CHARS}					return LITERAL;
{CHAR}					return LITERAL;

	/* OCTAL */
{OCTAL}					return LITERAL;

	/* HEXADECIMAL */
{HEXADECIMAL}			return LITERAL;

	/* Numeros reales */
{CONST_REAL1}			return LITERAL;
{CONST_REAL2}			return LITERAL;
{CONST_REAL3}			return LITERAL;

	/* Operadores del lenguaje */
{ARITHMETIC}			return OPERATOR;
{ASSIGNMENT}			return OPERATOR;
{COMPARISON}			return OPERATOR;
{INC_DRE}				return OPERATOR;
{LOGICAL}				return OPERATOR;
{PUNTUACTORS}			return PUNTUACTOR;
{ACCESS}				return OPERATOR;

<<EOF>>					return EOF;

	/* ERRORES LEXICOS */
	/*.*				return LEXICALERROR; */
%%

/**
 * When yylex is finished, it call function yywrap(). If yywrap() returns 1, then yylex returns 0 to its caller. That means "end of file".
 * If yywrap returns 0, then yylex assumes that you have stored a different file into yyin, and it starts reading that file.
 */
int yywrap() {
    return 1; 
}
