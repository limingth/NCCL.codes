#include <stdio.h>

int main(void)
{
	int x, y;
	int oldx = -1;
	int oldy = -1;

	FILE * fd;

	fd = fopen("log.txt", "a+");

	while (1)
	{
		scanf("%d %d", &x, &y);
		fprintf(stderr, "[pipe: <%d> %d %d]\n", getpid(), x, y);

		if (x == oldx && y == oldy)
			break;

		printf("%d %d\n", x, y);
		fflush(stdout);

		fprintf(fd, "%d %d\n", x, y);
		fflush(fd);

		oldx = x;
		oldy = y;
	}	
	
	fclose(fd);

	return 0;
}
