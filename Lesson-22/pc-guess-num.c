#include <stdio.h>

#define	N	2
#define	ALL	(10*10)
//#define	N	3
//#define	ALL	(10*10*10)
//#define	N	4
//#define	ALL	(10*10*10*10)
//#define	N	5
//#define	ALL	(10*10*10*10*10)

void num_to_str(int num, char * str, int n)
{
	int rest;
	int i = 0;
	char * p = str;
	
	while (num > 0)
	{
		rest = num % 10;
		*p++ = rest + '0';
		num /= 10;
	}

	while (p - str < n)
		*p++ = '0';
	*p= '\0';

	for (i = 0; i < n / 2; i++)
	{
		char tmp;
		tmp = str[i];
		str[i] = str[n-1-i];
		str[n-1-i] = tmp;
	}

	return;
}

int check_same_digit(char * str, int n)
{
	int i, j;

	for (i = 0; i < n - 1; i++)
		for (j = i + 1; j < n; j++)
		{
			if (str[i] == str[j])
				return 1;
		}

	return 0;
}

int find_first_num(int p[])
{
	int i = 0;

	for (i = 0; i < ALL; i++)
		if (p[i] == 1)
			return i;

	return -1;
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

int check_all_possible(char * src, int na, int nb, int p[])
{
	int i = 0;
	char dst[N+1];
	int new_na, new_nb;

	for (i = 0; i < ALL; i++)
	{
		if (p[i] == 0)
			continue;

		// i -> string dst;
		num_to_str(i, dst, N);

		comp_str(src, dst, &new_na, &new_nb);

		if (new_na != na || new_nb != nb)
			p[i] = 0;
	}

	return 0;
}


int main(void)
{
	int i = 0;
	char str[N+1];
	int possible[ALL];
	int counter = 0;

	char your_num[N+1];
	char guess_str[N+1];

	printf("hello, pc guess num \n");
	printf("please, input %d digits, I will guess it\n", N);
	scanf("%s", your_num);

	for (i = 0; i < ALL; i++)
	{
		//printf("i = %d, ", i);

		num_to_str(i, str, N);

		if (check_same_digit(str, N))
			possible[i] = 0;
		else
			possible[i] = 1;

		//printf("str = %s, p = %d \n", str, possible[i]);
	}

	while (1)
	{
		int guess = find_first_num(possible);
		int na = 0, nb = 0;

		//printf("guess = %d\n", guess);
		num_to_str(guess, guess_str, N);
		printf("\nI guess your number is %s\n", guess_str);

		comp_str(guess_str, your_num, &na, &nb);
		printf("hint: %da, %db\n", na, nb);

		printf("please tell me ?A?B \n");
		//scanf("%da%db", &na, &nb);
		counter++;
		printf("%d: it is %dA%dB \n", counter, na, nb);
		if (na == N)
			break;

		check_all_possible(guess_str, na, nb, possible);
	}

	printf("\nhaha, I win! Your number is %s\n", guess_str);
	
	return 0;
}
