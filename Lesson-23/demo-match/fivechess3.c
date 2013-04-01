#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

/* define chessboard size */
#define ROW  15
#define COL  15

/* define how many chess win */
#define N  5

#define printf(fmt, args...)    fprintf(stderr, fmt, ##args)

struct dir_struct
{
	int dx;		// row diff
	int dy;		// col diff
	char name[16];	// name of dir
};

struct dir_struct dirs[8] =
{
	{0, 1, "right"},
	{0, -1, "left"},
	{-1, 0, "up"},
	{1, 0, "down"},
	{-1, 1, "right_up"},	
	{1, -1, "left_down"},
	{-1, -1, "left_up"},
	{1, 1, "right_down"},
};

int board[ROW][COL] = {{0} };

/* display chessboard using printf */
void print_board(void)
{
    int i, j;

    printf("\n");
    printf("   ");

    for (j = 0; j < COL; j++)
        printf(" %d", j % 10);
    printf("\n");

    printf("  -");
    for (j = 0; j < COL; j++)
        printf(" -");

    printf("\n");
    for (i = 0; i < ROW; i++) {
        printf("%2d| ", i);
        for (j = 0; j < COL; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}


void print_board2(void)
{
	int i, j;

	printf("\n");
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
			printf("%d ", board[i][j]);

		printf("\n");
	}
	printf("\n");

	return;
}

void get(int* x_addr, int* y_addr)
{
	printf("man please input x y : ");
	scanf("%d %d", x_addr, y_addr);
}

void readline_from_fifo(int fd, char * buf)
{
	int ret = 0;

	while (1)
	{
		ret = read(fd, buf, 1);
		if (errno == EAGAIN || ret == 0)
			continue;
		//printf("get %c\n", *buf);

		if (*buf == '\n' || *buf == '\0')
			break;

		buf++;
	}

	*buf = '\0';
	printf("buf = %s", buf);

	return;
}

void get_from_fifo(int* x_addr, int* y_addr, int fd)
{
	char buf[32];

	printf("fifo please input x y : ");

	readline_from_fifo(fd, buf);
	sscanf(buf, "%d %d", x_addr, y_addr);
}

int is_onboard(int x, int y)
{
	if (x < 0 || x >=ROW || y < 0 || y >= COL)
		return 0;

	return 1;
}

int is_empty(int x, int y)
{
	if (board[x][y] != 0)
		return 0;

	return 1;
}

void put(int x, int y, int who)
{
	board[x][y] = who;

	return;
}

int count(int x, int y, struct dir_struct onedir)
{
	int counter = 0;

	// get current x and y to nextx & nexty
	int nx = x, ny = y;

	int i;
	for (counter = 0, i = 0; i < 4; i++) 
	{
		// get next x & y in onedir
		nx += onedir.dx;
		ny += onedir.dy;

		if (!is_onboard(x, y))
			break;

		if (board[nx][ny] != board[x][y])
			break;

		counter++;
	}

	return counter;
}

int check(int x, int y)
{
	int i = 0;

	/* judge if there is 5-chess in a line */
	for (i = 0; i < 4; i++)
	{
		int counter1;
		int counter2;

		counter1 = count(x, y, dirs[i*2]);
		counter2 = count(x, y, dirs[i*2+1]);

		if (counter1 + counter2 + 1 >= N)
		{
			printf("%s: %d, %s: %d\n", dirs[i*2].name, counter1, dirs[i*2+1].name,  counter2);
			return 1;
		}
	}

	return 0;
}

int think(int *x, int *y)
{
	printf("machine is thinking x y ...\n");
	/* random position */
	do {
		*x = rand() % ROW;
		*y = rand() % ROW;
	} while (!is_empty(*x, *y));

	return 0;
}

int main(int argc, char * argv[])
{
	int x = 4;
	int y = 5;
	int who = 0;
	int step = 0;
	int first = 0;

	printf("Hello, chess board!\n");

	if (argc < 2)
	{
		printf("./a.out who_is_first(man/machine)\n");
		return 0;
	}

	if (strcmp(argv[1], "machine") == 0)
	{
		printf("machine first\n");
		first = 1;	// 1 -> machine first
	}
	else
	{
		printf("man first\n");
		first = 2;	// 2 -> man first
	}

	printf("open p1... \n");
	int fd = open("p1", O_RDONLY);
	printf("p1 opened. fd = %d\n", fd);

	print_board();

	while (1)
	{
		who = step % 2 + 1;
		printf("player %d -> ", who);

		if (first == who)
		{   
			/* computer think a position */
			//think(&x, &y);
			get_from_fifo(&x, &y, fd);
			printf("machine: %d %d\n", x, y);

		}   
		else
		{   
			/* get user input x y */
			get(&x, &y);
			printf("man: %d %d\n", x, y);
		}   

		if (!is_onboard(x, y))
		{
			printf("this place is out of board, please reinput\n");
			continue;
		}

		if (!is_empty(x, y))
		{
			printf("this place is taken, please reinput\n");
			continue;
		}

		/* put the chess down */
		put(x, y, who);
		step++;

		printf("step %d : %d %d [Player %d]\n", step, x, y, who); 
		
		/* send x y to stdout, fifo */
		if (first != who)
		{
			//fprintf(stdout, "step %d : %d %d\n", step, x, y); 
			fprintf(stdout, "%d %d\n", x, y); 
			fflush(stdout);
		}

		print_board();

		/* check if this chess (x, y) leads to win */
		if (check(x, y))
		{
			printf("player %d wins! (%d %d) \n", who, x, y);
			break;
		}
	}

	close(fd);
	printf("game over!\n");

	return 0;
}
