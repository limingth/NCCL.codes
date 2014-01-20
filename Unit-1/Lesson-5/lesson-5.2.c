#include <stdio.h>

#define PRINT(x)	printf(#x " = %d \n", x)

int main(void)
{
	int sum = 0;
	
#if (!defined(__STDC__))
	printf("Not Standard C \n");
	for (int i = 0; i <= 100; i++)
#else
	int i;
	for (i = 0; i <= 100; i++)	
#endif
	{
		PRINT(sum);
		sum += i;
	}

	printf("sum = %d\n", sum);

	return 0;
}
