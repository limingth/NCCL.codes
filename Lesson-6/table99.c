#include <stdio.h>

//#define PRINT(x) 	printf( "<debug> " #x " = %d\n", x)
#define PRINT(x) 	

int main(void)
{
	int i = 0;
	int j = 0;

	printf("print 9*9 multiplication table\n");

	for (i = 1; i < 10; i++)
	{
		//printf("i = %d\n", i);
		PRINT(i);

		for (j = 1; j <= i; j++)
		{
			//printf("j = %d\n", j);
			PRINT(j);
			printf("%d*%d=%d\t", j, i, i*j);
		}
		printf("\n");
	}

	return 0;
}
