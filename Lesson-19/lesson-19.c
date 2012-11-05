#include <stdio.h>

int shell_parse(char * buf, char * argv[])
{
	int argc = 0;
	int state = 0;
	
	while (*buf)
	{
		if (*buf != ' ' && state == 0)
		{
			argv[argc++] = buf;
			state = 1;
		}
		
		
		if (*buf == ' ' && state == 1)
		{
			*buf = '\0';
			state = 0;
		}
		
		buf++;	
	}
	
	return argc;
}

int main(void)
{
	int argc = 0;
	char * argv[10];
	char str[100] = "ls -l -a /home/ftp";
	int i;

	printf("hello, shell\n");

	printf("str = <%s> \n", str);

	argc = shell_parse(str, argv);

	for (i = 0; i < argc; i++)
		printf("%d: <%s> \n", i, argv[i]);

	return 0;
}
