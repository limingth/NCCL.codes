#include <stdio.h>

void itoa(int num, char *buf, int base)
{
	char * hex = "0123456789ABCDEF";
	//char hex[] = "0123456789ABCDEF";
	int i = 0;
	int j = 0;

	do
	{
		int rest;

		rest = num % base;
		buf[i++] = hex[rest];	// *(hex+rest)
		num /= base;
	} while (num != 0);

	buf[i] = '\0';

#define SWAP(a, b)		\
	do \
	{ 			\
	  a = (a) ^ (b);	\
	  b = (a) ^ (b);	\
	  a = (a) ^ (b);	\
	} while (0)

	// reverse buf
	for (j = 0; j < i / 2; j++)
	{
		SWAP(buf[j], buf[i-1-j]);
	}
	return;
}
 
void myputs(char *buf)
{
	while (*buf)
		putchar(*buf++);

	return;
}

	char buf[32];

#include <stdarg.h>
// va_list xxx;
// va_start()
// va_arg()
// va_end()

int myprintf(const char * format, ...)
{
//	int * p;
	va_list ap;
	char c;
	int value;

//	p = (int *)&format;
//	p++;
//	printf("p = %x\n", (int)p);
	va_start(ap, format);
	//printf("ap = %x\n", (int)ap);

	while ((c = *format++) != '\0')
	{
		if (c != '%')
		{
			putchar(c);	
			continue;
		}
		else
		{
			// get next char after '%'
			c = *format++;
			if (c == 's')
			{
				//value = *p++;
				//value = va_arg(ap, char *);
				//myputs((char *)value);
				myputs(va_arg(ap, char *));
			}

			if (c == 'c')
			{
				//value = *p++;
				//value = (int)va_arg(ap, char);
				//putchar((char)value);
				//putchar((int)va_arg(ap, char));
				putchar(va_arg(ap, int));
			}
			if (c == 'd')
			{
				//value = *p++;
//				printf("<%d>", value);
				value = va_arg(ap, int);
				itoa(value, buf, 10);
				myputs(buf);
				//printf("ap = 0x%x\n", (int)ap);
				//printf("va_arg value = %d\n", value);
			}
			if (c == 'x')
			{
				//value = *p++;
				value = va_arg(ap, int);
//				printf("%x", value);
				itoa(value, buf, 16);
				myputs(buf);
				//printf("ap = 0x%x\n", (int)ap);
				//printf("va_arg value = %d\n", value);
			}
		}
	}

	va_end(ap);
	//printf("ap = 0x%x\n", (int)ap);

	return 0;
}

int test(int a, int b, int c, int d)
{
	int * p;
	char buff[32];

	p = &a;
	printf("*p = %d\n", *p);
	p++;
	printf("*p = %d\n", *p);
	p++;
	printf("*p = %d\n", *p);
	p++;
	printf("*p = %d\n", *p);

	printf("&a = %p\n", &a);
	printf("&b = %p\n", &b);
	printf("&c = %p\n", &c);
	printf("&d = %p\n", &d);

	return 0;
}

int main(void)
{
	char buf[32];

//	test(100, 200, 300, 400);
//	myprintf("a = %d\n", 100);
	//myprintf("a = %d\n", 100, 200);
#if 0
	itoa(100, buf, 10);
	puts(buf);

	itoa(100, buf, 16);
	puts(buf);
#endif

	myprintf("a = %d, b = 0x%x\n", 100, 200);
	myprintf("c = %c, s = %s\n", 'A', "helloworld");

	return 0;
}
