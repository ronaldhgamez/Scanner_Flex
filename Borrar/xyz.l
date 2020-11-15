digit [0-9]
letter [a-zA-Z]
%%
{letter}({letter}|{digit})*	printf("id: %s\n", yytext);
{digit}({digit})*		printf("digit: %s\n", yytext);
\n				printf("new line\n");
%%
int main(int argc, char** argv) {
	yylex();
	return 0;
}
