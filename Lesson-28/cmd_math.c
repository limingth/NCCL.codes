#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>

int math_main(int argc, char *argv[])
{
	if (argc < 3)
	{
		printf("Usage: math func para1 para2\n");
		return -1;
	}

	if (strcmp(argv[1], "sin") == 0)
	{
		double r = sin(atoi(argv[2]));
		printf("result = %f\n", r);
		return 0;
	}

	if (strcmp(argv[1], "sqrt") == 0)
	{
		double r = sqrt(atoi(argv[2]));
		printf("result = %f\n", r);
		return 0;
	}

	printf("math function: %s not implemented\n", argv[1]);
	return -1;
}
