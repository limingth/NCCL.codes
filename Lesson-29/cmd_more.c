#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include <termios.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>	// STDIN_FILENO

int width;
int height;	// 80*24 -> display only line 0 -> line 22, last line is for command

void get_termios(void)
{
	struct winsize *ws;

	ws=(struct winsize*)malloc(sizeof(struct winsize));
	memset(ws,0x00,sizeof(struct winsize));
	ioctl(STDIN_FILENO, TIOCGWINSZ, ws);

	width=ws->ws_col;
	height=ws->ws_row;

	printf("w = %d, h = %d\n", width, height);

	return;
}

void set_no_echo(void)
{
	struct termios ts; //终端属性

	tcgetattr(STDIN_FILENO,&ts); //获取终端属性 
	ts.c_lflag &= (~ECHO); //阻止回显
	tcsetattr(STDIN_FILENO,TCSAFLUSH,&ts); //设置终端的新属性
}

void set_echo(void)
{
	struct termios ts; //终端属性

	tcgetattr(STDIN_FILENO,&ts); //获取终端属性 
	ts.c_lflag |= ECHO;	// 开启回显
	tcsetattr(STDIN_FILENO,TCSAFLUSH,&ts); //设置终端的新属性
}

void set_no_enter(void)
{
	struct termios ts; //终端属性

	tcgetattr(STDIN_FILENO,&ts);	//获取终端属性 
	ts.c_lflag &= (~ICANON);	//设置终端为非标准模式，在非标准模式下终端驱动程序没有缓冲区，输入立即交换程序处理
	ts.c_cc[VMIN]=1;	//VMIN的值告诉驱动程序一次可以读取多少个字符。如果想一次读取3个字符就设为3
	ts.c_cc[VTIME]=0;	//VTIME设置超时
	tcsetattr(STDIN_FILENO,TCSAFLUSH,&ts);	//设置终端的新属性 
}

int top = 0;
int dropdown = 0;	// all lines from top to bottom

char *pv[1024];		// every line buffer pointer array
int lines = 0;		// total lines in file

void display(void)
{
	int i = 0;

	for (i = 0; i < dropdown; i++)	
		printf("%s", pv[top+i]);
}

int more_main(int argc, char *argv[])
{
	FILE *fp;

	if (argc < 2)
	{
		printf("Usage: more filename\n");
		return -1;
	}

	fp = fopen(argv[1], "rb");
	if (fp == NULL)
	{
		printf("file <%s> open error\n", argv[1]);
		return -1;
	}
	// verify that fp1 not NULL
	assert(fp);
	
	char buf[1024];

	// http://www.programmer-club.com/showsametitlen/c/39966.html
	while (fgets(buf, 1024, fp))
	{
		//printf("lines %d: %s", lines, buf);
		pv[lines] = malloc(strlen(buf) + 1);
		strcpy(pv[lines], buf);
		lines++;
	}
	printf("lines = %d\n", lines);

	get_termios();
	set_no_echo();
	set_no_enter();

	top = 0;
	if (lines <= height - 1)
	{
		dropdown = lines;
		goto quit;
	}
	else
		dropdown = height - 1;

	while (1)
	{            
		system("clear");
		display();
		printf(":");

		char c;
		// get user input
		if ((c = getc(stdin)) == EOF)
			break;

		switch (c)
		{
		case 'q':
			goto quit;
		case 'k':	// up
			if (top == 0)
				continue;
			top -= 1;
			break;
		case '\n':	// enter
		case 'j':	// down
			if (top + 1 + dropdown > lines)
				goto quit;
			top += 1;
			break;
		case ' ':	// down a page
			if (top + height - 1 + dropdown > lines)
			{
				top = lines - dropdown;
				goto quit;
			}
			top += height - 1;
			break;
		case 'b':	// up a page
			if (top - (height - 1) < 0)
			{
				top = 0;
				continue;
			}
			top -= height - 1;
			break;
		}
	}

quit:
	display();
	set_echo();
	return 0;
}
