#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define SIZE	512
#ifdef DEBUG
#define debug(fmt, args...) 	fprintf(stderr, fmt, ##args)
#else
#define debug(fmt, args...) 	;
#endif

int sed_main(int argc, char *argv[])
{
	int i = 0;

	if (argc < 2)
	{
		printf("Usage: sed pattern\n");
		return -1;
	}

	char buf[SIZE];
	int n;
	// [2addr]s/regular expression/replacement/flags from man strtok
	char *cmd, *regexp, *replace, *flags = NULL;

	// parse pattern like 's/unix/linux'
	debug("patter = %s\n", argv[1]);

	// cmd = s
	cmd = strtok(argv[1], "/");
	debug("cmd = %s\n", cmd);

	// regexp = unix
	regexp = strtok(NULL, "/");
	debug("regexp = %s\n", regexp);

	// replace = linux 
	replace = strtok(NULL, "/");
	debug("replace = %s\n", replace);
	
	// flags = "", "g", "3" 
	flags = strtok(NULL, "/");
	debug("flags = %s\n", flags);

	fgets(buf, SIZE, stdin);
	//strcpy(buf, "I love unix. Linux is GNU is not unix");
	debug("%s", buf);

	char *cursor = buf;
	char *occur;
	int counter = 0;

	while (1)
	{
		occur = strstr(cursor, regexp);
		if (occur == NULL)
			break;

		counter++;
		debug("occur = %s\n", occur);
		for (i = 0; i < occur - cursor; i++)
			putchar(*(cursor+i));
		
		if (flags == NULL)
		{
			if (counter == 1)
				printf("%s", replace);
			else
				printf("%s", regexp);
		}
		else	
		if (strcmp(flags, "g") == 0)
			printf("%s", replace);
		else
		{
			if (isdigit(*flags) && *flags - '0' == counter)
				printf("%s", replace);
			else
				printf("%s", regexp);
		}
	
		cursor += occur - cursor + strlen(regexp);
		debug("cursor = %s\n", cursor);
	} 

	for (i = 0; *(cursor+i) != '\0'; i++)
		putchar(*(cursor+i));

	return 0;
}
