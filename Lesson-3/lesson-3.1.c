#include <stdio.h>

int main(void)
{
	int counter;

	printf("hello, NCCL!\n");
	
	counter =  0;
	while (counter < 0)
	{
		counter++;
		printf("counter = %d\n", counter);
	}

	return 0;
}
