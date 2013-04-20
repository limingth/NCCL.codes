%{
	int lines = 0;
	int words = 0;
	int chars = 0;
%}

%%
[\n]	{ chars++; words++; lines++; printf("lines %d: \n", lines); }
[ ]	{ chars++; words++; }
.	{ chars++; }
%%

int main(void)
{
	yylex();

	printf("chars: %d, words: %d, lines: %d\n", chars, words, lines);

	return 0;
}
