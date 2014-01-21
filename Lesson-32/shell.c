#include <stdio.h>
#include <string.h>

int mycp_main(int, char**);
int readelf_main(int, char**);

struct operation
{
	char name[8];
	int (*pf)(int, char **);
} op[] =
{
	{ "mycp", mycp_main },
	{ "readelf", readelf_main },
	// add more opeation here
};

int command_do(int argc, char *argv[])
{
	int i = 0;

	for (i = 0; i < sizeof(op)/sizeof(op[0]); i++)
	{
		if (strcmp(argv[0], op[i].name) == 0)
		{
			op[i].pf(argc, argv);
			break;
		}
	}

	return 0;
}

void shell_parse(char *buf)
{
	int argc;
	char *argv[8];
	int state = 0;
	int i = 0;

	argc = 0;
	// parse buf	
	while (*buf)
	{
		char c = *buf;
		if(c == ' ' && state == 0)	// "   add 100"
			state = 0;
		else
		if(c != ' ' && state == 0)	// "add 100"
		{
			argv[argc++] = buf;
			state = 1;
		}
		else
		if(c == ' ' && state == 1)	// "a dd 100"
		{
			*buf = '\0';
			state = 0;
		}
		else
		if(c != ' ' && state == 1)	// "add 100"
		{
			state = 1;
		}
		buf++;
		if (*buf == '\n')
			*buf = '\0';
	}

	argv[argc] = NULL;
	printf("argc = %d\n", argc);
	for (i = 0; i <= argc; i++)
		printf("argv[%d] : %s\n", i, argv[i]);

	command_do(argc, argv);

}

//int main(void)
//int main(int argc, char *argv[])
int main(int argc, char *argv[], char *env[])
{
	int i = 0;
	char buf[64];

	printf("demo argc & argv \n");

	//scanf("%s", buf);
	//gets(buf);
	while (1)
	{
		printf("NCCL# ");
		fgets(buf, 64, stdin);
		printf("buf = %s\n", buf);
		
		shell_parse(buf);
	}

	return 0;
}
