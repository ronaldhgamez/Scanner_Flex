%{
typedef enum {
    ID, KEYWORD,
	 LPAREN, RPAREN, SEMICOLON, COMMA, OPERATOR, LEXICALERROR
} TOKEN;
%}

/* CONSTANTESS */
DIGIT	[0-9]
INT		[-+]?DIGIT*
/* PUEDE NO TENER PUNTO DECIMAL */
FLOAT	[+-]?[0-9]+(\.[0-9]+)*

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
OTHERS		{|<%|}|%>|\(|\)|\?|:

/* Member access operators */
ACCESS		\[|<:|\]|:>|\.|->

/* Secuencia de letras, digitos, y underscores. Primer caracter no puede ser digito */
ID      _*[a-zA-Z][a-zA-Z0-9_]*

%%

/*	Keywords: taken from "https://devdocs.io/c/keyword" */
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

out         return 1;

\(          printf("A LPAREN: %s (%d)", yytext, atoi(yytext));
\)          printf("A RPAREN: %s (%d)", yytext, atoi(yytext));
\,                       printf("A COMMA: %s (%d)", yytext, atoi(yytext));
\;                       printf("A SEMICOLON: %s (%d)", yytext, atoi(yytext));
\+|\-|\/|\*                 printf("A OPERATOR: %s (%d)", yytext, atoi(yytext));
{OPERADORES}       printf("A OPERATOR: %s (%d)", yytext, atoi(yytext));

/* Contantes */


{DIGIT}*    printf("A DIGIT: %s (%d)", yytext, atoi(yytext));

{ID}        printf("An ID: %s (%d)", yytext, atoi(yytext));
{FLOAT}		printf("A FLOAT: %s (%d)", yytext, atoi(yytext));
{ARITHMETIC}	printf("AN Arithmetic OPERATOR: %s (%d)", yytext, atoi(yytext));
{ASSIGNMENT}	printf("AN ASSIGNMENT OPERATOR: %s (%d)", yytext, atoi(yytext));
{COMPARISON}	printf("AN COMPARISON OPERATOR: %s (%d)", yytext, atoi(yytext));
{INC_DRE}		printf("AN INCDRE OPERATOR: %s (%d)", yytext, atoi(yytext));

%%
int main(int argc, char** argv) {
	yylex();
	return 0;
}
