#include <stdio.h>
#include "yy_nxt.c"
#include "yy_accept.c"

#define debug(fmt, args...)	fprintf(stderr, fmt, ##args)

int main(void)
{
	int state = 1;
	char buf[64];
	int i = 0;

	while (1)
	{
		char c;

		c = getchar();
		if (c == EOF)
			break;

		buf[i++] = c;

		debug("\tstate = %d, ", state);

		state = yy_nxt[state][c];

		debug("c = <%c>, new state = %d\n", c, state);

		if (state < 0)
		{
			int act = 0;

			state = -state;
			act = yy_accept[state];
			buf[i-1] = '\0';

			// 1: \n   21: space
			if (!(act == 1 || act == 21))
				printf("\tPattern %2d found: %s\n", act, buf);
			i = 0;

			state = 1;
			ungetc(c, stdin);
		}
	}

	return 0;
}
