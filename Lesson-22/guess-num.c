#include <stdio.h>

#define		N	3

void get_rand_num(int n, char * guess)
{
	int counter = 0;
	int digit = 0;
	int flag = 0;

	srand(time(NULL));

	while (counter < n)
	{
		// get a rand digit in 0-9
		digit = rand() % 10;

		if (!(flag & (1<<digit)))
		{
			*guess = digit + '0';

			guess++;
			counter++;

			// set flag bit_n = 1
			flag |= 1<<digit;
		}
	}
	
	return;
}

void get_input_num(int n, char * input)
{
	scanf("%s", input);

	*(input+N) = '\0';

	return;
}

void comp_str(char * pa, char * pb, int * na, int * nb)
{
	int i, j;

	*na = 0;
	*nb = 0;

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
		{
			if (pa[i] == pb[j])
			{
				if (i == j)
					(*na)++;
				else
					(*nb)++;
			}
		}

	return;
}

int main(void)
{
	char guess[N+1] = "39";
	char input[N+1];
	int na = 0, nb = 0;
	int counter = 0;

	printf("hello, guess num\n");

	get_rand_num(N, guess);
//	printf("guess num = %s\n", guess);

	while (1)
	{
		counter++;

		printf("please input %d digits:", N);
		get_input_num(N, input);
		printf("input num = %s\n", input);

		// compare two string, return nA, nB;
		comp_str(guess, input, &na, &nb);
//		printf("str1: %s\n", guess);
		printf("%d str2: %s\n", counter, input);
		printf("%dA, %dB\n", na, nb);

		if (na == N)
			break;
	}

	printf("You win! congratulation! game over!\n");

	return 0;
}
