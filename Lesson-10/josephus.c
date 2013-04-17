#include <stdio.h>

#define ALL	100	// all people in the ring
#define OUT	3	// if count to 3, then out

/* record the next people's index */
int next[ALL];

void init_ring(void)
{
	int i = 0;

	for (i = 0; i < ALL; i++)
		next[i] = (i + 1) % ALL;

	return;
}

void print_ring(void)
{
	int i = 0;

	for (i = 0; i < ALL; i++)
		printf("%d ", next[i]);
	printf("   (next)\n");

	return;
}

int main(void)
{
	int left;	// how many people in the ring
	int counter;
	int i;
	int prev;

	printf("demo josephus ring problem\n");

	init_ring();

	print_ring();

	left = ALL;	// left = all people
	counter = 0;	// counter = 1, 2, 3
	i = 0;		// begin from [0]
	prev = ALL - 1;		// 0 's prev = 5
	while (left > 0)
	{	
		// every step is useful
		counter++;

		// if count to 3, then someone is out
		if (counter == OUT)	
		{
			left--;		// someone is out
			printf("%d is out\n", i + 1);
			
			/* set the next[] */
			next[prev] = next[i];
		//	print_ring();
			counter = 0;	// set counter = 0
		}


//		printf("i = %d, counter = %d, left = %d\n", i, counter, left);

		prev = i;
		i = next[i];		// get next i

//		getchar();
	}

	printf("problem is finished\n");

	return 0;
}
