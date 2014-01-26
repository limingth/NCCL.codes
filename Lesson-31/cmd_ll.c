#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>


int ll_main(int argc, char *argv[])
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
	
	int option_i = 0;
	int option_s = 0;
	int option_T = 0;

	if (argc > 2)
	{
		switch (argv[2][1])
		{
		case 'i':
			option_i = 1;
			break;
		case 's':
			option_s = 1;
			break;
		case 'T':
			option_T = 1;
			break;
		}	
	}

	struct stat buf;

	stat(argv[1], &buf);

	#define SIZE 256
	char buffer[SIZE];
	time_t curtime;
	struct tm *loctime;

	/* Convert it to local time representation. */
	loctime = localtime (&buf.st_mtime);

	if (option_i == 1)
	{
		printf("file st_ino = %lld\n", buf.st_ino);
		return 0;
	}
	if (option_s == 1)
	{
		printf("file st_blocks = %lld\n", buf.st_blocks);
		return 0;
	}
	if (option_T == 1)
	{
		strftime (buffer, SIZE, "The time is %m %d %H:%M:%S %Y\n", loctime);
		fputs (buffer, stdout);
		return 0;
	}

	printf("Access mode: 0%o\n", buf.st_mode);
	printf("file uid = %s\n", (getpwuid(buf.st_uid))->pw_name);
	printf("file size = %lld\n", buf.st_size);
	//printf("file last access atime = %s", ctime(&buf.st_atime));
	printf("file last modify mtime = %s", ctime(&buf.st_mtime));
	//printf("file last status change ctime = %s", ctime(&buf.st_ctime));

	/* Print out the date and time in the standard format. */
	//fputs (asctime (loctime), stdout);

	/* Print it out in a nice format. */
	//strftime (buffer, SIZE, "Today is %A, %B %d.\n", loctime);
	//fputs (buffer, stdout);
	strftime (buffer, SIZE, "The time is %m %d %H:%M:%S %Y\n", loctime);
	fputs (buffer, stdout);
	
	return 0;
}

