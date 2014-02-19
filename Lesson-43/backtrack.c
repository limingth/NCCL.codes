#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
	{ 0, 0, 0, 0, 0 },
	{ 0, 1, 0, 1, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 1, 0, 1, 0 },
	{ 0, 0, 0, 0, 0 },
};

void print_maze(void)
{
	int i, j;

	for(i = 0; i < 5; i++)
	{
		for(j = 0; j < 5; j++)
			printf( "%d(%d)\t", maze[i][j], i*MAX_COL+j );

		printf( "\n" );
	}

	printf( "******************\n" );
	return;
}

struct point {
	int row;
	int col;
} stack[512]; 

int top = 0;

void push( struct point p )
{
	printf( "stack <- push point(%d, %d) %d \n", p.row, p.col, p.row*5+p.col );
	stack[top++] = p;
}

struct point pop(void)
{
	struct point p;
	p = stack[--top];
	printf( "stack -> pop point(%d, %d) %d \n", p.row, p.col, p.row*5+p.col );
	return p;
}

struct point get_top(void)
{
	return stack[top-1];
}

int is_empty(void)
{
	return (top==0);
}

void print_stack(void)
{
	int i;

	printf( "stack info : \n" );
	for(i = top-1; i >= 0; i--)
	{
		printf( "(%d, %d) %d\n", 
				stack[i].row, stack[i].col, 
				stack[i].row*MAX_COL+stack[i].col );
	}
	return;
}

struct point start = {0, 0};
//struct point target = {0, 0};
struct point target = {4, 4};

struct point pre[MAX_ROW][MAX_COL];

void print_pre()
{
	int i, j;
	int row, col;

	printf( "pre info : \n" );
	for(i = 0; i < 5; i++)
	{
		for(j = 0; j < 5; j++)
		{
			row = pre[i][j].row;
			col = pre[i][j].col;

			printf( "%d(%d)\t", row*MAX_COL+col, i*MAX_COL+j );
		}
		printf( "\n" );
	}

	printf( "******************\n" );
	return;
}

int visit( int newrow, int newcol, struct point father)
{
	struct point tmp;

	/* set as recorded */
	maze[newrow][newcol] = 2;

	/* set new expend node 's father node */
	pre[newrow][newcol] = father;

	/* push this point to record */
	tmp.row = newrow;
	tmp.col = newcol;
	push(tmp);

	return 1;
}

void backtrack( struct point p )
{
	struct point stacktop;
	struct point tmp;
	struct point branch_point;

	// 1. struct point stacktop = get the top item from stack
	stacktop = get_top();
	printf( "top is (%d, %d) \n", stacktop.row, stacktop.col );

	// 2. get stacktop 's father point = branch_point
	branch_point = pre[stacktop.row][stacktop.col];
	printf( "father is (%d, %d) \n", branch_point.row, branch_point.col);

	// 3. from p to branch_point
	tmp = p;

	while( !(tmp.row==branch_point.row && tmp.col==branch_point.col) )
	{
		struct point save;
		maze[tmp.row][tmp.col] = 0;
		save = tmp;

		tmp = pre[tmp.row][tmp.col];

		pre[save.row][save.col].row = 0;
		pre[save.row][save.col].col = 0;

		print_maze();
		print_pre();
		//getchar();
	}
}

void print_solution(void)
{
	struct point tmp = target;

	while( !(tmp.row==start.row && tmp.col==start.col)  )
	{
		printf( "(%d,%d) %d \n", tmp.row, tmp.col, tmp.row*MAX_COL+tmp.col );

		tmp = pre[tmp.row][tmp.col];
	}

	printf( "(%d,%d) %d \n", tmp.row, tmp.col, tmp.row*MAX_COL+tmp.col );
}


int main(void)
{
	struct point p;
	int ways = 0;

	printf( "hello, maze! \n" );
	print_maze();

	/* init start situation */ 
	p = start;
	maze[p.row][p.col] = 2;
	push(p);
	print_maze();

	while( !is_empty() )
	{
		print_stack();
		/* get the saved point from stack */
		p = pop();

		/* judge if p is target point */
		if( p.row == target.row && p.col == target.col )
		{
			printf( "target is found! \n" );
			print_stack();

			/* print backward road */
			printf( "%d solution as follows: \n", ++ways );
			print_solution();
			getchar();

			// assume p is the target point
			backtrack( p );
			continue;
		}

		int flag = 0;
		/* expend p to UP, LEFT, DOWN, RIGHT */
		// look UP
		if( p.row-1 >= 0 && maze[p.row-1][p.col] == 0 )
			flag = visit( p.row-1, p.col, p );	

		// look LEFT 
		if( p.col-1 >= 0 && maze[p.row][p.col-1] == 0 )
			flag = visit( p.row, p.col-1, p );

		// look DOWN 
		if( p.row+1 < MAX_ROW && maze[p.row+1][p.col] == 0 )
			flag = visit( p.row+1, p.col, p );

		// look RIGHT 
		if( p.col+1 < MAX_COL && maze[p.row][p.col+1] == 0 )
			flag = visit( p.row, p.col+1, p );

		// backtrack clear 0
		if( flag == 0 )
			backtrack( p );

		print_maze();
		print_pre();
		print_stack();
		getchar();
	}

	printf( "there is %d ways out! \n", ways );

	return 0;
}

