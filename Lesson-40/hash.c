// wordfreq.c -- list of words in file, with counts 
// edit by SmilingDolphin
// data: 2008-5-17
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node *nodeptr;
typedef struct node {
	char *word;
	int count;
	nodeptr next;
} node;
#define NHASH 29989
#define MULT 31
nodeptr bin[NHASH];
unsigned int hash(char *str)
{ 
	unsigned int h = 0;
	unsigned char * p;
	for (p = (unsigned char *)str ; *p != '\0'; p++)
		h = MULT * h + *p;
	return h % NHASH;
}
void insertWord(char *str)
{
	int h;
	nodeptr p;
	h = hash(str);
	for(p = bin[h]; p != NULL; p = p->next)
		if(strcmp(p->word,str) == 0)
		{
			p->count++;
			return;
		}
	p = (nodeptr)malloc(sizeof(node));

	if(p != NULL)
	{
		p->count = 1;
		p->word = (char *)malloc(strlen(str)+1);
		strcpy(p->word, str);
		p->next = bin[h];
		bin[h] = p;
	}
}
int main()
{ 
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);

	int i;
	nodeptr p;
	char word[100];
	for (i = 0; i < NHASH; i++)
		bin[i] = NULL;
	while (scanf("%s", word) != EOF)
	{
		insertWord(word);
		puts(word);
	}
	for(i = 0; i < NHASH; i++)
		for(p = bin[i]; p != NULL; p = p->next)
			printf("%s: %d\n", p->word, p->count);
	return 0;
}       
