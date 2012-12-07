#include <stdio.h>

#define ALL_NUM		100
#define COUNT_NUM	3
#define OUT_NUM		3

/* record people's next available position, -1 means OUT */
int next[ALL_NUM];

int main(void)
{
	int left;			/* left people number */
	int pos, prev_pos, next_pos;	/* current pos, previous pos */
	int step;			/* which step */
	int tmp;
	int i;

	int counter = 0;

	left = ALL_NUM;
	pos = 0;
	prev_pos = ALL_NUM - 1;
	step = 0;


	for (i = 0; i < ALL_NUM; i++)
	{
		/* init next position as 1,2,3,4,5,0 */
		next[i] = (i + 1) % ALL_NUM;
	}

	/* if there is still people in queue */
	while (left > 0)
	{
		/* step = 1, 2, 3 */
		step = step % COUNT_NUM + 1;

		/* deal with the people to be out */
		if (step == OUT_NUM)
		{
			/* say who is out */
			printf("%d out \n", pos+1 ); 		
			left--;

			/* set prev_pos' next = this pos' next */
			next[prev_pos] = next[pos];			
		}

		/* save current pos to prev_pos and get next pos */
		prev_pos = pos;
		pos = next[pos];						
	}

	return 0;
}