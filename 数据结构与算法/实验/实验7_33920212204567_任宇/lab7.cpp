#include "lab7.h"

int main() {
	AMGraph G;
	CreateMap(&G);
	printf("提供路线咨询服务的景点有：\n");
	Print(G);
	printf("\n");
	Menu();
	int choice;
	scanf("%d", &choice);
	while (choice) 
	{
		switch (choice) 
		{
		case 1:
			PrintMap(G);
			break;
		case 2:
			Print(G);
			printf("\n请输入您想查询的景点对应的序号：\n");
			int x;
			scanf("%d", &x);
			if (x<1 || x>G.vexnum)
			{
				printf("输入错误！\n");
			}
			else {
				Dijkstra(G, x);
				Print_Dij(G, x);
			}
			break;
		case 3:
			Print(G);
			printf("\n请分别输入起点和终点的对应序号：\n");
			int x1, x2;
			scanf("%d %d", &x1, &x2);
			if (x1<1 || x1>G.vexnum || x2<1 || x2>G.vexnum||x1==x2) 
			{
				printf("输入错误！！\n");
			}
			else 
			{
				floyd(G);
				Print_Floyd(G, x1, x2);
			}
			break;
		default:
			printf("输入错误，请重新输入！\n");
			break;
		}
		Menu();
		scanf("%d", &choice);
	}
	printf("\n望您满意！\n");
	printf("正在退出...\n");
	Sleep(2000);
	return 0;
}