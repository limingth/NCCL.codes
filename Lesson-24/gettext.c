/*
 * state.c - using FSM to find (+/-)float number strings in buf
 *
 * Copyright (C) 2010   li ming <limingth@gmail.com>
 *
 * find number string such as 123, +1, -03.708 in "ab123+1--03.708"
 *
 */
#include <stdio.h>
#include <string.h>

//#define DEBUG
#ifdef DEBUG
#define DPRINT(fmt, args...)    fprintf(stderr, fmt, ##args)
#else
#define DPRINT(fmt, args...)    
#endif

int state = 0;
char input;

/* global index of input */
int pos = 0;

int mark = 0;

/* the string buffer to deal with */
char buf[1024*4];

char get_next_char(void)
{
	char c;
	
	c = getchar();

	// save the input
	buf[pos] = c;
	
	if (mark == 1)
		pos++;
	
	return c;
}

int get_input_type(char ch)
{
    if (ch == ' ')
		return 0;
		
	if (ch == '<')
        return 1;

    if (ch == '>' )
        return 2;

    if (ch == '\0' || ch == EOF)
        return 4;

	return 3;
}

int state_table[2][5] = 
{
	0,			 1,			  0, 			0,			-1,
	1, 			 1,			  0,			1, 			-1,
};

/*
   States (状态表)
   Actions (动作表)

                0( )         1(<)         2(>)          3(z)        4(\0)
S0()            S0( )        S1(<)        S0( )         S0( )       -1
				0,			 1,			  0, 			0,			-1,
                act_print,   act_begin,    act_print,   act_print,  act_null,
			   
S1(<)           S1(< )       S1(<<)       S0(<>)        S1(<z)      -1
				1, 			 1,			  0,			1, 			-1,
    	        act_null,    act_null,    act_null,     act_null,   act_null,
	   		   
*/
void act_begin(void)
{
	putchar('\n');
}

void act_print(void)
{
	putchar(input);
}		

void act_warn(void)
{
   // fprintf(stderr, "warning! \n");
}

void act_null(void)
{

}

void (*action[2][5])(void) =
{
                act_print,   act_begin,    act_print,    act_print,  act_null,
			    act_null,    act_null,    act_null,     act_null,   act_null,   
};

int main(int argc, char * argv[])
{
    state = 0;
	pos = 0;
		
    while( state != -1 )
    {
		int condition;
		
		input = get_next_char();
				
        condition = get_input_type(input);
        DPRINT("(%d) %d [%c] \n", state, condition, input);
      
        /* call action to do something */
        action[state][condition]();

		/* get new state from state transition table */
        state = state_table[state][condition];
        //getchar();    
    }

    return 0;
}
