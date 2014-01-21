#include <stdio.h>
#include <stdlib.h>

// see terms in http://bbs.csdn.net/topics/10266946

char *string[] = {
	"return",	// 'return'
	"0", 	// 0
	"semicolon",	// ';'
	"lbrace",		// '{'
	"rbrace",		// '}'
	"lparen",		// '('
	"rparen",		// ')'
	"int",		// 'int'
	"void",		// 'void'
	"id",		// 'main'
	"eof"
};

typedef enum {
	returnsym,	// 'return'
	number, 	// 0
	semicolon,	// ';'
	lbrace,		// '{'
	rbrace,		// '}'
	lparen,		// '('
	rparen,		// ')'
	tint,		// 'int'
	tvoid,		// 'void'
	id,		// 'main'
	eof
} Symbol;

Symbol sym;
int cursor = 0;

//Symbol input[] = { returnsym, number, semicolon };
//Symbol input[] = { lbrace, returnsym, number, semicolon, rbrace };
//Symbol input[] = { lparen, tvoid, rparen };
//Symbol input[] = { tint };
//Symbol input[] = { id, lparen, tvoid, rparen };
Symbol input[] = { tint, id, lparen, tvoid, rparen, lbrace, returnsym, number, semicolon, rbrace };

void getsym(void) {
  if (cursor >= sizeof(input) / sizeof(Symbol)) {
    sym = eof;
  } else {
    sym = input[cursor];
    printf("cursor: %d  get input: %s\n", cursor, string[sym]);
    cursor++;
  }
}

void error(const char msg[]) {
  //fprintf(stderr, "%s\n", msg);
  //fprintf(stderr, "%s [Sym=%d]\n", msg, sym);
  fprintf(stderr, "%s [Sym=%d, cursor=%d]\n", msg, sym, cursor);
  exit(0);
}

int accept(Symbol s) {
  if (sym == s) {
    getsym();
    return 1;
  }
  return 0;
}
 
int expect(Symbol s) {
  if (accept(s))
    return 1;
  error("expect: unexpected symbol");
  return 0;
}

/*
 *	stat            : 'return' number ';'
 */
void stat(void){
    if (accept(returnsym)) {
        expect(number);
        expect(semicolon);
    } else {
        error("stat: syntax error");
        getsym();
    }
}

/*
 *	compound_stat   : '{' stat '}'   
 */
void compound_stat(void){
    if (accept(lbrace)) {
        stat();
        expect(rbrace);
    } else {
        error("compound_stat: syntax error");
        getsym();
    }
}

/*
 *     type  : 'int' | 'void'
 */
void type_spec(void){
    if (accept(tint)) {
	;
    } else if (accept(tvoid)) {
	;
    } else {
        error("type_spec: syntax error");
        getsym();
    }
}

/*
 *	declarator      : id '(' type_spec ')'   
 */
void declarator(void){
    if (accept(id)){
        expect(lparen);
        type_spec();
        expect(rparen);
    }
     else {
        error("declarator: syntax error");
        getsym();
    }
}

/*
 *      decl_spec       : type_spec
 */
void decl_spec(void){
	type_spec();
}

/*
 *      function_definition : decl_spec declarator compound_stat
 */
void function_definition(void){
    decl_spec();
    declarator();
    compound_stat(); 
}

void program(void){
    function_definition();
}

int main(void) {
  getsym();
  //stat();
  //compound_stat();
  //declarator();
  //decl_spec();
  program();
  printf("Parse succeeded.\n");
  return 0;
}
