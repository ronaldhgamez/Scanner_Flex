%{
typedef enum {
    DIGIT, KEYWORD, ID, INTLITERAL, LPAREN, RPAREN, SEMICOLON, COMMA, OPERATOR, LEXICALERROR
} TOKEN;
%}

DIGIT   [0-9]
ID      [a-zA-Z][a-zA-Z0-9_]*

%%
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
out         return 1;

\(          printf("A LPAREN: %s (%d)", yytext, atoi(yytext));
\)          printf("A RPAREN: %s (%d)", yytext, atoi(yytext));
\,                       printf("A COMMA: %s (%d)", yytext, atoi(yytext));
\;                       printf("A SEMICOLON: %s (%d)", yytext, atoi(yytext));
\+|\-|\/|\*                 printf("A OPERATOR: %s (%d)", yytext, atoi(yytext));
\=\=|\!\=|\<|\>\=|\<\=        printf("A OPERATOR: %s (%d)", yytext, atoi(yytext));


{DIGIT}*    printf("A DIGIT: %s (%d)", yytext, atoi(yytext));
{ID}        printf("An ID: %s (%d)", yytext, atoi(yytext));

%%
int main(int argc, char** argv) {
	yylex();
	return 0;
}
