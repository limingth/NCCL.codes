#include <stdio.h>

#define XXX 	 a = 1; b = 2; 

#define XXX	do { a = 1; b = 2; } while (0)

int main(void)
{
	int counter;
	int a, b;

	printf("hello, NCCL!\n");
	
	if (counter == 0)
		XXX;
	else
		counter = 1;

	if (counter == 0)
	do 
	{	a = 1; 

		b = 2;;
	} while (0);
	else
		counter = 1;

	counter = 0;
	do 
	{
		counter++;
		printf("counter = %d\n", counter);
	} while (counter < 0);

	return 0;
}
