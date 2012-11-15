#include <stdio.h>

int main(void)
{
	int counter;

	printf("hello, NCCL!\n");
	
	counter = 0;
	do 
	{
		counter++;
		printf("counter = %d\n", counter);
	} while (counter < 10);

	return 0;
}
