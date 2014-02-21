#include "stdio.h"
#define M 8
#define N 6

void printLSC(int i, int j,char *a, int status[][N])
{
	if(i == 0 || j== 0)
		return;

	if(status[i][j] == 0)
	{
		printLSC(i-1,j-1,a,status);
		printf("%c",a[i]);
	} 
	else
	{
		if(status[i][j] == 1)
			printLSC(i-1,j,a,status);
		else
			printLSC(i,j-1,a,status);
	}
}

int main(void)
{
	int i,j;

	char a[] = {' ','A','B','C','B','D','A','B', '\0'};
	char b[] = {' ','B','D','C','B','A', '\0'};
	int status[M][N]; //保存状态
	int dp[M][N];

	for(i = 0; i < M; i++)
		for(j = 0; j < N; j++)
		{
			dp[i][j] = 0;
			status[i][j] = 0;
		}
			
	for(i = 1; i < M; i++)
		for(j = 1; j < N; j++)
		{
			if(a[i] == b[j]){
				dp[i][j] = dp[i-1][j-1] + 1;
				status[i][j] = 0;
			}
			else if(dp[i][j-1] >= dp[i-1][j]){
				dp[i][j] = dp[i][j-1];
				status[i][j] = 2;
			}
			else{
				dp[i][j] = dp[i-1][j];
				status[i][j] = 1;
			}
		}

	printf("a=%s\n", a);
	printf("b=%s\n", b);
	printf("最大长度：%d",dp[M-1][N-1]);
	printf("\n");
	printLSC(M-1,N-1,a,status);
	printf("\n");

}
