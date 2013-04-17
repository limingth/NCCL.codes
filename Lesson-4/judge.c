#include <stdio.h>

int main(void)
{
	int num = 0;

	printf("demo judge number parity\n");

	while (1)
	{
		scanf("%d", &num);
		printf("num = %d\n", num);

		if (num % 2 == 0)
			printf("num %d is even\n", num);
		else
			printf("num %d is odd\n", num);
	}

	return 0;
}
	
