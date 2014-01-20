#include <stdio.h>

void putchar_hex(char c)
{
	const char * hex = "0123456789ABCDEF";  // good
	//char hex[] = "0123456789ABCDEF";  bad!

	putchar(hex[(c & 0xf0)>>4]);
	putchar(hex[(c & 0x0f)>>0]);
	//putchar(' ');
}

void putint_hex(int a)
{
	putchar_hex( (a>>24) & 0xFF );
	putchar_hex( (a>>16) & 0xFF );
	putchar_hex( (a>>8) & 0xFF );
	putchar_hex( (a>>0) & 0xFF );
}

char * itoa(int num, char * buf)
{   
	int i = 0;
	int len = 0;

	do 
	{
		buf[i++] = num % 10 + '0';
		num /= 10;      
	} while (num);
	buf[i] = '\0';

	len = i;
	for (i = 0; i < len/2; i++)
	{
		char tmp;
		tmp = buf[i];
		buf[i] = buf[len-i-1];
		buf[len-i-1] = tmp;
	}

	return buf; 
}

#if 0
#include <stdarg.h>
#else
//typedef int * va_list;
//#define va_start(ap, A)      (ap = (int *)&(A) + 1)
//#define va_arg(ap, T)        (*(T *)ap++)
//#define va_end(ap)       ((void)0)

/* type definitions */
typedef char *va_list;
/* macros */
#define va_arg(ap, T) \
	(* (T *)(((ap) += _Bnd(T, 3U)) - _Bnd(T, 3U)))
#define va_end(ap) (void)0
#define va_start(ap, A) \
	(void)((ap) = (char *)&(A) + _Bnd(A, 3U))
#define _Bnd(X, bnd) (sizeof (X) + (bnd) & ~(bnd))

#endif

static int myputs(const char * s)
{
	while (*s)
		putchar(*s++);

	return 0;
}


char buf[100]; 

int myprintf(const char * format, ...)
{
	char c;

	va_list ap;

	va_start(ap, format);

	while ((c = *format++) != '\0')
	{
		switch (c)
		{
			case '%':
				c = *format++;

				switch (c)
				{
					char ch;
					char * p;
					int a;

					case 'c':
						ch = va_arg(ap, int);
						putchar(ch);
						break;
					case 's':
						p = va_arg(ap, char *);
						myputs(p);
						break;                  
					case 'x':
						a = va_arg(ap, int);
						putint_hex(a);
						break;      
					case 'd':
						a = va_arg(ap, int);
						itoa(a, buf);
						myputs(buf);
						break;  
					default:
						break;
				}               
				break;      

			default:
				putchar(c);
				break;
		}
	}

	return 0;   
}

int main(void)
{
	printf("test: %c, %s, %d, 0x%x\n", 'A', "abcdef", 11, 0x23);

	myprintf("test: %c, %s, %d, 0x%x\n", 'A', "abcdef", 11, 0x23);

	return 0;
}
