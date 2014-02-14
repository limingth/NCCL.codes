#include <stdlib.h>
#include <stdio.h>

#include "clist.h"

link make_node(void *data)
{
	link p = malloc(sizeof(*p));
	
	p->data = data;
	p->next = NULL;

	return p;	
}

void delete_node(link p)
{
	free(p->data);
	free(p);

	return;	
}

link clist_tail(link cur)
{
	link p = cur;

	while (p->next != cur)
		p = p->next;

	return p;
}

int clist_length(link cur)
{
	link p = cur;
	int count = 0;

	if (cur == NULL)
		return 0;

	do
	{
		count++;
		p = p->next;
	} while (p != cur);

	return count;
}

link clist_insert_after(link cur, link item)
{
	if (cur == NULL)
	{
		item->next = item;
		return item;
	}

	// insert item after cur
	item->next = cur->next;
	cur->next = item;	

	return item;
}

link clist_delete(link cur, link item)
{
	link p = cur;

	// only 1 item left in the ring
	if (item->next == item)
	{
		delete_node(item);
		return NULL;
	}

	do 
	{
		if (p->next == item)
		{
			link q = p->next;

			p->next = q->next;
			delete_node(q);
			return p->next;
		}
		p = p->next;
	} while (p != cur);
	return p;
}

void clist_print(link cur, void (*pf)(void *))
{
	link p = cur;

	if (cur == NULL)
		return;

	do 
	{
		pf(p->data);
		p = p->next;
	} while (p != cur);
	printf("\n");

	return;
}

void print_int_data(void *data)
{
	if (data)
		printf("%d ", *(char *)data);

	return;
}

int *make_data(int data)
{
	int *p = malloc(sizeof(int));

	*p = data;

	return p;	
}

