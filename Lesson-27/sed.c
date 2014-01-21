#include <stdio.h>
#include <assert.h>

#define SIZE	512

int sed_main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Usage: sed pattern\n");
		return -1;
	}

	char buf[SIZE];
	int n;

	fgets(buf, SIZE, stdin);
	printf("buf = %s\n", buf);
	
	printf("patter = %s\n", argv[1]);

	return 0;
}
