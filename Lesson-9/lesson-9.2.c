#include <stdio.h>

void itoa(int num, char buf[])
{
	int i = 0;
	int len = 0;

	do 
	{
		buf[i++] = num % 10 + '0';
		num /= 10;		
	} while (num);
	buf[i] = '\0';

	len = i;
	for (i = 0; i < len/2; i++)
	{
		char tmp;
		tmp = buf[i];
		buf[i] = buf[len-i-1];
		buf[len-i-1] = tmp;
	}

	return;
}

int main(void)
{	
	int num;
	char buf[100];

	printf("Please input a number: ");
	scanf("%d", &num);

	itoa(num, buf);

	printf("number string = %s\n", buf);

	return 0;	
}
