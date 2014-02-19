
#include <stdio.h>
static int maze[5][5] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

static void print_maze(void)
{
	int i, j;

	for( i = 0; i < 5; i++ )
	{
		for( j = 0; j < 5; j++ )
			printf( "%d ", maze[i][j] );
		printf("\n");
	}

	printf("------------------------\n");
	return;
}

struct point
{
	int row;
	int col;
};

/* one backtrack node */
struct node
{
	struct point pos;
	int way; /* UP, DOWN, LEFT, RIGHT */ 
} stack[512];

static int top = 0;
void push(struct node cur)
{
	stack[top] = cur;
	top++;
}

struct node pop(void)
{
	top--;
	return stack[top];
}

int is_empty()
{
	if( top <= 0 )
		return 1;

	return 0;
}

struct point start = { 0, 0 };
struct point target = { 4, 4 };

#define MAX_COL  5
#define MAX_ROW  5

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

void print_stack(void)
{
	int i;
	char str[5][16] = { "0", "up", "down", "left", "right" };

	for( i = 0; i < top; i++ )
	{
		printf( "No.%d step: (%d, %d)_%s \n", i, stack[i].pos.row, stack[i].pos.col, str[stack[i].way] );
	}
	printf( "************************\n" );
}

int try_method( struct point pos, int way )
{
	switch( way )
	{
		case UP:
			if( pos.row == 0 || maze[pos.row-1][pos.col] > 0 )
				return 0;
			return 1;
		case DOWN:
			if( pos.row == MAX_ROW-1 || maze[pos.row+1][pos.col] > 0 )
				return 0;
			return 1;
		case LEFT:
			if( pos.col == 0 || maze[pos.row][pos.col-1] > 0 )
				return 0;
			return 1;
		case RIGHT:
			if( pos.col == MAX_COL-1 || maze[pos.row][pos.col+1] > 0)
				return 0;
			return 1; 
	}

	return 0;
}

struct point expend_node( struct node cur )
{
	struct point ret;

	ret = cur.pos;

	switch( cur.way )

	{
		case UP:
			ret.row = ret.row - 1;
			break;
		case DOWN:
			ret.row = ret.row + 1;
			break;
		case LEFT:
			ret.col = ret.col - 1;
			break;
		case RIGHT:
			ret.col = ret.col + 1;
			break;
	}
	return ret;
}

int is_target( struct point pos)
{
	if( (pos.row == target.row) && (pos.col == target.col) )
		return 1;

	return 0;
}

void print_solution(void)

{
	print_maze();
	print_stack();
	getchar();
}
void confirm_node(struct node cur)
{
	// set as visited: 2 
	maze[cur.pos.row][cur.pos.col] = 2;
}

void unconfirm_node(struct node cur)
{
	// set as not visited: 0
	maze[cur.pos.row][cur.pos.col] = 0;
}

int expend_method( int way )
{
	// get next valid mothed
	return ++way;
}

int check_method( int way )
{
	// no more valid method any more
	if( way > RIGHT )
		return 0;

	return 1;
}

int main(void)
{
	// define current point : cur
	struct node cur;
	int ways = 0;

	print_maze();

	cur.pos = start;
	cur.way = 0;

	/* if stack is not over-poped */

	while( 1 )
	{
		/* judge if it is target */
		if( is_target(cur.pos) )
		{
			/* set node as confirmed */
			confirm_node( cur );

			printf("find %d solution !\n", ++ways);
			print_solution(); 

			/* if only 1 solution is to be found, then break here */
			// break;

			/* or else, continue to expend another mothed */
			unconfirm_node( cur );
			cur = pop();
		}
		/* get next mothed */
		cur.way = expend_method( cur.way );

		// if no more valid mothed, then use backtrack
		if( !check_method( cur.way ) )
		{
			// set node as not confirmed
			unconfirm_node( cur );

			/* if stack is empty, then no need to pop, just stop */
			if( is_empty() )
				break;

			/* continue to expend another mothed */
			cur = pop();
			continue;
		}

		/* confirm current node */
		confirm_node( cur );

		if( try_method( cur.pos, cur.way ) )
		{
			/* push current node */
			push( cur );
			print_stack();

			/* use current method(way) to expend node */
			cur.pos = expend_node( cur );
			cur.way = 0;
		}
	}

	printf( "there are total %d solutions. \n", ways );
	return 0;
}

