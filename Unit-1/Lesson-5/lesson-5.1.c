#include <stdio.h>

int main(void)
{
	int sum = 0;
	int i;
	
	for (i = 0; i <= 100; i++)	
	{
		sum += i;
	}

	printf("sum = %d\n", sum);

	return 0;
}
