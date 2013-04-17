#include <stdio.h>

#if 0
void swap(int a, int b)
{
	char tmp;

	tmp = b;
	b = a;
	a = tmp;
}
#endif

#define SWAP(a, b)	\
do {			\
	char tmp;	\
			\
	tmp = b;	\
	b = a;		\
	a = tmp;	\
} while (0)

void reverse(char buf[], int i)	
{
	int j = 0;

	/* string "321" to string "123" */
	for (j = 0; j < i/2; j++)
	{
		if (j >= 0)
			SWAP(buf[j], buf[i-1-j]);
		else
			printf("error\n");
	}

}

void itoa(int num, char buf[])
{
	int i = 0;
	
	/* num 123 to string "321" */
	do 
	{
		buf[i] = num % 10 + '0';
		i++;
		
		num /= 10;
	} while (num != 0);
	buf[i] = '\0';

	reverse(buf, i);

	return;
}


int main(void)
{
	int num = 123;
	char buf[10];

	printf("input a number\n");
	scanf("%d", &num);
	printf("num = %d\n", num);

	itoa(num, buf);

	printf("buf = %s\n", buf);

	return 0;
}
