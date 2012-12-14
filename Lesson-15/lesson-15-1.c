#include <stdio.h>

int get_bit(int num, int pos)
{
	if (num & (1<<pos))
		return 1;

	return 0;
}

int set_bit(int num, int pos, int value)
{
	if (value)
		return (num | (1<<pos));

	return (num & ~(1<<pos));
}

int count_bit_1(int num)
{
	int sum = 0;
	int i = 0;

	for (i = 0; i < 32; i++)
		sum += get_bit(num, i);

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
