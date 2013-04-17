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



enum { s0 = 0, s1, s2, s3, s4, s5, s6, s7, s8, s9 };

int state_transition[10][6] = 
{
 s0, s1, s9, s9, s0, s9,
 s1, s0, s2, s0, s0, s0,
 s3, s0, s0, s0, s0, s0,
 s3, s4, s4, s4, s5, s4,
 s4, s4, s4, s4, s5, s4, 
 s5, s6, s7, s7, s5, s5, 
 s6, s5, s5, s6, s7, s8,
 s7, s7, s7, s7, s5, s7,
 s8, s7, s7, s7, s0, s7,
 s9, s9, s9, s9, s0, s9,
};


typedef void (*PF)(void);
PF act_table[10][6] =
{
 act_print_word, act_save_to_buf, act_print_word, act_print_word, act_print_word, act_print_word,
 act_save_to_buf, act_print_buf_and_word, act_save_to_buf, act_print_buf_and_word, act_print_buf_and_word, act_print_buf_and_word,
 act_save_to_buf, act_print_buf_and_word, act_print_buf_and_word, act_print_buf_and_word, act_print_buf_and_word, act_print_buf_and_word,
 act_save_to_buf, act_save_word, act_save_word, act_save_word, act_print_buf_and_word, act_save_word,
 act_save_word, act_save_word, act_save_word, act_save_word, act_get_macro_name, act_save_word,
 act_print_word_in_macro, act_save_to_buf, act_print_word_in_macro, act_print_word_in_macro, act_print_word_in_macro, act_print_word_in_macro,
 act_save_to_buf, act_save_word, act_print_buf_and_word_in_macro, act_print_buf_and_word_in_macro, act_print_buf_and_word_in_macro, act_save_to_buf,
 act_print_word_in_macro, act_print_word_in_macro, act_print_word_in_macro, act_print_word_in_macro, act_print_word_in_macro, act_print_word_in_macro,
 act_clear_buf, act_print_buf_and_word_in_macro, act_print_buf_and_word_in_macro, act_print_buf_and_word_in_macro, act_clear_buf, act_print_buf_and_word_in_macro,
 act_print_word, act_print_word, act_print_word, act_print_word, act_print_word, act_print_word,
};

void getword(char * word)
{
	char c;

	c = getchar();

	if (c == EOF)
	{
		*word = '\0';
		return;
	}

	
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


	
	
		getword(word);
		input = get_input_type(word);
		
		

		
		
		if (strcmp(word, "") == 0)
			break;

		pf = act_table[state][input];
		pf();

		state = state_transition[state][input];

		debug("word = <%s>, input = %d, state = %d\n", word, input, state);
	}

	return 0;
}
