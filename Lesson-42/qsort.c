#include <stdio.h>

/* swap: interchange v[i] and v[j] */ 
void swap(int v[], int i, int j)
{
	int temp;
	temp = v[i]; 
	v[i] = v[j]; 
	v[j] = temp;
}

/* qsort: sort v[left]...v[right] into increasing order */ 
void qsort(int v[], int left, int right)
{
	int i, last;
	void swap(int v[], int i, int j);
	if (left >= right) /* do nothing if array contains */ 
		return; /* fewer than two elements */

	swap(v, left, (left + right)/2); /* move partition elem */ 
	last = left; /* to v[0] */
	for (i = left + 1; i <= right; i++) /* partition */
		if (v[i] < v[left]) 
			swap(v, ++last, i);
	swap(v, left, last); 
	qsort(v, left, last-1); 
	qsort(v, last+1, right);
	/* restore partition elem */
}


int main()
{
	int array[] = {5, 3, 9, 1, 7};

	qsort(array, 0, 4);

	for (int i = 0; i < sizeof(array)/sizeof(int); i++)
		printf("%d ", array[i]);
	printf("\n");

	return 0;
}
