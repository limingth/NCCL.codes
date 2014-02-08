#ifndef _LIST_H
#define _LIST_H

struct node
{
	void *data;
	struct node * next;
};

typedef struct node * link;

link make_node(void *data);
char *make_data(char data);

link list_new(void);
void list_print(link head, void (*pf)(void *));
link list_insert_tail(link head, link item);
void list_insert_after(link where, link item);
link list_delete(link head, link item);

#endif
