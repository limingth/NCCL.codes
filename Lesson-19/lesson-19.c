#include <stdio.h>
#include <string.h>

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


		if ((*buf == ' ') && state == 1)
		{
			*buf = '\0';
			state = 0;
		}

		buf++;	
	}

	return argc;
}

int do_cmd(int argc, char ** argv)
{
	int i;

	printf("argc = %d\n", argc);

	for (i = 0; i < argc; i++)
		printf("argv[%d]: <%s>\n", i, argv[i]);	

	return 0;
}

int do_add(int argc, char ** argv)
{
	printf("help: this is a add function with %d args\n", argc - 1);

	return 0;
}

int do_sub(int argc, char ** argv)
{
	printf("ls: this is a sub function with %d args\n", argc - 1);

	return 0;
}

int (*pf)(int argc, char ** argv);

int main(void)
{
	char buf[64];
	int argc = 0;
	char * argv[10];

	printf("$ ");
	fgets(buf, 64, stdin);
	buf[strlen(buf)-1] = '\0';
	printf("<%s>\n", buf);

	argc = shell_parse(buf, argv);

	pf = do_cmd;	
	if (strcmp(argv[0], "add") == 0)					
		pf = do_add;	

	if (strcmp(argv[0], "sub") == 0)
		pf = do_sub;	

	pf(argc, argv);
	//callback(pf，argc, argv);

	return 0;
}
