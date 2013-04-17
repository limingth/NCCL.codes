#include <stdio.h>
//#include <string.h>
#include <assert.h>

char s1[16];

#define CONTAIN_OF_ZERO_BYTE(n)	\
	( ((n-0x01010101) & (~n)) & 0x80808080 )

/* n = 0x12340078 */

#define TEST(n)		( ((n-1) & (~n)) & 0x80 )

#if 0
n = 0	-> 0xFF & 0xFF = 0xFF
n = 1	-> 0x00 & 0xFE = 0x0
n = 2 	-> 0x01 & 0xFD = 0x1

n = FF ->              = 0b 0xxx xxxx
n = 0xxx xxxx
-1          1

#endif

char *mystrcpy3(char * dest, const char * src)
{
	int * s;
	int * d;
	char * p = dest;

	s = (int *)src;
	d = (int *)dest;
	while (1)
	{
		if (!CONTAIN_OF_ZERO_BYTE(*s))
		{
			printf("int *S is copied %x\n", *s);
			*d = *s;
			s++;
			d++;
			continue;
		}
		
		src = (char *)s;
		dest = (char *)d;

		while (*dest++ = *src++);
		break;
	}

	return p;
}

char *mystrcpy(char * dest, const char * src)
{
	char * p = dest;
	int delta = dest - src;
	
#if 0
	if (dest == NULL || src == NULL)
	{
		printf("must be not NULL\n");
		return dest;
	}
#endif
	assert(dest != NULL && src != NULL);

//	while (*dest++ = *src++);
	while (*(char *)(src+delta) = *src++);
 
	return p;
}

int main(void)
{
	char * p = NULL;
	char s2[16] = "hell123456789";
	unsigned int n;
#if 0
	for (n = 0x00; n <= 0xFF; n++)
	{
		printf("n = %x, TEST(n) = %x\n", n, TEST(n));
	}
	return 0;
#endif

	printf("1) s1 = %s\n", s1);
	mystrcpy3(s1, s2);
	printf("2) s1 = %s\n", s1);

	return 0;
}
