#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#define MaxNum 15//最大景点个数
#define NameLength 40//景点名称长度
#define INF 99999

//首先定义栈和栈的接口函数
typedef struct
{
	int SserialNumber[MaxNum];//记录最短路径上的顶点序号
	int top;
}Stack;

void InitStack(Stack* S)
{
	S->top = 0;
}

bool StackIsEmpty(Stack S)
{
	if (S.top == 0)
	{
		return true;
	}
	return false;
}

bool Push(Stack* S, int x)
{
	if (S->top == MaxNum)
	{
		return false;
	}
	S->SserialNumber[S->top] = x;
	S->top++;
	return true;
}

bool Pop(Stack* S, int* x)
{
	if (S->top == 0) {
		return false;
	}
	S->top--;
	*x = S->SserialNumber[S->top];
	return true;
}

//菜单
void Menu(void)
{
	printf("\n");
	printf("查询服务如下：\n");
	printf("****************************************************\n");
	printf("*     1-查看景点地图                               *\n");
	printf("*     2-查询某个景点到其他景点的最短路线           *\n");
	printf("*     3-查询两个景点间的最短路线                   *\n");
	printf("*     0-退出系统                                   *\n");
	printf("****************************************************\n");
	printf("\n请输入您的选择：\n");
}

//定义需要用的数据结构
//邻接矩阵
typedef struct
{
	char vexs[MaxNum + 1][NameLength];//景点名称表
	double arcs[MaxNum + 1][MaxNum + 1];//邻接矩阵
	int vexnum , arcnum; 
}AMGraph;

//Dijkstra算法
typedef struct 
{
	int S[MaxNum + 1];               //标记是否已求出最短路径
	double Path[MaxNum + 1];    //记录到i的最短路径
	int PrePath[MaxNum + 1];        //记录前驱顶点
}Dij;

//Floyd算法
typedef struct
{
	double Path[MaxNum + 1][MaxNum + 1];//记录当前最短路径
	int PrePath[MaxNum + 1][MaxNum + 1];//记录当前最短路径的前驱顶点
}Floyd;

//使用到的函数
//打印景点名称及其序号
void Print(AMGraph G) 
{
	for (int i = 1; i <= G.vexnum; i++) 
	{
		printf("%-3d- %-20s", i, G.vexs[i]);
		if (i % 4 == 0)   //4个景点一行 
		{
			printf("\n");
		}
	}
}

//求景点对应的序号
int Locate(AMGraph G, char* name)
{
	for (int i = 1; i <= G.vexnum; i++) 
	{
		if (strcmp(G.vexs[i], name) == 0) 
		{
			return i;
		}
	}
}

//创建邻接矩阵
void CreateMap(AMGraph* G) 
{
	FILE* fp = fopen("sights.txt", "r");
	fscanf(fp, "%d", &G->vexnum);
	for (int i = 1; i <= G->vexnum; i++)
	{
		fscanf(fp, "%s", G->vexs[i]);
	}
	fclose(fp);

	//初始化矩阵
	for (int i = 0; i <= G->vexnum; i++)
	{
		for (int j = 0; j <= G->vexnum; j++)
		{
			G->arcs[i][j] = INF;
		}
	}

	fp = fopen("PathDistance.txt", "r");
	int n = 0;//记录边数
	char name1[30], name2[30];
	double distance;
	while (fscanf(fp, "%s%s%lf", name1, name2, &distance) != EOF)
	{
		n++;
		int i = Locate(*G, name1);
		int j = Locate(*G, name2);
		G->arcs[i][j] = distance;
		G->arcs[j][i] = distance;
	}
	G->arcnum = n;//当前边数
}

//打印邻接矩阵
void PrintMap(AMGraph G)
{
	printf("\n景点及其对应序号为：\n");
	Print(G);
	printf("\n景点地图为：\n");
	printf("序号  ");
	for (int i = 1; i <= G.vexnum; i++) {
		printf("%-4d", i);
	}
	printf("\n");
	for (int i = 1; i <= G.vexnum; i++) 
	{
		printf("%-5d", i);
		for (int j = 1; j <= G.vexnum; j++)
		{
			if (G.arcs[i][j] == INF) {
				printf("%-5c", '*');
				continue;
			}
			printf("%-5.1lf", G.arcs[i][j]);
		}
		printf("\n");
	}
	printf("*号表示两景点没有直达路径.\n");
}

