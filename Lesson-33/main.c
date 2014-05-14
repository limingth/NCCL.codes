#include <stdio.h>
#include "list.h"
#include "array.h"

int g = 100;

int main(void)
{
	Array samples = array_new();

	array_print(samples);
	printf("array length is %d\n", array_length(samples));
	array_insert(samples, 0, 'e'); 
	printf("array length is %d\n", array_length(samples));
	array_print(samples);

	array_insert(samples, 6, 'c'); 
	array_print(samples);
	array_insert(samples, 3, 'd'); 
	array_insert(samples, 4, 'b'); 
	array_insert(samples, 5, 'a'); 
	array_print(samples);
	//return 0;

	int index = array_index(samples, 'd');
	printf("index 'd' is %d\n", index);
	index = array_index(samples, 'a');
	printf("index 'a' is %d\n", index);

	Item p = array_at(samples, 5);
	printf("index 5 is '%c'\n", *(char *)(p->data));

	array_delete_at(samples, 5);
	array_print(samples);

	array_delete_at(samples, 1);
	array_print(samples);

	array_delete_at(samples, 1);
	array_print(samples);

	array_sort(samples);
	array_print(samples);

	return 0;
}

