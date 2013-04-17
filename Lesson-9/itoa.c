#include <stdio.h>

int main(void)
{
	int num = 123;
	char buf[10];
	int i = 0;
	int j = 0;
/*
	buf[0] = '1';
	buf[1] = '2';
	buf[2] = '3';
	buf[3] = '\0';
*/

	printf("input a number\n");
	scanf("%d", &num);
	printf("num = %d\n", num);
	
	/* num 123 to string "321" */
	do 
	{
		buf[i] = num % 10 + '0';
		i++;
		
		num /= 10;
	} while (num != 0);
	buf[i] = '\0';

	/* string "321" to string "123" */
	for (j = 0; j < i/2; j++)
	{
		char tmp;

		tmp = buf[i-1-j];
		buf[i-1-j] = buf[j];
		buf[j] = tmp;
	}

	printf("buf = %s\n", buf);

	return 0;
}
