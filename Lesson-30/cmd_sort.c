#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>


static char *pv[1024];		// every line buffer pointer array
static int lines = 0;		// total lines in file

int option_u = 0;
int option_r = 0;
int option_n = 0;

static void display(void)
{
	int i = 0;
	char prev_line[1024] = "";

	if (option_u == 0)	
	{
		for (i = 0; i < lines; i++)	
			printf("%s", pv[i]);
	}
	else
	{
		for (i = 0; i < lines; i++)	
		{
			if (strcmp(pv[i], prev_line) == 0)
				continue;	
			printf("%s", pv[i]);
			strcpy(prev_line, pv[i]);
		}
	}
}

int cmp_str(const void *s1, const void *s2)
{
//	printf("pv: %p\n", pv);
//	printf("sizeof int : %d\n", sizeof(int));
//	printf("sizeof char *: %d\n", sizeof(char *));
//	printf("line1: %p, line2: %p\n", s1, s2);

	char *line1 = (char *)(*(char **)s1);
	char *line2 = (char *)(*(char **)s2);

//	printf("line1: %p, line2: %p\n", line1, line2);
//	printf("line1: %s, line2: %s\n", line1, line2);

	return strcmp(line1, line2);
}

int cmp_str_r(const void *s1, const void *s2)
{
	char *line1 = (char *)(*(char **)s1);
	char *line2 = (char *)(*(char **)s2);

	return (-1)*strcmp(line1, line2);
}

int cmp_str_n(const void *s1, const void *s2)
{
	char *line1 = (char *)(*(char **)s1);
	char *line2 = (char *)(*(char **)s2);

	return atoi(line1) - atoi(line2);
}

int sort_main(int argc, char *argv[])
{
	FILE *fp;

	fp = fopen(argv[1], "rb");
	if (fp == NULL)
	{
		printf("file <%s> open error\n", argv[1]);
		return -1;
	}
	// verify that fp1 not NULL
	assert(fp);
	
	// http://www.programmer-club.com/showsametitlen/c/39966.html
	char buf[1024];
	lines = 0;
	while (fgets(buf, 1024, fp))
	{
	//	printf("lines %d: %s", lines, buf);
		pv[lines] = malloc(strlen(buf) + 1);
	//	printf("%s: malloc at %p \n", buf, pv[lines]);
		strcpy(pv[lines], buf);
		lines++;
	}
	fclose(fp);
	//printf("lines = %d\n", lines);

	if (argc > 2)
	{
		switch (argv[2][1])
		{
		case 'u':
			option_u = 1;
			break;
		case 'r':
			option_r = 1;
			break;
		case 'n':
			option_n = 1;
			break;
		}	
	}

	display();
	printf("--- after sort ---\n");

	if (option_r == 1)	
		qsort(pv, lines, sizeof(char *), cmp_str_r);
	else if (option_n == 1)	
		qsort(pv, lines, sizeof(char *), cmp_str_n);
	else 
		qsort(pv, lines, sizeof(char *), cmp_str);
	display();

	printf("\n");
	return 0;
}
