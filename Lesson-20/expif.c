#include <stdio.h>
#include <string.h>

#define debug(fmt, args...) 	fprintf(stderr, fmt, ##args)

int get_input_type(char * word)
{
	if (strcmp(word, " ") == 0)
		return 0;
	if (strcmp(word, "\t") == 0)
		return 0;

	if (strcmp(word, "#") == 0)
		return 1;
	
	if (strcmp(word, "if") == 0)
		return 2;

	if (strcmp(word, "\n") == 0)
		return 4;

	if (strcmp(word, "endif") == 0)
		return 5;

	return 3;
}

char c;
char word[64];
char word_buf[64];
char buf[128];

int macro_value = 0;

void act_print_word(void)
{
	printf("%s", word);

	return;
}

void act_save_to_buf(void)
{
	strcat(buf, word);

	return;
}

void act_print_buf_and_word(void)
{
	printf("%s", buf);
	printf("%s", word);

	strcpy(buf, "");

	return;
}

void act_save_word(void)
{
	strcat(word_buf, word);
	strcat(buf, word);

	return;
}

void act_get_macro_name(void)
{
	debug("macro name = <%s>\n", word_buf);

	if (atoi(word_buf) > 0)
		macro_value = 1;
	else
		macro_value = 0;

	return;
}

void act_print_word_in_macro(void)
{
	debug("word buf = <%s>, macro = %d\n", word_buf, macro_value);

	if (macro_value > 0)
		printf("%s", word);

	return;
}

void act_print_buf_and_word_in_macro(void)
{
	debug("word buf = <%s>, macro = %d\n", word_buf, macro_value);

	if (macro_value > 0)
	{
		printf("%s", buf);
		printf("%s", word);
	}

	return;
}

void act_clear_buf(void)
{
	strcpy(buf, "");
	strcpy(word_buf, "");
	macro_value = 0;

	return;
}

/* state machine design */
#if 0
i0: space & tab
i1: #
i2: if
i3: anyword (MAX)
i4: \n
i5: endif

a0 act_print_word
a1 act_save_to_buf
a2 act_print_buf_and_word
a3 act_save_word
a4 act_get_macro_name
a5 act_print_word_in_macro
a6 act_print_buf_and_word_in_macro
a7 act_null

#define MAX 100

     spa  #    if  MAX  \n   endif
     i0   i1   i2   i3   i4   i5
-----------------------------------------
s0:  start
     s0,  s1,  s9,  s9,  s0,  s9,
     a0,  a1,  a0,  a0,  a0,  a0,

s1:  #
     s1,  s0,  s2,  s0,  s0,  s0,
     a1.  a2,  a1,  a2,  a2,  a2,

s2:  #if
     s3,  s0,  s0,  s0,  s0,  s0,
     a1,  a2,  a2,  a2,  a2,  a2,

s3:  #if |
     s3,  s4,  s4,  s4,  s5,  s4,
     a1,  a3,  a3,  a3,  a2,  a3,

s4:  #if abc
     s4,  s4,  s4,  s4,  s5,  s4,  
     a3,  a3,  a3,  a3,  a4,  a3,

s5:  #if abc
      
     s5,  s6,  s7,  s7,  s5,  s5, 
     a5,  a1,  a5,  a5,  a5,  a5,

s6:  #if abc
     #
     s6,  s5,  s5,  s6,  s7,  s8,
     a1,  a3,  a6,  a6,  a6,  a1,

s7:  #if abc
     abc
     s7,  s7,  s7,  s7,  s5,  s7,
     a5,  a5,  a5,  a5,  a5,  a5,

s8:  #if abc
  :  abc
  :  #endif 
     s8,  s7,  s7,  s7,  s0,  s7,
     a7,  a6,  a6,  a6,  a7,  a6,

s9:  if
     s9,  s9,  s9,  s9,  s0,  s9,
     a0,  a0,  a0,  a0,  a0,  a0,

#endif

enum { s0 = 0, s1, s2, s3, s4, s5, s6, s7, s8, s9 };

int state_transition[10][6] = 
{
     s0,  s1,  s9,  s9,  s0,  s9,
     s1,  s0,  s2,  s0,  s0,  s0,
     s3,  s0,  s0,  s0,  s0,  s0,
     s3,  s4,  s4,  s4,  s5,  s4,
     s4,  s4,  s4,  s4,  s5,  s4,  
     s5,  s6,  s7,  s7,  s5,  s5, 
     s6,  s5,  s5,  s6,  s7,  s8,
     s7,  s7,  s7,  s7,  s5,  s7,
     s8,  s7,  s7,  s7,  s0,  s7,
     s9,  s9,  s9,  s9,  s0,  s9,
};

#define a0 act_print_word
#define a1 act_save_to_buf
#define a2 act_print_buf_and_word
#define a3 act_save_word
#define a4 act_get_macro_name
#define a5 act_print_word_in_macro
#define a6 act_print_buf_and_word_in_macro
#define a7 act_clear_buf

#if 1
typedef void (*PF)(void);
PF act_table[10][6] =
{
     a0,  a1,  a0,  a0,  a0,  a0,
     a1,  a2,  a1,  a2,  a2,  a2,
     a1,  a2,  a2,  a2,  a2,  a2,
     a1,  a3,  a3,  a3,  a2,  a3,
     a3,  a3,  a3,  a3,  a4,  a3,
     a5,  a1,  a5,  a5,  a5,  a5,
     a1,  a3,  a6,  a6,  a6,  a1,
     a5,  a5,  a5,  a5,  a5,  a5,
     a7,  a6,  a6,  a6,  a7,  a6,
     a0,  a0,  a0,  a0,  a0,  a0,
};
#endif

void getword(char * word)
{
	char c;

	c = getchar();

	if (c == EOF)
	{
		*word = '\0';
		return;
	}

	// if c == 1, % 
	if (!isalpha(c))
	{
		*word++ = c;
		*word = '\0';
		return;
	}

	do
	{
		*word++ = c;
		
		c = getchar();
	} while (isalnum(c) || c == '_');

	// current c is $
	ungetc(c, stdin);
	*word = '\0';

	return;
}

int main(void)
{
	int state = 0;

	while (1)
	{
		int input = 0;
		void (*pf)(void);
//		char word[64];

	//	c = getchar();
	//	input = get_input_type(c);
		getword(word);
		input = get_input_type(word);
		
		//printf("c = %c, input = %d\n", c, input);

		//if (c == EOF)
		//	break;
		if (strcmp(word, "") == 0)
			break;

		pf = act_table[state][input];
		pf();

		state = state_transition[state][input];

		debug("word = <%s>, input = %d, state = %d\n", word, input, state);
	}

	return 0;
}
