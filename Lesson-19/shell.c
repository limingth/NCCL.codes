#include <stdio.h>

int (*pf)(int, int);
char opchar;

int power(int a, int b)
{
	int result = 1;
	int i;

	for (i = 0; i < b; i++)
		result *= a;
	
	return result;
}

int add(int a, int b)
{
	return a+b;
}

int sub(int a, int b)
{
	return a-b;
}

int mul(int a, int b)
{
	return a*b;
}

int div(int a, int b)
{
	if (b != 0)
		return a/b;

	return 0;
}

int math_main(int argc, char *argv[])
{
	int a, b;
	int result;

	if (argc < 3)
	{
		printf("argc = %d, para is too few\n", argc);
		return -1;
	}

	a = atoi(argv[1]);
	b = atoi(argv[2]);

//	result = add(a, b);
//	result = sub(a, b);
	result = pf(a, b);
	
	printf("result: %s %c %s = %d\n", argv[1], opchar, argv[2], result);

	return 0;
}
#if 0
int sub_main(int argc, char *argv[])
{
	int a, b;

	if (argc < 3)
	{
		printf("argc = %d, para is too few\n", argc);
		return -1;
	}

	a = atoi(argv[1]);
	b = atoi(argv[2]);

	printf("sub result: %s + %s = %d\n", argv[1], argv[2], a-b);

	return 0;
}

int add_main(int argc, char *argv[])
{
	int a, b;

	if (argc < 3)
	{
		printf("argc = %d, para is too few\n", argc);
		return -1;
	}

	a = atoi(argv[1]);
	b = atoi(argv[2]);

	printf("add result: %s + %s = %d\n", argv[1], argv[2], a+b);

	return 0;
}
#endif

struct operation
{
	char name[8];
	int (*pf)(int, int);
	char opchar;
} op[] =
{
	{ "add", add, '+' },
	{ "sub", sub, '-' },
	{ "mul", mul, 'x' },
	{ "div", div, '/' },
	{ "p", power, '^' }
	// add more opeation
};

int command_do(int argc, char *argv[])
{
	int i = 0;
#if 0
	if (strcmp(argv[0], "add") == 0)
		//add_main(argc, argv);
		pf = add;

	if (strcmp(argv[0], "sub") == 0)
		//sub_main(argc, argv);
		pf = sub;
#endif

	for (i = 0; i < sizeof(op)/sizeof(op[0]); i++)
	{
		if (strcmp(argv[0], op[i].name) == 0)
		{
			pf = op[i].pf;
			opchar = op[i].opchar;
			break;
		}
	}

	math_main(argc, argv);

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
#if 0
	printf("argc = %d\n", argc);
	for (i = 0; i <= argc; i++)
		printf("argv[%d] : %s\n", i, argv[i]);

	for (i = 0; i <= 3; i++)
		printf("env[%d] : %s \n", i, env[i]);
#endif

	return 0;
}
