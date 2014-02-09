#include <stdio.h>
#include <ctype.h>

static int stack[512];
static int top = 0;

int pop(void)
{
	printf("pop %d\n", stack[top-1]);
	return stack[--top];
}

void push(char item)
{
	printf("push %d\n", item);
	stack[top]= item;
	top++;
	return;
}

int is_empty(void)
{
	return top == -1;
}

int test_main(void)
{
	push('1');
	push('2');
	push('3');

	while (!is_empty())
	{
		putchar(pop());
	}

	return 0;
}

int main(void)
{
	//char buf[] = "12+5*4+";

	// 1+2*3-4
	char buf[] = "123*+4-";
	int i = 0;
	char c;

	puts(buf);

	while ((c = buf[i]) != '\0')
	{
		int ret;

		if (isdigit(c))
			push(c - '0');
		else
		{
			int op2 = pop();
			int op1 = pop();

			printf("%d", op1);
			putchar(c);
			printf("%d = ", op2);

			switch (c)
			{
			case '+':
				ret = op1 + op2;
				push(ret);	
				break;
			case '*':
				ret = op1 * op2;
				push(ret);	
				break;
			case '-':
				ret = op1 - op2;
				push(ret);	
				break;
			}
		}

		i++;
	}

	printf("result is %d\n", pop());

	return 0;
}
