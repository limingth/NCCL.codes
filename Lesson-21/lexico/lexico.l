%option noyywrap
%{
  int i = 0;
  int chars = 1;
  int lines = 1;
%}

%%
[\n] { lines++; chars = 1; } 

"void"    { printf("VOID\n")    ;  chars += strlen(yytext); }
"int"     { printf("INT\n")     ;  chars += strlen(yytext); }
"char"    { printf("CHAR\n")    ;  chars += strlen(yytext); }
"return"  { printf("RETURN\n")  ;  chars += strlen(yytext); }
"break"   { printf("BREAK\n")   ;  chars += strlen(yytext); }
"switch"  { printf("SWITCH\n")  ;  chars += strlen(yytext); }
"case"    { printf("CASE\n")    ;  chars += strlen(yytext); }
"default" { printf("DEFAULT\n") ;  chars += strlen(yytext); }
"do"      { printf("DO\n")      ;  chars += strlen(yytext); }
"while"   { printf("WHILE\n")   ;  chars += strlen(yytext); }
"for"     { printf("FOR\n")     ;  chars += strlen(yytext); }
"if"      { printf("IF\n")      ;  chars += strlen(yytext); }
"else"    { printf("ELSE\n")    ;  chars += strlen(yytext); }
"printf"  { printf("PRINTF\n")  ;  chars += strlen(yytext); }
"scanf"   { printf("SCANF\n")   ;  chars += strlen(yytext); }
"define"  { printf("DEFINE\n")  ;  chars += strlen(yytext); }
"exit"    { printf("EXIT\n")    ;  chars += strlen(yytext); }

  /*comentários*/
[/][*]([^*]|[*]+[^/])*[*]+[/] {i=0; while(i<strlen(yytext)){if (yytext[i]=='\n'){ lines++; chars=0; };chars++; i++;};}
[/][/].*                      

  /*tab e white*/
[ \t]     { chars += strlen(yytext); } 

0(X|x){1}[0-9A-Fa-f]+    { printf("NUM_HEXA(%s)\n",yytext)    ; chars += strlen(yytext) ; }
0[1-7][0-7]*             { printf ("NUM_OCTAL(%s)\n",yytext)  ; chars += strlen(yytext) ; }
[0-9]+                   { printf("NUM_INTEGER(%s)\n",yytext) ; chars += strlen(yytext) ; }

\'([^\']|\\.)?\'         { printf("CARACTER(%s)\n",yytext)    ; chars += strlen(yytext) ; }
\"(\\.|\"\"|[^"\n])*\"   { printf("STRING(%s)\n",yytext)      ; chars += strlen(yytext) ; }
[a-zA-Z_][a-zA-Z0-9_]*   { printf("IDENTIFIER(%s)\n",yytext)  ; chars += strlen(yytext) ; }

"+"  { printf("PLUS\n")                ;  chars += strlen(yytext); }
"-"  { printf("MINUS\n")               ;  chars += strlen(yytext); }
"*"  { printf("MULTIPLY\n")            ;  chars += strlen(yytext); }
"%"  { printf("REMAINDER\n")           ;  chars += strlen(yytext); }
"++" { printf("INC\n")                 ;  chars += strlen(yytext); }
"--" { printf("DEC\n")                 ;  chars += strlen(yytext); }
"&"  { printf("BITWISE_AND\n")         ;  chars += strlen(yytext); }
"|"  { printf("BITWISE_OR\n")          ;  chars += strlen(yytext); }
"~"  { printf("BITWISE_NOT\n")         ;  chars += strlen(yytext); }
"^"  { printf("BITWISE_XOR\n")         ;  chars += strlen(yytext); }
"!"  { printf("NOT\n")                 ;  chars += strlen(yytext); }
"&&" { printf("LOGICAL_AND\n")         ;  chars += strlen(yytext); }
"||" { printf("LOGICAL_OR\n")          ;  chars += strlen(yytext); }
"==" { printf("EQUAL\n")               ;  chars += strlen(yytext); }
"!=" { printf("NOT_EQUAL\n")           ;  chars += strlen(yytext); }
"<"  { printf("LESS_THAN\n")           ;  chars += strlen(yytext); }
">"  { printf("GREATER_THAN\n")        ;  chars += strlen(yytext); }
"<=" { printf("LESS_EQUAL\n")          ;  chars += strlen(yytext); }
">=" { printf("GREATER_EQUAL\n")       ;  chars += strlen(yytext); }
">>" { printf("R_SHIFT\n")             ;  chars += strlen(yytext); }
"<<" { printf("L_SHIFT\n")             ;  chars += strlen(yytext); }
"="  { printf("ASSIGN\n")              ;  chars += strlen(yytext); }
"+=" { printf("ADD_ASSIGN\n")          ;  chars += strlen(yytext); }
"-=" { printf("MINUS_ASSIGN\n")        ;  chars += strlen(yytext); }
","  { printf("COMMA\n")               ;  chars += strlen(yytext); }
":"  { printf("COLON\n")               ;  chars += strlen(yytext); }
"("  { printf("L_PAREN\n")             ;  chars += strlen(yytext); }
")"  { printf("R_PAREN\n")             ;  chars += strlen(yytext); }
"{"  { printf("L_CURLY_BRACKET\n")     ;  chars += strlen(yytext); }
"}"  { printf("R_BRACE_BRACKET\n")     ;  chars += strlen(yytext); }
"?"  { printf("TERNARY_CONDITIONAL\n") ;  chars += strlen(yytext); }
"#"  { printf("NUMBER_SIGN\n")         ;  chars += strlen(yytext); }
";"  { printf("SEMICOLON\n")           ;  chars += strlen(yytext); }


  /* erro genérico */
.  { printf("ERRO: LINHA: %d,COLUNA:%d\n",lines, chars);} /* qualquer outro caracter */
%%

int main(int argc, char **argv){
  yylex();
  return 0;
}
