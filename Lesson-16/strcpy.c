#include <stdio.h>

char c;
int main(void)
{
	int addr;
	char * p;

	c = 'A';
	printf("c = %c %x\n", c, c);
	printf("&c = %p\n", &c);

	addr = (int)&c;
//	printf("addr = 0x%x\n", addr);

	p = (char *)0x1234;
	printf("p = %p\n", p);

	p = (char *)addr;
	printf("*p = 0x%x\n", *p);
//	addr = 0xbfc2ad3f;
	//addr = 0x804a020;
	addr = 0x804a920;
	printf("*addr = 0x%x\n", *(char *)addr);

	printf("exit\n");
	return 0;
}
