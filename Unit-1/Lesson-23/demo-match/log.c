#include <stdio.h>
#include <string.h>

int main(int argc, char * argv[])
{
	int x, y;
	int step = 0;
	int oldx = -1;
	int oldy = -1;
	char buf[64];

	FILE * fd;
	FILE * fd2;

	if (argc >= 2)
		strcpy(buf, argv[1]);
	else
		strcpy(buf, "m.log");

	fd = fopen(buf, "a+");

	strcat(buf, ".html");
	fd2 = fopen(buf, "a+");
		

	while (1)
	{
		scanf("%d %d", &x, &y);
		step++;
		
		fprintf(stderr, "[pipe: <%d> step %d: %d %d]\n", getpid(), step, x, y);
		fflush(stderr);

		if (x == oldx && y == oldy)
			break;

		fprintf(stdout, "%d %d\n", x, y);
		fflush(stdout);

		fprintf(fd, "step %d : %d %d\n", step*2-1, x, y);
		fflush(fd);

		fprintf(fd2, "[%d,%d], ", x, y);
		fflush(fd2);

		oldx = x;
		oldy = y;

		usleep(1000*200);
	}	
	
	fclose(fd);
	fclose(fd2);

	return 0;
}
