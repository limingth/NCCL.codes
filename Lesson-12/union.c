#include <stdio.h>

struct test
{
	int n;
	char test[4];
};

union test2
{
	int n;
	unsigned char test[4];
	float f;
};

typedef union test2 test2_t;

int main(void)
{
	int number;
	test2_t t;	

	number = 0x12345678;
	// little-endian: 0x78 56 34 12
	// big-endian: 0x12 34 56 78
	printf("sizeof struct = %d\n", sizeof(struct test));
	printf("sizeof union = %d\n", sizeof(union test2));

	printf("does your machine use little-endian\n");
/*	
	t.n = 0x12345678;
	printf("test[0] = 0x%x\n", t.test[0]);
	printf("test[1] = 0x%x\n", t.test[1]);
	printf("test[2] = 0x%x\n", t.test[2]);
	printf("test[3] = 0x%x\n", t.test[3]);
	printf("t.n = 0x%x\n", t.n);

	t.test[0] = 0x99;
	printf("t.n = 0x%x\n", t.n);

	t.f = 1.0;
	printf("test[0] = 0x%x\n", t.test[0]);
	printf("test[1] = 0x%x\n", t.test[1]);
	printf("test[2] = 0x%x\n", t.test[2]);
	printf("test[3] = 0x%x\n", t.test[3]);
	printf("t.n = 0x%x\n", t.n);
*/

	// 0x3f800000(int) == 1.0(float)
	t.n = 0x3f800000;
	printf("t.f = %f\n", t.f);

	return 0;
}
