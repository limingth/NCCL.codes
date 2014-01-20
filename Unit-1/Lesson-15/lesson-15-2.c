#include <stdio.h>

int count_bit_1(int num)
{
	int sum = 0;

	while(num)
	{
		sum++;
		num &= num - 1;
	}

	return sum;
}

int main(int argc, char *argv[])
{
	int num;
	
 	printf("please input a number:");
	scanf("%d", &num);
	printf("number in hex is 0x%x\n", num);
	
	printf("%d bit '1' in %d\n", count_bit_1(num), num);
    
	return 0;
}
