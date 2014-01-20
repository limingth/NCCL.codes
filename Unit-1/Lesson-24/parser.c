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

/* global var : state and input */
int state = 0;
char input;

/* global index of input */
int pos = 0;

/* the string buffer to deal with, 4K size */
char buf[1024*4];

/* mark == 1, then record the input char */
int mark = 0;

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
char * pattern = "html";

int get_input_type(char ch)
{
    if (ch == ' ')
		return 0;
		
	if (ch == '<')
        return 1;

	if (ch == '>' )
        return 3;

    if (ch == '/' )
        return 4;

    if (ch == '\0' || ch == EOF)
        return 6;

	if (state == 1 || state == 6)
	{		
		int i = 0;
		
		while (1)
		{
			if (ch != pattern[i])
				return 5;
			
			i++; 				
			if (pattern[i] == '\0')	
				return 2;
			
			pos++;		
			ch = get_next_char();
		}
	}
		
	return 5;
}


int select = 0;

void act_mark(void)
{
	mark = 1;
	pos++;
}

void act_unmark(void)
{
	mark = 0;
	pos = 0;
}

void act_select(void)
{
    select = 1;	
}

void act_unselect(void)
{
    select = 0;
	
	act_unmark();
}

void act_print(void)
{
	static int counter = 0;
    int i;

	// if current tag is a match, then print it
	if (select == 1)
	{			
		buf[pos] = '\0';
	
		counter++;	
		printf("%3d : %s (%d)\n", counter, buf, pos);
	}		
		
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

/*
   States (状态表)
   Actions (动作表)

                0( )         1(<)         2(tag)        3(>)        4(/)        5(z)       6(\0)
S0()            S0( )        S1(<)        S0( )         S0( )       S0( )       S0(z)      -1
                act_null,    act_mark,    act_null,     act_null,   act_null,   act_null,
                           							 
S1(<)           S1(< )       S1(<<)       S2(<tag)      S0(<>)      S0(</)      S0(<z)     -1
    	        act_null,    act_mark,    act_null,     act_null,   act_unmark, act_unmark,                          
				     		 act_warn                   act_warn    act_warn

S2(<tag)        S3(<tag )    S1(<tag<)    S0(<tagtag)   S4(<tag>)   S3(<tag/)   S0(<tagz)  -1
    	        act_select,  act_mark,    act_unmark,   act_select, act_select, act_unmark,               
			    act_warn     act_warn                   act_warn

S3(<tag )       S3(<tag )    S1(<tag <)   S3(<tag tag)  S4(<tag >)  S3(<tag /)  S3(<tag z) -1
    	        act_null,    act_mark,    act_null,     act_null,   act_null,   act_null,
			    act_warn                       

S4(<tag>)       S4(<tag> )   S5(<tag><)   S4(<tag>tag)  S4(<tag>>)  S4(<tag>/)  S4(<tag>z) -1
    	        act_null,    act_null,    act_null,     act_null,   act_null,   act_null,
				
S5(<tag><)      S5(<tag>< )  S5(<tag><<) S5(<tag><tag)  S5(<tag><>) S6(<tag></) S5(<tag><z) -1
    	        act_null,    act_null,   act_null,      act_null,   act_null,    act_null, 

S6(<tag></)     S6(<tag></ ) S5(<tag><)  S7(<tag></tag) S4(<tag>)   S4(<tag>)   S4(<tag>)   -1
                act_warn,    act_warn,   act_null,      act_warn,   act_warn,   act_warn,
		   
S7(<tag></tag)  S7(<T></T )  S5(<T><)    S4(<tag>tag)   S0( )       S4(<tag>)   S4(<tag>)   -1
                act_null,    act_warn,   act_null,      act_print,  act_null,   act_null,
		   
*/
int state_table[8][7] = 
{
	0, 1, 0, 0, 0, 0, -1,
	1, 1, 2, 0, 0, 0, -1,
	3, 1, 0, 4, 3, 0, -1,
	3, 1, 3, 4, 3, 3, -1,
	4, 5, 4, 4, 4, 4, -1,
	5, 5, 5, 5, 6, 5, -1,
	6, 5, 7, 4, 4, 4, -1,
	7, 5, 4, 0, 4, 4, -1,      
};

void (*action[8][7])(void) =
{
                act_null,    act_mark,    act_null,     act_null,   act_null,   act_null, act_null,
			   
				act_null,    act_mark,    act_null,     act_null,   act_unmark, act_unmark, act_null,

    	        act_select,  act_mark,    act_unmark,   act_select, act_select, act_unmark, act_null,

    	        act_null,    act_mark,    act_null,     act_null,   act_null,   act_null, act_null,

    	        act_null,    act_null,    act_null,     act_null,   act_null,   act_null, act_null,

    	        act_null,    act_null,   act_null,      act_null,   act_null,    act_null, act_null,

                act_warn,    act_warn,   act_null,      act_warn,   act_warn,   act_warn, act_null,
		   
                act_null,    act_warn,   act_null,      act_print,  act_null,   act_null, act_null,
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
		/* input TYPE ID which is return from get_input_type */
		int condition;

		input = get_next_char();
		DPRINT("%c, pos = %d ", input, pos);
				
        condition = get_input_type(input);		
		
        DPRINT("(%d) %d [%c] \n", state, condition, input);
      
        /* call action to do something */
        action[state][condition]();

		/* get new state from state transition table */
        state = state_table[state][condition];
        //DPRINT( "new state: %d \n", input );
        //getchar();    

		// if mark is true, then set to next pos
		//if (mark == 1)
		//	pos++;

		//pos++;
    }

    return 0;
}
