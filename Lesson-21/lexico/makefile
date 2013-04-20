.PHONY: lex.yy.c
.PHONY: a.out

lex.yy.c: lexico.l
	flex lexico.l

a.out: lex.yy.c
	cc lex.yy.c -lfl
	
run: ./a.out 
	./a.out
