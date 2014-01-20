#include <stdio.h>

int main(void)
{
	int x, y;
	int oldx = -1;
	int oldy = -1;
	char buf[64];

	FILE * fd;

	fd = fopen("log.txt", "a+");

	while (1)
	{
		scanf("%s : %d %d", buf, &x, &y);
		if (strcmp(buf, "step") != 0)
			continue;
		
		fprintf(stderr, "[pipe: <%d> %d %d]\n", getpid(), x, y);
		fflush(stderr);

		if (x == oldx && y == oldy)
			break;

		printf("%d %d\n", x, y);
		fflush(stdout);

		fprintf(fd, "%d %d\n", x, y);
		fflush(fd);

		oldx = x;
		oldy = y;

		sleep(1);
	}	
	
	fclose(fd);

	return 0;
}
