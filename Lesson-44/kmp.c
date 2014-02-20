#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


const char *kmp_search(const char *text, const char *pattern)
{
	int *T;
	int i, j;
	const char *result = NULL;

	if (pattern[0] == '\0')
		return text;

	/* Construct the lookup table */
	T = (int*) malloc((strlen(pattern)+1) * sizeof(int) );
	T[0] = -1;
	for (i=0; pattern[i] != '\0'; i++) {
		T[i+1] = T[i] + 1;
		while (T[i+1] > 0 && pattern[i] != pattern[T[i+1]-1])
			T[i+1] = T[T[i+1]-1] + 1;
	}

	for (i = 1; i < strlen(pattern)+1; i++)
		printf("%d", T[i]);
	printf("\n");

	/* Perform the search */
	for (i=j=0; text[i] != '\0'; ) {
		if (j < 0 || text[i] == pattern[j]) {
			++i, ++j;
			if (pattern[j] == '\0') {
				result = text+i-j;
				break;
			}
		}
		else j = T[j];
	}

	free(T);
	return result;
}

int main(void)
{
	char base[]="BBC ABCDAB ABCDABCDABDE";
	char pattern[16]="ABCDABD";
	const char * p;

	printf("%s\n",base);
	//scanf("%s", pattern);
	printf("\n%s\n",pattern);

	p = kmp_search(base, pattern);

	printf("%s\n",base);
	for (int i = 0; i < p-base; i++)
		printf(" ");
	printf("^\n");
	for (int i = 0; i < p-base; i++)
		printf(" ");
	printf("%s\n",pattern);

	return 0;
}

