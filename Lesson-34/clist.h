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

link clist_new(void);
void clist_print(link cur, void (*pf)(void *));
link clist_insert_after(link cur, link item);
link clist_delete(link cur, link item);

void print_int_data(void *data);
int clist_length(link cur);

#endif
