#include <stdio.h>

int main(void)
{
	int i = 0;
	int num = 999;
	int sum = 0;
	int counter = 0;
	int max = 0;

	printf("please input a number\n");
	scanf("%d", &max);
	printf("sumary 9 from 1 to %d\n", max);

	for (i = 1; i <= max; i++)
	{
		num = i;
		counter = 0;
		while (num != 0)
		{
			if (num % 10 == 9)
				counter++;

			num = num / 10;
		}
#if DEBUG
		printf("num = %d, counter = %d\n", i, counter);
#endif
		sum += counter;
	}

	printf("sum = %d\n", sum);

	return 0;
}
