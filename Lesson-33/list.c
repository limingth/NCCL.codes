#include <stdlib.h>
#include <stdio.h>

#include "list.h"

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

link list_new(void)
{
	link head = make_node(NULL);

	return head;
}

link list_tail(link head)
{
	link p = head;

	while (p->next != NULL)
		p = p->next;

	return p;
}

void list_insert_after(link where, link item)
{
	item->next = where->next;
	where->next = item;

	return;
}

link list_insert_tail(link head, link item)
{
	link tail = list_tail(head);

	tail->next = item;	
	item->next = NULL;

	return head;
}

link list_delete(link head, link item)
{
	link p = head;

	while (p)
	{
		if (p->next == item)
		{
			link q = p->next;

			p->next = q->next;
			delete_node(q);
			return head;
		}
			 
		p = p->next;

	}
	return p;
}


link list_search(link head, link item)
{
	link p = head;

	while (p != NULL && p->data != item->data)
		p = p->next;

	return p;
}

void list_print(link head, void (*pf)(void *))
{
	link p = head;

	while (p)
	{
		//printf("p->data = %p\n", p->data);
		pf(p->data);
		p = p->next;
	}
	printf("\n");

	return;
}

void print_char_data(void *data)
{
	if (data)
		printf("%c -> ", *(char *)data);

	return;
}


char *make_data(char data)
{
	char *p = malloc(sizeof(char));

	*p = data;

	return p;	
}

int list_main(void)
{
	link head = NULL;
	link item = NULL;
	char *p = NULL;

	head = list_new();

	list_print(head, print_char_data);

	p = make_data('a');
	item = make_node(p);
	list_insert_tail(head, item);
	list_print(head, print_char_data);

	p = make_data('b');
	item = make_node(p);
	list_insert_tail(head, item);
	list_print(head, print_char_data);

	p = make_data('c');
	item = make_node(p);
	list_insert_tail(head, item);
	list_print(head, print_char_data);

	return 0;
}
