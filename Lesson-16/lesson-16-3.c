#include <stdio.h>
#include <assert.h>

char * my_strcpy(char * dst, const char * src)
{
	assert(dst != NULL && src != NULL);

	char *s = (char *)src;
	int delt = dst - src;

	while ((s[delt] = *s++) != '\0');

	return dst;
}

int main(int argc, char *argv[])
{
    char d[32];
    char s[32] = "Hello World";

    printf("s = %s\n", s);

//	my_strcpy(d, s);
    printf("d = %s\n", my_strcpy(d, s));
	
    return 0;
}

