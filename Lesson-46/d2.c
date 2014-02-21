# include <stdio.h>
# include <stdlib.h>
# define maxlen 10
# define large 999
typedef struct
{
	int vexnum;
	char vexs[maxlen];
	int arcs[maxlen][maxlen];
}graph;
void init_graph(graph *g)
{
	int i=0,j=0;
	g->vexnum=5;
	for(i=0;i<5;i++)
		for(j=0;j<5;j++)
			g->arcs[i][j]=1000;
	g->arcs[0][1]=1;
	g->arcs[0][3]=3;
	g->arcs[0][4]=7;
	g->arcs[1][2]=2;
	g->arcs[2][3]=2;
	g->arcs[2][4]=2;
	g->arcs[3][4]=5;
	g->arcs[3][2]=3;
	g->arcs[3][1]=1;
	g->vexs[0]='a';
	g->vexs[1]='b';
	g->vexs[2]='c';
	g->vexs[3]='d';
	g->vexs[4]='e';
}
void shortpath_dijkstra(graph g)
{ 
	int cost[maxlen][maxlen];//cost[i][j]: The cost of i to j.
	int dist[maxlen];//dist[i]: The distance of source point to i.
	int path[maxlen];//The point passed by.
	int s[maxlen];//if s[i]=1,then i is in the source point gather.
	int i,j,n,v0,min,u;
	printf("Input the source point(1 means the first point):");
	scanf("%d",&v0);
	v0--;
	for(i=0;i<g.vexnum;i++)
	{
		for(j=0;j<g.vexnum;j++)
			cost[i][j]=g.arcs[i][j];
	}
	for(i=0;i<g.vexnum;i++)
	{ 
		dist[i]=cost[v0][i];
		if(dist[i]<large&&dist[i]>0) path[i]=v0;
		s[i]=0;
	}
	s[v0]=1;
	for(i=0;i<g.vexnum;i++)
	{ 
		min=large;
		u=v0;
		for(j=0;j<g.vexnum;j++)
			if(s[j]==0&&dist[j]<min)
			{min=dist[j];u=j;}
		s[u]=1;   
		for(j=0;j<g.vexnum;j++)
			if(s[j]==0&&dist[u]+cost[u][j]<dist[j])
			{ 
				dist[j]=dist[u]+cost[u][j];
				path[j]=u;
			}
	}
	printf("Output\n",v0);
	for(i=0;i<g.vexnum;i++)
		if(s[i]==1)
		{ 
			u=i;
			while(u!=v0)
			{ 
				printf("%c<-",g.vexs[u]);
				u=path[u];
			}
			printf("%c",g.vexs[u]);
			printf(":%d\n",dist[i]);
		}
		else printf("%c<-%c:no path\n",g.vexs[i],g.vexs[v0]);
}
int main()
{
	graph g;
	init_graph(&g);
	shortpath_dijkstra(g);
}
