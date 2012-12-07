#include <stdio.h>
#include <assert.h>

#if 1
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

	while((*dst++ = *src++) != '\0');

	return ret;
}
#endif

int main(int argc, char *argv[])
{
    char d[32];
    char s[32] = "Hello World";

    printf("s = %s\n", s);

//	my_strcpy(d, s);
    printf("d = %s\n", my_strcpy(d, s));
	
    return 0;
}