//单源最短路径
Dij D;
void Dijkstra(AMGraph G, int v) 
{
	//初始化
	for (int i = 1; i <= G.vexnum; i++) 
	{
		D.S[i] = 0;
		D.Path[i] = G.arcs[v][i];
		if (D.Path[i] < INF)
			D.PrePath[i] = v;
		else
			D.PrePath[i] = -1;//不存在边vi，i的前驱顶点置为-1
	}
	D.S[v] = 1;
	D.Path[v] = 0;

	for (int i = 2; i <= G.vexnum; i++)
	{
		//找到权值最短的边对应的顶点w
		double min = INF;
		int w;
		for (int j = 1; j <= G.vexnum; j++) 
		{
			if (!D.S[j] && D.Path[j] < min) 
			{
				min = D.Path[j];
				w = j;
			}
		}
	    D.S[w] = 1;
		//优化
		for (int j = 1; j <= G.vexnum; j++)
		{
			if (!D.S[j] && D.Path[w] + G.arcs[w][j] < D.Path[j])   
			{
				D.Path[j] = D.Path[w] + G.arcs[w][j];
				D.PrePath[j] = w;
			}
		}
	}
}

void Print_Dij(AMGraph G, int start) {
	printf("从%s出发，到其他景点的最短路径为：\n", G.vexs[start]);
	for (int end = 1; end <= G.vexnum; end++)
	{
		if (end == start) 
		{
			continue;
		}
		Stack S;
		InitStack(&S);
		Push(&S, end);
		//从end找最短路径的前驱节点，若不是start则进栈
		int tem1, tem2;
		for (tem1 = D.PrePath[end]; tem1 != start; tem1 = D.PrePath[tem2]) 
		{
			Push(&S, tem1);
			tem2 = tem1;
		}
		printf("%s", G.vexs[start]);
		tem1 = start;//tem1记录前驱顶点
		double sum = 0;
		while (!StackIsEmpty(S))
		{
			Pop(&S, &tem2);
			printf("-%.1lfkm->%s", G.arcs[tem1][tem2], G.vexs[tem2]);
			sum += G.arcs[tem1][tem2];
			tem1 = tem2;
		}
		printf("\n总路程为%.1lfkm.\n\n", sum);
	}
}

//求两景点间最短路径
Floyd F;
void floyd(AMGraph G) 
{
	//初始化
	for (int i = 1; i <= G.vexnum; i++) 
	{
		for (int j = 1; j <= G.vexnum; j++) 
		{
			if (i == j) 
			{
				F.Path[i][j] = 0;
			}
			else 
			{
				F.Path[i][j] = G.arcs[i][j];
			}
			if (F.Path[i][j] < INF && i != j) 
			{
				F.PrePath[i][j] = i;
			}
			else
			{
				F.PrePath[i][j] = -1;
			}
		}
	}
	//k表示每次加的顶点
	for (int k = 1; k <= G.vexnum; k++)
	{
		for (int i = 1; i <= G.vexnum; i++) 
		{
			for (int j = 1; j <= G.vexnum; j++) 
			{
				if (F.Path[i][j] > F.Path[i][k] + F.Path[k][j]) 
				{
					F.Path[i][j] = F.Path[i][k] + F.Path[k][j];
					F.PrePath[i][j] = F.PrePath[k][j];
				}
			}
		}
	}
}

void Print_Floyd(AMGraph G, int start, int end) 
{
	printf("%s到%s的最短路径为：\n\n", G.vexs[start], G.vexs[end]);
	Stack S;
	InitStack(&S);
	Push(&S, end);
	int tem1, tem2;
	for (tem1 = F.PrePath[start][end]; tem1 != start; tem1 = F.PrePath[start][tem2])
	{
		Push(&S, tem1);
		tem2 = tem1;
	}
	printf("%s", G.vexs[start]);
	tem1 = start;//tem1记录前驱顶点
	double sum = 0;
	while (!StackIsEmpty(S)) {
		Pop(&S, &tem2);
		printf("-%.1lfkm->%s", G.arcs[tem1][tem2], G.vexs[tem2]);
		sum += G.arcs[tem1][tem2];
		tem1 = tem2;
	}
	printf("\n总路程为%.1lfkm.\n\n", sum);
}