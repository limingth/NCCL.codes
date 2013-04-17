#include <stdio.h>

int global = 200;
extern _start;

int main(void)
{
	int local = 100;

	printf("_start is %p\n", &_start);

	printf("hello, world.\n");
	printf("local = %d\n", local);
	printf("local = 0x%x\n", local);

	printf("global = %d\n", global);
	printf("global = 0x%x\n", global);

	printf("&local = %p\n", &local);
	printf("&global = %p\n", &global);
	printf("main = %p\n", main);

	return 0;
}
