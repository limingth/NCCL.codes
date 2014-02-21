#include <stdio.h>
#include <ctype.h>
#include <string.h>

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
	return top == 0;
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

int calc_suffix(char * buf)
{
	//char buf[] = "12+5*4+";

	// 1+2*3-4
	//char buf[] = "123*+4-";
	int i = 0;
	char c;
	int ret;

	puts(buf);

	while ((c = buf[i]) != '\0')
	{
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

	ret = pop();
	printf("result is %d\n", ret);

	return ret;
}

static int operand_stack[512];
static int operand_top = 0;

int pop_operand(void)
{
	printf("pop %d\n", operand_stack[operand_top-1]);
	return operand_stack[--operand_top];
}

void push_operand(int item)
{
	printf("push %d\n", item);
	operand_stack[operand_top]= item;
	operand_top++;
	return;
}

int operand_is_empty(void)
{
	return operand_top == 0;
}

static char operator_stack[512];
static int operator_top = 0;

int get_top_operator(void)
{
	return operator_stack[operator_top-1];
}

int pop_operator(void)
{
	printf("pop %c\n", operator_stack[operator_top-1]);
	return operator_stack[--operator_top];
}

void push_operator(char item)
{
	printf("push %c\n", item);
	operator_stack[operator_top]= item;
	operator_top++;
	return;
}

int operator_is_empty(void)
{
	return operator_top == 0;
}

int prio(char op)
{
	switch (op)
	{
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	}
	return 0;
}

int infix_to_suffix(char *infix, char *suffix)
{
	char c;
	int i = 0;
	int j = 0;

	while ((c = infix[i++]) != '\0')
	{
		if (c == ' ')
			continue;

		printf("%c\n", c);
		//usleep(200*1000);

		if (isdigit(c))
		{
			//push_operand(c);
			suffix[j++] = c;
			printf("write operand %c\n", c);
		}
		else if (c == '(')
			push_operator(c);
		else if (c == ')')
		{
			while (!operator_is_empty())
			{
				char operator = pop_operator();
				if (operator == '(')
					break;

				suffix[j++] = operator;
				printf("write op %c\n", operator);
			} 
		}
		else 
		{
			char op = get_top_operator();

			if (prio(op) >= prio(c))
			{
				op = pop_operator();
				suffix[j++] = op;
				printf("write op %c\n", op);
			}
			push_operator(c);
		}
	}
	
	while (!operator_is_empty())
	{
		char operator = pop_operator();

		suffix[j++] = operator;
		printf("write op %c\n", operator);
	}
	suffix[j] = '\0';

	return 0;
}

int main(void)
{
	char infix[64];
	char suffix[64];
	int ret;

	strcpy(infix, "5 + ((1 + 2) * 4) - 3");
	printf("infix = <%s>\n", infix);
	infix_to_suffix(infix, suffix);

	printf("suffix = <%s>\n", suffix);

	ret = calc_suffix(suffix);
	printf("%d\n", ret);

	return 0;
}
