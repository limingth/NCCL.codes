#include <stdio.h>

#define ROW	10
#define COL	10

int chessboard[ROW][COL];

void print_chessboard(void)
{
	int i, j;

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			printf("%d ", chessboard[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	return;
}

void init_chessboard(void)
{
	int i, j;

	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++)
			chessboard[i][j] = rand() % 2;

	return;
}

int is_valid(int row, int col)
{
	if (row < 0 || row >= ROW)
		return 0;

	if (col < 0 || col >= ROW)
		return 0;

	return 1;
}

struct direction 
{
	int dr;		// delta row
	int dc;		// delta col
	char name[16];
};

typedef struct direction dir_t;

dir_t dirs[4] = 
{
	{-1, 0, "up"},
	{1, 0, "down"},
	{0, -1, "left"},
	{0, 1, "right"},
};

int check(int row, int col, dir_t dir)
{
	int nr, nc;	// next row, next col
	
	nr = row + dir.dr;
	nc = col + dir.dc;

	if (is_valid(nr, nc) && chessboard[nr][nc] == 0)
		return 1;

	return 0;
}

int main(void)
{
	int row, col;

	printf("Is there a way out?\n");

	print_chessboard();
	init_chessboard();
	print_chessboard();

	while (1)
	{
		int ways = 0;
		int i = 0;

		printf("please input a position\n");
		scanf("%d %d", &row, &col);
		printf("row = %d, col = %d\n", row, col);

		if (!is_valid(row, col))
			continue;

		for (i = 0; i < 4; i++)
		{
			int ret;
		
			ret = check(row, col, dirs[i]);
			if (ret > 0)
			{
				printf("direction %s is ok!\n", dirs[i].name);			
				ways++;
			}
		}

		printf("value = %d\n", chessboard[row][col]);
		printf("ways = %d\n", ways);
	}

	return 0;
}
