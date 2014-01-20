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

/*
 * get_input_type - get the input char TYPE ID
 *
 * 0: [ ]
 * 1: [<]
 * 2: [tag]
 * 3: [>]
 * 4: [/]
 * 5: [a-z]
 * 6: '\0' - string end
 *
 */

// <a> </a>
char * pattern = "href";

int get_input_type(char ch)
{
    if (ch == ' ')
		return 0;
		
	if (ch == '<')
        return 1;

	if (ch == '=' )
        return 3;

    if (ch == '>' )
        return 4;

    if (ch == '\0' || ch == EOF)
        return 6;

	if (state == 2)
	{
		int i = 0;
		
		while (1)
		{
			if (ch != pattern[i])
				return 5;
			
			i++; 				
			if (pattern[i] == '\0')	
				return 2;
			
			//pos++;		
			ch = get_next_char();
		}
	}
		
	return 5;
}

int state_table[7][7] = 
{
	0, 1, 0, 0, 0, 0, -1,
	2, 1, 1, 1, 0, 3, -1,
	2, 1, 4, 1, 0, 0, -1,
	2, 1, 3, 3, 0, 3, -1,
	4, 1, 3, 5, 0, 3, -1,
	5, 6, 6, 6, 0, 6, -1,
	2, 6, 6, 6, 0, 6, -1,	
};

/*
   States (状态表)
   Actions (动作表)

                0( )         1(<)         2(tag)        3(=)        4(>)        5(z)       6(\0)
S0()            S0( )        S1(<)        S0( )         S0( )       S0( )       S0(z)      -1
                act_null,    act_null,    act_null,     act_null,   act_null,   act_null,  act_null,
			   
S1(<)           S2(< )       S1(<<)       S1(<tag)      S1(<=)      S0(<>)      S3(<z)     -1
    	        act_null,    act_null,    act_null,     act_null,   act_null,   act_null,  act_null,			     		                  

S2(< )          S2(<  )      S1(< <)      S4(< tag)     S1(< =)     S0(< >)     S0(< z)    -1
    	        act_null,    act_null,    act_null,     act_null,   act_null,   act_null,  act_null,
			                 
S3(<z)          S2(<z )      S1(<z<)      S3(<ztag)    S3(<z=)      S0(<z>)     S3(<zz)    -1
    	        act_null,    act_null,    act_null,     act_null,   act_null,   act_null,  act_null,
			    
S4(< tag)       S4(< tag )   S1(< tag<)   S3(< tagtag)  S5(< tag=)  S0(< tag>)  S3(< tagz) -1
    	        act_null,    act_null,    act_null,     act_null,   act_null,   act_null,  act_null,
				
S5(< tag=)      S5(< tag= )  S6(< tag=<)  S6(< tag=tag) S6(< tag==) S0(< tag=>) S6(< tag=z) -1
    	        act_null,    act_mark,    act_mark,     act_mark,   act_print,  act_mark,   act_null,

S6(< tag=z)     S2(< tag=z ) S6(< tag=z<) S6(< tag=ztag) S6(< tag=z=) S0(< tag=z>) S6(< tag=zz)   -1
                act_print,   act_null,    act_null,      act_null,   act_print,  act_null,   act_null,
		   		   
*/

void act_mark(void)
{
	mark = 1;
	pos++;
}

void act_print(void)
{
	static int counter = 0;
    int i;

	buf[pos-1] = '\0';
	
	counter++;	
	printf("%3d : %s (%d)\n", counter, buf, pos);
		
	// clear buf and pos
	memset(buf, '\0', pos);
	pos = 0;
	
	// reset mark = 0		
	mark = 0;
}

void act_warn(void)
{
   // fprintf(stderr, "warning! \n");
}

void act_null(void)
{

}

void (*action[7][7])(void) =
{
                act_null,    act_null,    act_null,     act_null,   act_null,   act_null,  act_null,
    	        act_null,    act_null,    act_null,     act_null,   act_null,   act_null,  act_null,				     		                  
    	        act_null,    act_null,    act_null,     act_null,   act_null,   act_null,  act_null,
    	        act_null,    act_null,    act_null,     act_null,   act_null,   act_null,  act_null,
    	        act_null,    act_null,    act_null,     act_null,   act_null,   act_null,  act_null,
    	        act_null,    act_null,    act_mark,     act_mark,   act_print,  act_mark,  act_null, 
                act_print,   act_null,    act_null,     act_null,   act_print,  act_null,  act_null,		   
};

int main(int argc, char * argv[])
{
   //  printf( "please input a string : " );
    //  scanf( "%s", buf );
//    printf( "your input string is: %s \n", buf );
//    DPRINT( "%s\n", buf );
   
	if (argc > 1)
		pattern = argv[1];
	else
		fprintf(stderr, "./parse p OR ./parse a OR ./parse td \n");
	
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
