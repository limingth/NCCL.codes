#include <stdio.h>
#include <assert.h>

#if 0
char * my_strcpy(char * dst, const char * src)
{
	assert(dst != NULL && src != NULL);

	char * ret = dst;

	while ((*dst++ = *src++) != '\0');

	return ret;
}
#else
char * my_strcpy(char * dst, const char * src)
{
	char * ret = dst;

	printf("strcpy demo\n");

	assert(dst != NULL && src != NULL);

#if 0
	while((*dst++ = *src++) != '\0');
#endif

	while ((*dst = *src) != '\0')
	{
		printf("++\n");
		dst++;
		src++;
	}

	return ret;
}
#endif

void my_strcpy4(char dst[], const char src[])
{
	int i = 0;

	printf("strcpy4 demo\n");

	while ((dst[i] = src[i]) != '\0')
		i++;
#if 0
	do
	{
		dst[i] = src[i];
	} while (src[i++] != '\0');
#endif

	return;
}

void my_strcpy3(char dst[], const char src[])
{
	int i = 0;

	do
	{
		dst[i] = src[i];
	} while (src[i++] != '\0');

	return;
}


void my_strcpy2(char dst[], const char src[])
{
	int i = 0;

	printf("strcpy2 demo\n");

	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = src[i];

	return;
}

char * d2;

int main(int argc, char *argv[])
{
	char d[32];
	char s[32] = "Hello World";

	printf("s = %s\n", s);

	printf("d = %s\n", d);

	d2 = d;
	my_strcpy(d2, s);

	printf("d = %s\n", d);

	//    printf("d = %s\n", my_strcpy(d, s));

	return 0;
}

