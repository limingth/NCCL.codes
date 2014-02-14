#include <stdio.h>
#include "clist.h"

int main(void)
{
	link cursor = NULL;
	int i = 0;

	clist_print(cursor, print_int_data);

	for (i = 0; i < 100; i++)
	{
		int *p = make_data(i+1);
		link item = make_node(p);
		cursor = clist_insert_after(cursor, item);
	}

	cursor = cursor->next;
	clist_print(cursor, print_int_data);
	printf("ring list length = %d\n", clist_length(cursor));

	int step = 0;
	while (cursor != NULL)
	{
		print_int_data(cursor->data);
		step++;

		if (step == 3)	
		{
			printf("-> %d out\n", *(int *)(cursor->data));
			cursor = clist_delete(cursor, cursor);
			printf("length = %d\n", clist_length(cursor));
			step = 0;
		}
		else
			cursor = cursor->next;

		//getchar();
		//sleep(1);
	}

	return 0;
}


