//对于图的弧节点一定要初始化为INFINITY； 还有对于int型值，不要存储在double数组中，
//很有可能为0；  有时候编译器对于结构体成员的提示也有可能出错
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INFINITY  10000   //网的初始化值，最大值
#define MAX_VERTEX_NUM 40 //最大定点个数
#define MAX_NAME 20
#define OK 1
#define ERROR 0

typedef int Status;
typedef char VertexType[MAX_NAME];//用来保存顶点的名字
typedef char InfoType; //一条弧相关的信息
typedef int VRType; //顶点关系类型，表示两个节点是不是有关系

typedef struct ArcCell  //弧节点的存储结构
{
	VRType adj; //顶点关系类型，表示两个节点是不是有关系

}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//二维数组表示关系矩阵

typedef struct  //图的存储结构
{
	VertexType vexs[MAX_VERTEX_NUM];//顶点向量，这实际上是一个二位数组，因为数组元素也是保存名字的数组
	AdjMatrix arcs;        //邻接矩阵
	int vexnum,arcnum;        //图的顶点数与弧数
}MGraph;
//**********************************************************************************************************
int Locate(MGraph G,VertexType u) //查找顶点u在顶点向量中的位置
{
	int i;
	for(i=0;i<G.vexnum;i++)
		if(strcmp(u,G.vexs[i])==0)
			return i;
	return -1;
}

Status CreateFUDN(MGraph &G) //用文件创造无向网
{

	VertexType v1,v2;
	int w;
	FILE *file;
	char filename[20]="map.txt";
	file=fopen(filename,"r"); 
	if(!file)
	{
		printf("文件打开失败\n");
		return 0;
	} 
	fscanf(file,"%d%d",&G.vexnum,&G.arcnum);

	int i;
	int j;
	int k;

	for(i=0;i<G.vexnum;i++)   //千万别忘了
		for(j=0;j<G.vexnum;j++)
			G.arcs[i][j].adj=INFINITY;  //初始化
	for( i=0;i<G.vexnum;i++)
		fscanf(file,"%s",G.vexs[i]);  //输入顶点信息

	for(k=0;k<G.arcnum;k++)
	{

		fscanf(file,"%s%s%d",v1,v2,&w);
		i=Locate(G,v1); j=Locate(G,v2);
		G.arcs[i][j].adj=w;   //顶点v1 yu v2 的权值  
	}
	fclose(file);
	return OK;
}

void PrintGraph(MGraph &G)  //输出各个城市名
{

	int i;
	for(i=0;i<G.vexnum;i++)
	{
		if(i%5==0)
			printf("\n");
		printf("%3d %-10s ",i+1,G.vexs[i]);
	} 

}

//******************************************************************************************
//用弗洛伊德算法求任意两个顶点的最短路径
typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];
//三维数组保存任意两个顶点之间的最短路径,如果P[v][w][u]为真，那么u是从v到w的路径上的一个顶点
typedef int DistancMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
//二维数组保存任意两个顶点之间的最短路径的权值
void ShortestPath_FLOYD(MGraph G,PathMatrix P,DistancMatrix D)
{
	int v,w,u,i;
	for(v=0;v<G.vexnum;v++)
		for(w=0;w<G.vexnum;w++)
		{
			D[v][w]=G.arcs[v][w].adj; //从v到w的直接路径为弧v--w的权值
			for(u=0;u<G.vexnum;u++)
				P[v][w][u]=false; //假设从v到w的最短路径不经过任何顶点
			if(D[v][w]<INFINITY)  //如果v和w相连，那么从v到w的最短路径包括v和w
			{
				P[v][w][v]=P[v][w][w]=true;//
			}
		}
	for(v=0;v<G.vexnum;v++)
		for(w=0;w<G.vexnum;w++)
			for(u=0;u<G.vexnum;u++)
			{
				if((D[v][u]+D[u][w])<D[v][w])  //如果从v经过u到w的路径更小，更新
				{
					D[v][w]=D[v][u]+D[u][w];
					for(i=0;i<G.vexnum;i++)
						P[v][w][i]=P[v][u][i]||P[u][w][i];//从v到w的路径等于从v到u 的路径加从u到w的路径
				}
			}
}

int main()
{

	MGraph g;  //图
	PathMatrix p; //路径向量
	DistancMatrix d; //最短路径的权值向量
	int i,j,k;
	CreateFUDN(g);  //
	for(i=0;i<g.vexnum;i++)
		g.arcs[i][i].adj=0;//令对角线上的顶点权值为0；即时顶点到自己的距离为0

	ShortestPath_FLOYD(g,p,d);  //生成最短路径和权值
	int option;
	printf("请输入你的选项-----1 查询-------- 0：结束\n");
	scanf("%d",&option);
	while(option)
	{
		switch(option)
		{
			case 1: PrintGraph(g);
				printf("\n");
				printf("请输入要查询的起点城市与终点城市的代码:");
				scanf("%d %d",&i,&j);
				if(d[i-1][j-1]==10000)
				{
					printf("从%s到%s的无路径\n",g.vexs[i-1],g.vexs[j-1]);
				}
				else
				{
					printf("从%s到%s的最短路径为:%d\n",g.vexs[i-1],g.vexs[j-1],d[i-1][j-1]);

					printf("从%s到%s的最短路径经过:",g.vexs[i-1],g.vexs[j-1]);
					for(k=0;k<g.vexnum;k++)
						if(p[i-1][j-1][k]==1) //要写成是否等1，因为无穷也是真
							printf("%s ",g.vexs[k]);
				}
				break;
			case 0: printf("结束\n");
				break;
			default: printf("输入错误，结束\n");
				 break;
		}
		printf("\n");
		printf("请输入你的选项-----1 查询-------- 0：结束\n");
		scanf("%d",&option);
	}
	return 0;

}
