#include <stdio.h>

int main(void)
{
	int counter;

	printf("hello, NCCL!\n");
	
	counter = 1;
	while (counter <= 10)
	{
		printf("counter = %d\n", counter);
		counter++;
	}

	return 0;
}
