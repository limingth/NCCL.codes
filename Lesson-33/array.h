
#include "list.h"

typedef link Array;
typedef link Item;

Array array_new(void);
void array_insert(Array name, int index, char data);
void array_print(Array name);
void array_sort(Array name);

int array_index(Array name, char data);
Item array_at(Array name, int index);
int array_length(Array name);

void array_delete_at(Array name, int index);
