#include <stdio.h>

int strlen(const char * s)
{
        const char * p = s;

        while (*p)
                p++;

        return (p - s);
}

char * reverse(char * s)
{
        static int counter = 0;
        static char * p;
        char save;

        if (counter == 0)
                p = s;

        counter++;

        if (*s == '\0')
        {
                counter = 0;
                return s;
        }

        save = s[0];
        reverse(s+1);
        *p++ = save;

        return s;
}

char * reverse_r(char * s)
{
        int len = strlen(s);
        char c1 = s[0];
        char c2 = s[len-1];

        if (*s == '\0')
                return s;

        s[len-1] = '\0';

        reverse_r(s+1);

        s[0] = c2;
        s[len-1] = c1;

        return s;
}

char * reverse0(char * s)
{
        int len = strlen(s);
        int i;

        for (i = 0; i < len / 2; i++)
        {
                char tmp;

                tmp = s[i];
                s[i] = s[len-i-1];
                s[len-i-1] = tmp;
        }

        return s;
}

void itoa(int num, char buf[])
{
	int i = 0;
	int len = 0;

	do 
	{
		buf[i++] = num % 10 + '0';
		num /= 10;		
	} while (num);
	buf[i] = '\0';

	reverse(buf);

	return;
}

int main(void)
{	
	int num;
	char buf[100];

	printf("Please input a number: ");
	scanf("%d", &num);

	itoa(num, buf);

	printf("number string = %s\n", buf);

	return 0;	
}
