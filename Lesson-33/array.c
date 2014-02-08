#include <stdio.h>
#include "list.h"
#include "array.h"

Array array_new(void)
{
	link p;

	p = list_new();

	return p;
}


void print_array_data(void *data)
{
	if (data)
		printf("%c, ", *(char *)data);

	return;
}

int array_length(Array name)
{
	link p = name;
	int count = 0;

	while (p->next != NULL)
	{
		p = p->next;
		count++;
	}

	return count;
}

Item array_at(Array name, int index)
{
	Item p = name;
	int count = -1;

	while (p != NULL)
	{
		if (count == index)
			return p;

		p = p->next;
		count++;
	}

	return p;
}

void array_print(Array name)
{
	int i = 0;

	printf("[");
	for (i = 0; i < array_length(name); i++)
	{
		Item p = array_at(name, i);

		if (p->data == NULL)
			printf("nil");
		else
			printf("'%c'", *(char *)(p->data));

		if (i < array_length(name) - 1)
			printf(", ");
	}
	printf("]\n");

	return;
}

void array_delete_at(Array name, int index)
{
	int length = array_length(name);
	Item where;

	if (index < length)
	{
		where = array_at(name, index);
		list_delete(name, where);
		return;
	}

	return;
}


void array_insert(Array name, int index, char data)
{
	char *p = make_data(data);
	link item = make_node(p);
	int length = array_length(name);
	Item where;
	int i = 0;

	if (index <= length)
	{
		where = array_at(name, index-1);
		list_insert_after(where, item);
		return;
	}

	// insert nil as a padding item
	for (i = 0; i < index - length; i++)
	{
		link nil = make_node(NULL);
		list_insert_tail(name, nil);
	}

	// insert the data at the end 
	list_insert_tail(name, item);

	return;
}

int array_index(Array name, char data)
{
	link p = name;
	int index = -1;

	while (p != NULL)
	{
		if (p->data && *(char *)(p->data) == data)
			return index;

		p = p->next;
		index++;
	}

	return -1;
}

void array_sort(Array name)
{

	return;
}
