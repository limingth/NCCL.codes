#include <stdio.h>

int counter = 3;
int main(void)
{
	int counter = 6;

	printf("hello, NCCL!\n");
	
	counter++;
	printf("counter = %d\n", counter);

	printf("(counter < 10) = %d\n", (counter > 10));

	getchar();
	while (counter < 10)
	{
		int counter = 9;

		counter++;
		printf("counter = %d\n", counter);
		getchar();
	}

	return 0;
}
