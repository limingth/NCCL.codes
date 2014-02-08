#ifndef _LIST_H
#define _LIST_H

struct node
{
	void *data;
	struct node * next;
};

typedef struct node * link;

link make_node(void *data);
int *make_data(int data);

link list_new(void);
void list_print(link cur, void (*pf)(void *));
link list_insert_after(link cur, link item);
link list_delete(link cur, link item);

void print_int_data(void *data);
int list_length(link cur);

#endif
