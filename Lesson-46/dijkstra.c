/*
 * 最短路径，迪杰斯特拉算法和弗洛伊德算法（采用邻接矩阵存储）
 *
 */

#include<stdio.h>

#define MAX_VERTEX_NUM 20
#define INFINITE 10000  //当做无穷大
//图的定义
typedef struct 
{
	int vertexNum;
	char vertex[MAX_VERTEX_NUM];
	int arc[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
}Graph,*PGraph;

//辅助数组中的元素定义
typedef struct
{
	int distance;
	int path[MAX_VERTEX_NUM];
}ArrayNode;


//构造有向网
void createdGraph(PGraph g)
{
	int i,j;
    g->vertexNum=6;
    for(i=0;i<g->vertexNum;i++)
		g->vertex[i]='A'+i;
	for(i=0;i<g->vertexNum;i++)
		for(j=0;j<g->vertexNum;j++)
            g->arc[i][j]=0;
	g->arc[0][2]=10;
	g->arc[0][4]=30;
	g->arc[0][5]=100;
	g->arc[1][2]=5;
	g->arc[2][3]=50;
	g->arc[3][5]=10;
	g->arc[4][3]=20;
	g->arc[4][5]=60;
}

//迪杰斯特拉算法
void Dijkstra(PGraph g,int from,int to)
{
	int i,j,index=-1;
	int n=1;//记录已经求出的两个点之间的最短距离的个数
    ArrayNode shortestPath[MAX_VERTEX_NUM];
	int flag[MAX_VERTEX_NUM]={0};//标记，为1表示到这个顶点的最短距离已求出

	//1.求from到各个顶点的直接距离，即初始化shortestPath数组
	for(i=0;i<g->vertexNum;i++){
		if(from==i){
			shortestPath[i].distance=0;
			shortestPath[i].path[0]=i;
			flag[from]=1;
		}
		else if(g->arc[from][i]>0){
        	shortestPath[i].path[0]=from;
	    	shortestPath[i].path[1]=i;
			shortestPath[i].distance=g->arc[from][i];
		}else
        	shortestPath[i].distance=INFINITE;
	}
	printf("step 1\n");
	//2.每次求一个最短路径
	while(n<g->vertexNum){
		//选择shortestPath中距离最小的，求出from到这个顶点的最短路径
		index=-1;
		for(i=0;i<g->vertexNum;i++){
			if(i==from)
				continue;
			if(flag[i]==0 && index==-1 && shortestPath[i].distance!=INFINITE)
				index=i;
			if(flag[i]==0 && index!=-1 && shortestPath[i].distance<shortestPath[index].distance)
				index=i;
		}
		flag[index]=1;
		//修改到各个顶点的最短路径
		for(i=0;i<g->vertexNum;i++){
			if(i==from)
				continue;
			if(g->arc[index][i]>0 && g->arc[index][i]+shortestPath[index].distance<shortestPath[i].distance){
				shortestPath[i].distance=g->arc[index][i]+shortestPath[index].distance;
				//修改路径
				j=0;
                while(1){
					shortestPath[i].path[j]=shortestPath[index].path[j];
					if(shortestPath[index].path[j]==index)
						break;
					j++;
				}
			    shortestPath[i].path[j+1]=i;
			}
		}
		n++;
	}
	printf("step 2\n");
	//输出from到to的最短路径及长度
	if(shortestPath[to].distance==INFINITE){
		printf("%c到%c没有路径\n",from+'A',to+'A');
		return;
	}
	printf("%c到%c的最短路径长度是：%d\n",from+'A',to+'A',shortestPath[to].distance);
	printf("经过的顶点：  ");
	i=0;
	while(1){
		printf("%-3c",shortestPath[to].path[i]+'A');
        if(shortestPath[to].path[i]==to)
			break;
		i++;
	}
	printf("\n");
}

//弗洛伊德算法
void Floyd(PGraph g,int from,int to)
{
	int i,j,k;
    int shortestPath[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//存储最短路径的数组
	//初始化shortestPath
	for(i=0;i<g->vertexNum;i++)
		for(j=0;j<g->vertexNum;j++){
			if(i==j){
				shortestPath[i][j]=0;
				continue;
			}
			if(g->arc[i][j]>0)
	    		shortestPath[i][j]=g->arc[i][j];
			else
                shortestPath[i][j]=INFINITE;
		}
	//将各个顶点顺次加入，并修改最短路径
	for(k=0;k<g->vertexNum;k++){
		//在i，j之间加入k
		for(i=0;i<g->vertexNum;i++){
			for(j=0;j<g->vertexNum;j++){
                if(shortestPath[i][k]+shortestPath[k][j]<shortestPath[i][j])
					shortestPath[i][j]=shortestPath[i][k]+shortestPath[k][j];
			}
		}
	}
	//输出最短路径
	if(shortestPath[from][to]==INFINITE){
		printf("%c到%c没有路径\n",from+'A',to+'A');
		return;
	}
	printf("%c到%c的最短路径长度是：%d\n",from+'A',to+'A',shortestPath[from][to]);
	printf("\n");
}

void main()
{
	Graph graph;
	char from,to;
	createdGraph(&graph);
	printf("请输入起点终点(如AF，中间不要有空格)\n");
	scanf("%c%c",&from,&to);
	printf("\n迪杰斯特拉算法:\n");
	Dijkstra(&graph,from-'A',to-'A');
	printf("\n弗洛伊德算法:\n");
	Floyd(&graph,from-'A',to-'A');
}
