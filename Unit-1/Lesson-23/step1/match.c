#include <stdio.h>

#define PRINT(x, args...)	fprintf(stderr,"<%d> " x, getpid(), ##args)
//#define PRINT(x, args...)	

int main(int argc, char * argv[])
{
	int people = 0;
	int x = 0, y = 0;

	PRINT("hello, akaedu!\n");

	if (argc < 2)
	{
		PRINT("./a.out who_is_first(pc/people)\n");
		return 0;
	}

	if (strcmp(argv[1], "pc") == 0)
	{
		PRINT("pc first\n");
		people = 2;
	}
	else
	{
		PRINT("people first\n");
		people = 1;
	}

	int step = 0;
	while (step < 10)
	{
		// step = 1, 2, 3, 4, 5, 6
		step = step + 1;
		fprintf(stderr, "step %d: ", step);

		// pc first step (4 4)
		if (people == (step + 1) % 2 + 1)
		{
			scanf("%d %d", &x, &y);
			PRINT("(%d %d) by people\n", x, y);
		}	
		else
		{
		//	x = 4;
		//	y = 4;	
			x++;
			y++;
			printf("%d %d\n", x, y);
			PRINT("(%d %d) by pc\n", x, y);
		}
		
		//sleep(1);
	}
	

	return 0;
}
