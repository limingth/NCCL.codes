#include <stdio.h>

int get_input_type(char c)
{
	if (c == ' ')
		return 1;

	return 0;
}

char c;

void act_print(void)
{
	printf("%c", c);

	return;
}

void act_null(void)
{
	return;
}


int state_transition[3][2] = 
{
	{ 0, 1 },
	{ 0, 2 },
	{ 0, 2 }
};

typedef void (*PF)(void);
PF act_table[3][2] =
{
	{ act_print, act_print },
	{ act_print, act_null },
	{ act_print, act_null },
};

int main(void)
{
	char buf[] = "  This is   a book.   That  is a bag\n";
	// input      1100001001110100000111000011001010000
	// state     01200001001220100000122000012001010000
	// print      p pppppppp  pppppppp  ppppp ppppppppp
	int state = 0;
	int i = 0;
	int words = 0;
	char * p = NULL;
	int counter = 0;

//	printf("buf = %s\n", buf);

	i = 0;
	while (1)
	{
		int input = 0;
		void (*pf)(void);

		c = getchar();
		input = get_input_type(c);
		
		//printf("c = %c, input = %d\n", c, input);

		if (c == EOF)
			break;

		pf = act_table[state][input];
		pf();

		state = state_transition[state][input];

		i++;
	}

	return 0;
}
