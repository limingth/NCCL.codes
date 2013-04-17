/*
 * sum9-2.c 	-	sumary how many digit from 1 to 100
 *
 * Author: li ming <limingth@gmail.com>
 * Create Date: 2013-3-26
 * Revision 1.1
 * 	+ debug printf
 */
#include <stdio.h>

/*
 * count - count how many digit in num
 * @num: the number from 1 to 100
 * @digit: digit can be 0, 1, 2, 3, ... 9
 *
 * return value: the counter of digit in this num
 */
int count(int num, int digit)
{
	int counter = 0;

	do
	{
		if (num % 10 == digit)
			counter++;
		
		num /= 10;
	} while (num != 0);

	return counter;
}

int main(void)
{
	int i = 0;
	int sum = 0;	/* the sumary of 9 */
	int max = 0;	/* the max number to count */

	printf("sumary 9 from 1 to 100\n");
	scanf("%d", &max);

	/* sumary 9 from 0 to max */
	for (i = 0; i <= max; i++)
	{
		sum += count(i, 9);	
	}

	printf("sum = %d\n", sum);

	return 0;
}
