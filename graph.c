/*
* file: graph.c
* @author: Luo Feijie
* @date: 2021-5-5 to 2021-6-10
* @note: This file is written for summarizing graph theory knowledge.
*/
/*
* 广度优先搜索(breadth-first search) 深度优先搜索(depth-first search)
* 无向图(undirected graph) 无向网(undirected net) 有向图(directed graph) 有向网(directed net)
* 邻接(点)(adjacent) 邻接表(adjacency list) 邻接矩阵(adjacency matrix) 逆(邻接表)(inverse)
* 顶点(vertex) 弧(arc)
*/
#include <stdio.h>
#include <stdlib.h>
// 辅助队列
#define true 1
#define false 0
#define bool char
#define QueueDataType int
typedef struct QueueNode
{
	QueueDataType data;
	struct QueueNode* pNext;
}*PQueueNode, QueueNode;
typedef struct QueueInfo
{
	PQueueNode front; // 队头指针
	PQueueNode rear; // 队尾指针
	int length;
}QueueInfo, * PQueueInfo;
// 初始化队列
void QueueInit(PQueueInfo userQueue)
{
	userQueue->front = NULL;
	userQueue->rear = userQueue->front;
	userQueue->length = 0;
}
void QueueDestroy(PQueueInfo userQueue)
{
	PQueueNode temp = NULL;
	while (userQueue->rear != NULL)
	{
		temp = userQueue->rear;
		userQueue->rear = temp->pNext;
		free(temp);
	}
	userQueue->front = NULL;
	userQueue->rear = userQueue->front;
	userQueue->length = 0;
}
bool QueueEmpty(PQueueInfo userQueue)
{
	if (userQueue->length == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
int QueueLength(PQueueInfo userQueue)
{
	return userQueue->length;
}
PQueueNode QueueEn(PQueueInfo userQueue, QueueDataType elem)
{
	PQueueNode newNode = (PQueueNode)malloc(1 * sizeof(QueueNode));
	if (newNode != NULL)
	{
		userQueue->length = userQueue->length + 1;
		newNode->data = elem;
		newNode->pNext = NULL;

		if (userQueue->length == 1)
		{
			userQueue->front = newNode;
			userQueue->rear = newNode;
		}
		else
		{
			userQueue->front->pNext = newNode;
			userQueue->front = userQueue->front->pNext;
		}
		return newNode;
	}
	else
	{
		printf("malloc failed!\n");
	}
}
QueueDataType QueueDe(PQueueInfo userQueue)
{
	if (userQueue->rear != NULL)
	{
		QueueDataType retTemp = userQueue->rear->data;
		PQueueNode temp = userQueue->rear;
		userQueue->rear = userQueue->rear->pNext;
		free(temp);
		userQueue->length = userQueue->length - 1;
		return retTemp;
	}
	else
	{
		QueueDataType temp = -1;
		return temp;
	}
}
QueueDataType QueueFront(PQueueInfo userQueue)
{
	if (userQueue->front != NULL)
	{
		return userQueue->front->data;
	}
	else
	{
		QueueDataType temp = -1;
		return temp;
	}
}
QueueDataType QueueRear(PQueueInfo userQueue)
{
	if (userQueue->rear != NULL)
	{
		return userQueue->rear->data;
	}
	else
	{
		QueueDataType temp = -1;
		return temp;
	}
}

// 辅助栈
#define true 1
#define false 0
#define bool char
#define StackDataType int
typedef struct StackNode
{
	StackDataType data;
	struct StackNode* pNext;
}StackNode, * PStackNode;
typedef struct StackInfo
{
	PStackNode top; // 栈顶指针
	PStackNode base; // 栈低指针
	int size;
}StackInfo, * PStackInfo;
void StackInit(PStackInfo userStack)
{
	userStack->size = 0;
	userStack->top = NULL;
	userStack->base = userStack->top;
}
PStackNode StackPush(PStackInfo userStack, StackDataType elem)
{
	PStackNode temp = (PStackNode)malloc(1 * sizeof(StackNode));
	if (temp != NULL)
	{
		userStack->size = userStack->size + 1;
		temp->data = elem;
		if (userStack->size == 1)
		{
			userStack->base = temp;
			userStack->top = temp;
			temp->pNext = NULL;
		}
		else
		{
			temp->pNext = userStack->top;
			userStack->top = temp;
		}
		return NULL;
	}
	else
	{
		printf("malloc failed!\n");
	}
}
StackDataType StackPop(PStackInfo userStack)
{
	if (userStack->top != NULL)
	{
		userStack->size = userStack->size - 1;
		StackDataType retTemp = userStack->top->data;
		PStackNode temp = userStack->top;
		userStack->top = temp->pNext;
		free(temp);
		return retTemp;
	}
}
StackDataType StackGetTop(PStackInfo userStack)
{
	if (userStack->top != NULL)
	{
		return userStack->top->data;
	}
}
void StackDestroy(PStackInfo userStack)
{
	PStackNode temp;
	while (userStack->top != NULL)
	{
		temp = userStack->top;
		userStack->top = temp->pNext;
		free(temp);
	}
	userStack->size = 0;
}
bool StackEmpty(PStackInfo userStack)
{
	if (userStack->size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
#define ARCTYPE int
#define VERTEXTYPE int
typedef struct KruskalSort
{
	ARCTYPE arc;
	VERTEXTYPE i, j;
}KruskalSort, * PKruskalSort;
// 辅助排序
PKruskalSort QuickSort(PKruskalSort arr, int startIndex, int endIndex, bool bAscendingOrder)
{
	if (endIndex - startIndex < 2) // 少于两个元素的无需排序
	{
		return arr;
	}
	ARCTYPE pivot = arr[startIndex].arc; // 枢轴
	VERTEXTYPE pivotJ = arr[startIndex].j;
	VERTEXTYPE pivotI = arr[startIndex].i;
	int leftPoint = startIndex;
	int rightPoint = endIndex;
	if (bAscendingOrder) // 升序排序
	{
		while (leftPoint < rightPoint)
		{
			while (arr[rightPoint].arc >= pivot && rightPoint > leftPoint) // 两个条件都必须如此
			{
				--rightPoint;
			}
			arr[leftPoint] = arr[rightPoint];
			while (arr[leftPoint].arc <= pivot && leftPoint < rightPoint) // 两个条件都必须如此
			{
				++leftPoint;
			}
			arr[rightPoint] = arr[leftPoint];
		}
		arr[rightPoint].arc = pivot;
		arr[rightPoint].i = pivotI;
		arr[rightPoint].j = pivotJ;
	}
	else
	{
		while (leftPoint < rightPoint)
		{
			while (arr[rightPoint].arc <= pivot && rightPoint > leftPoint) // 两个条件都必须如此
			{
				--rightPoint;
			}
			arr[leftPoint] = arr[rightPoint];
			while (arr[leftPoint].arc >= pivot && leftPoint < rightPoint) // 两个条件都必须如此
			{
				++leftPoint;
			}
			arr[rightPoint] = arr[leftPoint];
		}
		arr[rightPoint].arc = pivot;
		arr[rightPoint].i = pivotI;
		arr[rightPoint].j = pivotJ;
	}

	QuickSort(arr, startIndex, rightPoint - 1, bAscendingOrder);
	QuickSort(arr, rightPoint + 1, endIndex, bAscendingOrder);
	return arr;
}
/*
* 图的数组(邻接矩阵)存储表示
* 空间复杂度 O(V^2), 适用与稠密图
* 求度、出度、入度: 遍历矩阵的行或列, 时间复杂度为 O(|V|)
*/
#define MAX_VERTEX_NUM 20	  // 最大顶点个数
#define VERTEXTYPE  int       // 顶点数据类型
#define ARCTYPE int			  // 弧长类型
#define ARCINFOTYPE char	  // 弧相关信息数据类型
// 图的类型
typedef enum GraphKind
{
	DG, DN, UDG, UDN // 依次表示为: 有向图, 有向网, 无向图, 无向网
}GraphKind;
// 邻接矩阵弧信息
typedef struct MGraphArc
{
	ARCTYPE  adj; // 对于无权图, 1和0分别代表是否相邻; 对于有权图, 数值大小表示权值
	ARCINFOTYPE* arcInfo; // 弧相关信息
}MGraphArc, * PMGraphArc, MGraphArcArr[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 或者适用动态分配内存
// 邻接矩阵图
typedef struct MGraph
{
	VERTEXTYPE* vexs;                       // 存储图中顶点数据
	PMGraphArc* arcs;                                      // 记录图顶点之间的关系
	int vexNum, arcNum;                                     // 记录图的顶点树, 弧数
	GraphKind graphKind;                                    // 标记图的类型
}MGraph, * PMGraph;                                         // 邻接矩阵图
															// 定位顶点在顶点矩阵中的位置
int MGraphLocateVex(PMGraph userGraph, VERTEXTYPE tVertex)
{
	for (int n = 0; n < userGraph->vexNum; ++n)
	{
		if (userGraph->vexs[n] == tVertex)
		{
			return n;
		}
	}
	printf("No such vertex.\n");
	return -1;
}
// 创建邻接矩阵有向图
PMGraph MGraphCreateDG(PMGraph G)
{
	printf("请依次输入顶点、边的个数:");
	scanf_s("%d%d", &G->vexNum, &G->arcNum);
	G->vexs = (VERTEXTYPE*)malloc(G->vexNum * sizeof(VERTEXTYPE));
	G->arcs = (PMGraphArc*)malloc(G->vexNum * sizeof(PMGraphArc));
	if (G->vexs == NULL || G->arcs == NULL)
	{
		printf("malloc failed!\n");
	}
	for (int i = 0; i < G->vexNum; ++i)
	{
		G->arcs[i] = (PMGraphArc)malloc(G->vexNum * sizeof(MGraphArc));
		if (G->arcs[i] == NULL)
		{
			printf("malloc failed!\n");
		}
	}
	printf("依次输入顶点数据: ");
	for (int n = 0; n < G->vexNum; ++n)
	{
		scanf_s("%d", &G->vexs[n]);
	}
	// 初始化弧二维矩阵
	for (int n = 0; n < G->vexNum; ++n)
	{
		for (int m = 0; m < G->vexNum; ++m)
		{
			G->arcs[n][m].adj = 0;
			G->arcs[n][m].arcInfo = NULL;
		}
	}
	// 在二维弧矩阵中添加弧信息
	for (int i = 0; i < G->arcNum; ++i)
	{
		printf("请依次输入弧头、弧尾:");
		VERTEXTYPE head, tail;
		scanf_s("%d%d", &head, &tail);
		int headIndex = MGraphLocateVex(G, head);
		int	tailIndex = MGraphLocateVex(G, tail);
		if (headIndex == -1 || tailIndex == -1)
		{
			printf("No such vertex.");
		}
		// 指向为由行"指向"列
		G->arcs[headIndex][tailIndex].adj = 1;
	}
	return G;
}
// 创建邻接矩阵有向网
PMGraph MGraphCreateDN(PMGraph G)
{
	printf("请依次输入顶点、边的个数:");
	scanf_s("%d%d", &G->vexNum, &G->arcNum);
	G->vexs = (VERTEXTYPE*)malloc(G->vexNum * sizeof(VERTEXTYPE));
	G->arcs = (PMGraphArc*)malloc(G->arcNum * sizeof(PMGraphArc));
	if (G->vexs == NULL || G->arcs == NULL)
	{
		printf("malloc failed!\n");
	}
	for (int i = 0; i < G->vexNum; ++i)
	{
		G->arcs[i] = (PMGraphArc)malloc(G->arcNum * sizeof(MGraphArc));
		if (G->arcs[i] == NULL)
		{
			printf("malloc failed!\n");
		}
	}
	printf("依次输入顶点数据: ");
	for (int n = 0; n < G->vexNum; ++n)
	{
		scanf_s("%d", &G->vexs[n]);
	}
	// 初始化弧二维矩阵
	for (int n = 0; n < G->vexNum; ++n)
	{
		for (int m = 0; m < G->vexNum; ++m)
		{
			G->arcs[n][m].adj = 0;
			G->arcs[n][m].arcInfo = NULL;
		}
	}
	// 在二维弧矩阵中添加弧信息
	for (int i = 0; i < G->arcNum; ++i)
	{
		printf("请依次输入弧头、弧尾:");
		VERTEXTYPE head, tail;
		scanf_s("%d%d", &head, &tail);
		int headIndex = MGraphLocateVex(G, head);
		int	tailIndex = MGraphLocateVex(G, tail);
		if (headIndex == -1 || tailIndex == -1)
		{
			printf("No such vertex.");
		}
		printf("请输入弧长:");
		ARCTYPE arc;
		scanf_s("%d", &arc);
		// 指向为由行"指向"列
		G->arcs[headIndex][tailIndex].adj = arc;
	}
	return G;
}
// 创建邻接矩阵无向图
PMGraph MGraphCreateUDG(PMGraph G)
{
	printf("请依次输入顶点、边的个数:");
	scanf_s("%d%d", &G->vexNum, &G->arcNum);
	G->vexs = (VERTEXTYPE*)malloc(G->vexNum * sizeof(VERTEXTYPE));
	G->arcs = (PMGraphArc*)malloc(G->arcNum * sizeof(PMGraphArc));
	if (G->vexs == NULL || G->arcs == NULL)
	{
		printf("malloc failed!\n");
	}
	for (int i = 0; i < G->vexNum; ++i)
	{
		G->arcs[i] = (PMGraphArc)malloc(G->arcNum * sizeof(MGraphArc));
		if (G->arcs[i] == NULL)
		{
			printf("malloc failed!\n");
		}
	}
	printf("依次输入顶点数据: ");
	for (int n = 0; n < G->vexNum; ++n)
	{
		scanf_s("%d", &G->vexs[n]);
	}
	// 初始化弧二维矩阵
	for (int n = 0; n < G->vexNum; ++n)
	{
		for (int m = 0; m < G->vexNum; ++m)
		{
			G->arcs[n][m].adj = 0;
			G->arcs[n][m].arcInfo = NULL;
		}
	}
	// 在二维弧矩阵中添加弧信息
	for (int i = 0; i < G->arcNum; ++i)
	{
		printf("请依次输入边头、边尾:");
		VERTEXTYPE head, tail;
		scanf_s("%d%d", &head, &tail);
		int headIndex = MGraphLocateVex(G, head);
		int	tailIndex = MGraphLocateVex(G, tail);
		if (headIndex == -1 || tailIndex == -1)
		{
			printf("No such vertex.");
		}
		G->arcs[headIndex][tailIndex].adj = 1;
		G->arcs[tailIndex][headIndex].adj = 1;
	}
	return G;
}
// 创建邻接矩阵无向网
PMGraph MGraphCreateUDN(PMGraph G)
{
	printf("请依次输入顶点、边的个数:");
	scanf_s("%d%d", &G->vexNum, &G->arcNum);
	G->vexs = (VERTEXTYPE*)malloc(G->vexNum * sizeof(VERTEXTYPE));
	G->arcs = (PMGraphArc*)malloc(G->arcNum * sizeof(PMGraphArc));
	if (G->vexs == NULL || G->arcs == NULL)
	{
		printf("malloc failed!\n");
	}
	for (int i = 0; i < G->vexNum; ++i)
	{
		G->arcs[i] = (PMGraphArc)malloc(G->arcNum * sizeof(MGraphArc));
		if (G->arcs[i] == NULL)
		{
			printf("malloc failed!\n");
		}
	}
	printf("依次输入顶点数据: ");
	for (int n = 0; n < G->vexNum; ++n)
	{
		scanf_s("%d", &G->vexs[n]);
	}
	// 初始化弧二维矩阵
	for (int n = 0; n < G->vexNum; ++n)
	{
		for (int m = 0; m < G->vexNum; ++m)
		{
			G->arcs[n][m].adj = 0;
			G->arcs[n][m].arcInfo = NULL;
		}
	}
	// 在二维弧矩阵中添加弧信息
	for (int i = 0; i < G->arcNum; ++i)
	{
		printf("请依次输入边头、边尾:");
		VERTEXTYPE head, tail;
		scanf_s("%d%d", &head, &tail);
		int headIndex = MGraphLocateVex(G, head);
		int	tailIndex = MGraphLocateVex(G, tail);
		if (headIndex == -1 || tailIndex == -1)
		{
			printf("No such vertex.");
		}
		printf("请输入弧长:");
		ARCTYPE arc;
		scanf_s("%d", &arc);
		G->arcs[headIndex][tailIndex].adj = arc;
		G->arcs[tailIndex][headIndex].adj = arc;
	}
	return G;
}
// 邻接矩阵图复制
MGraph MGraphCopy(PMGraph G)
{
	MGraph ret;
	ret.arcNum = G->arcNum;
	ret.graphKind = G->graphKind;
	ret.vexNum = G->vexNum;
	ret.vexs = (VERTEXTYPE*)malloc(G->vexNum * sizeof(VERTEXTYPE));
	ret.arcs = (PMGraphArc*)malloc(G->vexNum * sizeof(PMGraphArc));
	if (ret.vexs == NULL || ret.arcs == NULL)
	{
		printf("malloc failed!\n");
	}
	for (int n = 0; n < G->vexNum; ++n)
	{
		ret.vexs[n] = G->vexs[n];
		ret.arcs[n] = (PMGraphArc)malloc(G->vexNum * sizeof(MGraphArc));
		if (ret.arcs[n] == NULL)
		{
			printf("malloc failed!\n");
		}
		for (int m = 0; m < G->vexNum; ++m)
		{
			ret.arcs[n][m] = G->arcs[n][m];
		}
	}
	return ret;
}
// 邻接矩阵图反转
MGraph MGraphReverse(PMGraph G)
{
	MGraph ret;
	ret.arcNum = G->arcNum;
	ret.graphKind = G->graphKind;
	ret.vexNum = G->vexNum;
	ret.vexs = (VERTEXTYPE*)malloc(G->vexNum * sizeof(VERTEXTYPE));
	ret.arcs = (PMGraphArc*)malloc(G->vexNum * sizeof(PMGraphArc));
	if (ret.vexs == NULL || ret.arcs == NULL)
	{
		printf("malloc failed!\n");
	}
	for (int n = 0; n < G->vexNum; ++n)
	{
		ret.vexs[n] = G->vexs[n];
		ret.arcs[n] = (PMGraphArc)malloc(G->vexNum * sizeof(MGraphArc));
		if (ret.arcs[n] == NULL)
		{
			printf("malloc failed!\n");
		}
		for (int m = 0; m < G->vexNum; ++m)
		{
			ret.arcs[n][m] = G->arcs[m][n];
		}
	}
	return ret;
}
// 创建邻接矩阵图
PMGraph MGraphCreateGraph(PMGraph G)
{
	printf("情输入需要创建的图的类型:(0:有向图, 1:有向网, 2:无向图, 3:无向网)");
	int graphKind;
	scanf_s("%d", &graphKind);
	G->graphKind = (GraphKind)graphKind;
	switch (graphKind)
	{
	case 0:
		MGraphCreateDG(G);
		break;
	case 1:
		MGraphCreateDN(G);
		break;
	case 2:
		MGraphCreateUDG(G);
		break;
	case 3:
		MGraphCreateUDN(G);
		break;
	default:
		printf("Invalid number.");
	}
	return G;
}
// 邻接矩阵图输出
void MGraphPrint(PMGraph G)
{
	for (int n = 0; n < G->vexNum; ++n)
	{
		for (int m = 0; m < G->vexNum; ++m)
		{
			printf("%d  ", G->arcs[n][m].adj);
		}
		printf("\n\n");
	}
}
// 邻接矩阵图销毁
void MGraphDestroy(PMGraph G)
{
	for (int n = 0; n < G->vexNum; ++n)
	{
		free(G->arcs[n]);
	}
	free(G->arcs);
	free(G->vexs);
}
/*
* 图的邻接表链式存储表示
* 空间复杂度: 无向图O(|V|+2|E|), 有向图O(|V|+|E|), 适合存储稀疏图
* 表达方式: 边链表结点的顺序是任意的, 不唯一
* 求度、入度、出度: 求无向图的度和有向图的出度的时间复杂度都是O(1), 求有向图的入度是O(|E|)
*/
#define  MAX_VERTEX_NUM 20
#define ARCINFOTYPE char // 弧长其他信息数据类型
#define ARCTYPE int      // 弧长数据类型
#define VERTEXTYPE int
// 邻接表弧信息
typedef struct ALGraphArc
{
	int adjvexIndex;      // 该弧所指向的顶点在数组中的位置. 相当于链表的数据域
	ARCTYPE adj;          // 对于无权图, 1和0分别代表是否相邻; 对于有权图, 数值大小表示权值
	ARCINFOTYPE* arcInfo; // 储存弧的其他信息
	struct ALGraphArc* pNext;
}ALGraphArc, * PALGraphArc;
// 邻接表顶点信息
typedef struct ALGraphVex
{
	VERTEXTYPE data;  // 结点的数据
	ALGraphArc* pFirstArc;
}ALGraphVex, * PALGraphVex, ALGraphVexArr[MAX_VERTEX_NUM]; // 或者使用动态内存分配
// 邻接表图
typedef struct ALGraph
{
	GraphKind graphKind; // 图的类型
	PALGraphVex vertices;
	int vertexNum, arcNum; // 依次为顶点数, 弧数
}ALGraph, * PALGraph;
// 邻接表查找tVertex顶点在数组中的位置
int ALGraphLocateVex(PALGraph G, VERTEXTYPE tVertex)
{
	for (int n = 0; n < G->vertexNum; ++n)
	{
		if (G->vertices[n].data == tVertex)
		{
			return n;
		}
	}
	return -1;
}
// 邻接表有向图
PALGraph ALGraphCreateDG(PALGraph G)
{
	printf("请分别输入顶点个数、弧数:");
	scanf_s("%d%d", &G->vertexNum, &G->arcNum);
	G->vertices = (PALGraphVex)malloc(G->vertexNum * sizeof(ALGraphVex));
	if (G->vertices == NULL)
	{
		printf("malloc failed!\n");
	}
	printf("请依次输入顶点数据:");
	for (int n = 0; n < G->vertexNum; ++n)
	{
		scanf_s("%d", &G->vertices[n].data);
		G->vertices[n].pFirstArc = NULL;
	}
	for (int m = 0; m < G->arcNum; ++m)
	{
		printf("请依次输入弧首、弧尾:");
		VERTEXTYPE head, tail;
		scanf_s("%d%d", &head, &tail);
		int headIndex = ALGraphLocateVex(G, head);
		int tailIndex = ALGraphLocateVex(G, tail);
		if (G->vertices[headIndex].pFirstArc == NULL)
		{
			ALGraphArc* temp = (ALGraphArc*)malloc(1 * sizeof(ALGraphArc));
			if (temp == NULL)
			{
				printf("malloc failed!\n");
			}
			temp->adjvexIndex = tailIndex;
			temp->adj = 1; // 无权图
			temp->arcInfo = NULL;
			temp->pNext = NULL;
			G->vertices[headIndex].pFirstArc = temp;
			continue;
		}
		ALGraphArc* temp = G->vertices[headIndex].pFirstArc;
		while (1)
		{
			if (temp->pNext == NULL)
			{
				ALGraphArc* tempNew = (ALGraphArc*)malloc(1 * sizeof(ALGraphArc));
				if (tempNew == NULL)
				{
					printf("malloc failed!\n");
				}
				tempNew->adjvexIndex = tailIndex;
				tempNew->adj = 1; // 无权图
				tempNew->arcInfo = NULL;
				tempNew->pNext = NULL;
				temp->pNext = tempNew;
				break;
			}
			temp = temp->pNext;
		}
	}
	return G;
}
// 邻接表有向网
PALGraph ALGraphCreateDN(PALGraph G)
{
	printf("请分别输入顶点个数、弧数:");
	scanf_s("%d%d", &G->vertexNum, &G->arcNum);
	G->vertices = (PALGraphVex)malloc(G->vertexNum * sizeof(ALGraphVex));
	if (G->vertices == NULL)
	{
		printf("malloc failed!\n");
	}
	printf("请依次输入顶点数据:");
	for (int n = 0; n < G->vertexNum; ++n)
	{
		scanf_s("%d", &G->vertices[n].data);
		G->vertices[n].pFirstArc = NULL;
	}
	for (int m = 0; m < G->arcNum; ++m)
	{
		printf("请依次输入弧首、弧尾:");
		VERTEXTYPE head, tail;
		scanf_s("%d%d", &head, &tail);
		ARCTYPE arcLength;
		printf("请输入弧长: ");
		scanf_s("%d", &arcLength);
		int headIndex = ALGraphLocateVex(G, head);
		int tailIndex = ALGraphLocateVex(G, tail);
		if (G->vertices[headIndex].pFirstArc == NULL)
		{
			ALGraphArc* temp = (ALGraphArc*)malloc(1 * sizeof(ALGraphArc));
			if (temp == NULL)
			{
				printf("malloc failed!\n");
			}
			temp->adjvexIndex = tailIndex;
			temp->adj = arcLength; // 有权网
			temp->arcInfo = NULL;
			temp->pNext = NULL;
			G->vertices[headIndex].pFirstArc = temp;
			continue;
		}
		ALGraphArc* temp = G->vertices[headIndex].pFirstArc;
		while (1)
		{
			if (temp->pNext == NULL)
			{
				ALGraphArc* tempNew = (ALGraphArc*)malloc(1 * sizeof(ALGraphArc));
				if (tempNew == NULL)
				{
					printf("malloc failed!\n");
				}
				tempNew->adjvexIndex = tailIndex;
				tempNew->adj = arcLength; // 有权网
				tempNew->arcInfo = NULL;
				tempNew->pNext = NULL;
				temp->pNext = tempNew;
				break;
			}
			temp = temp->pNext;
		}
	}
	return G;
}
// 邻接表无向图
PALGraph ALGraphCreateUDG(PALGraph G)
{
	printf("请分别输入顶点个数、弧数:");
	scanf_s("%d%d", &G->vertexNum, &G->arcNum);
	G->vertices = (PALGraphVex)malloc(G->vertexNum * sizeof(ALGraphVex));
	if (G->vertices == NULL)
	{
		printf("malloc failed!\n");
	}
	printf("请依次输入顶点数据:");
	for (int n = 0; n < G->vertexNum; ++n)
	{
		scanf_s("%d", &G->vertices[n].data);
		G->vertices[n].pFirstArc = NULL;
	}
	for (int m = 0; m < G->arcNum; ++m)
	{
		printf("请依次输入弧首、弧尾:");
		VERTEXTYPE head, tail;
		scanf_s("%d%d", &head, &tail);
		int headIndex = ALGraphLocateVex(G, head);
		int tailIndex = ALGraphLocateVex(G, tail);
		char bFirstHead = 0;
		char bFirstTail = 0;
		if (G->vertices[headIndex].pFirstArc == NULL)
		{
			ALGraphArc* temp = (ALGraphArc*)malloc(1 * sizeof(ALGraphArc));
			if (temp == NULL)
			{
				printf("malloc failed!\n");
			}
			temp->adjvexIndex = tailIndex;
			temp->adj = 1; // 无权图
			temp->arcInfo = NULL;
			temp->pNext = NULL;
			G->vertices[headIndex].pFirstArc = temp;
			bFirstHead = 1;
		}
		if (G->vertices[tailIndex].pFirstArc == NULL)
		{
			ALGraphArc* temp = (ALGraphArc*)malloc(1 * sizeof(ALGraphArc));
			if (temp == NULL)
			{
				printf("malloc failed!\n");
			}
			temp->adjvexIndex = headIndex;
			temp->adj = 1; // 无权图
			temp->arcInfo = NULL;
			temp->pNext = NULL;
			G->vertices[tailIndex].pFirstArc = temp;
			bFirstTail = 1;
		}
		ALGraphArc* temp = G->vertices[headIndex].pFirstArc;
		ALGraphArc* tempTail = G->vertices[tailIndex].pFirstArc;
		while (bFirstHead != 1)
		{
			if (temp->pNext == NULL)
			{
				ALGraphArc* tempNew = (ALGraphArc*)malloc(1 * sizeof(ALGraphArc));
				if (tempNew == NULL)
				{
					printf("malloc failed!\n");
				}
				tempNew->adjvexIndex = tailIndex;
				tempNew->adj = 1; // 无权图
				tempNew->arcInfo = NULL;
				tempNew->pNext = NULL;
				temp->pNext = tempNew;
				break;
			}
			temp = temp->pNext;
		}
		while (bFirstTail != 1)
		{
			if (tempTail->pNext == NULL)
			{
				ALGraphArc* tempNew = (ALGraphArc*)malloc(1 * sizeof(ALGraphArc));
				if (tempNew == NULL)
				{
					printf("malloc failed!\n");
				}
				tempNew->adjvexIndex = headIndex;
				tempNew->adj = 1; // 无权图
				tempNew->arcInfo = NULL;
				tempNew->pNext = NULL;
				tempTail->pNext = tempNew;
				break;
			}
			tempTail = tempTail->pNext;
		}
	}
	return G;
}
// 邻接表无向网
PALGraph ALGraphCreateUDN(PALGraph G)
{
	printf("请分别输入顶点个数、弧数:");
	scanf_s("%d%d", &G->vertexNum, &G->arcNum);
	G->vertices = (PALGraphVex)malloc(G->vertexNum * sizeof(ALGraphVex));
	if (G->vertices == NULL)
	{
		printf("malloc failed!\n");
	}
	printf("请依次输入顶点数据:");
	for (int n = 0; n < G->vertexNum; ++n)
	{
		scanf_s("%d", &G->vertices[n].data);
		G->vertices[n].pFirstArc = NULL;
	}
	for (int m = 0; m < G->arcNum; ++m)
	{
		printf("请依次输入弧首、弧尾:");
		VERTEXTYPE head, tail;
		scanf_s("%d%d", &head, &tail);
		ARCTYPE arcLength;
		printf("请输入弧长: ");
		scanf_s("%d", &arcLength);
		int headIndex = ALGraphLocateVex(G, head);
		int tailIndex = ALGraphLocateVex(G, tail);
		char bFirstHead = 0;
		char bFirstTail = 0;
		if (G->vertices[headIndex].pFirstArc == NULL)
		{
			ALGraphArc* temp = (ALGraphArc*)malloc(1 * sizeof(ALGraphArc));
			if (temp == NULL)
			{
				printf("malloc failed!\n");
			}
			temp->adjvexIndex = tailIndex;
			temp->adj = arcLength; // 有权网
			temp->arcInfo = NULL;
			temp->pNext = NULL;
			G->vertices[headIndex].pFirstArc = temp;
			bFirstHead = 1;
		}
		if (G->vertices[tailIndex].pFirstArc == NULL)
		{
			ALGraphArc* temp = (ALGraphArc*)malloc(1 * sizeof(ALGraphArc));
			if (temp == NULL)
			{
				printf("malloc failed!\n");
			}
			temp->adjvexIndex = headIndex;
			temp->adj = arcLength; // 有权网
			temp->arcInfo = NULL;
			temp->pNext = NULL;
			G->vertices[tailIndex].pFirstArc = temp;
			bFirstTail = 1;
		}
		ALGraphArc* temp = G->vertices[headIndex].pFirstArc;
		ALGraphArc* tempTail = G->vertices[tailIndex].pFirstArc;
		while (bFirstHead != 1)
		{
			if (temp->pNext == NULL)
			{
				ALGraphArc* tempNew = (ALGraphArc*)malloc(1 * sizeof(ALGraphArc));
				if (tempNew == NULL)
				{
					printf("malloc failed!\n");
				}
				tempNew->adjvexIndex = tailIndex;
				tempNew->adj = arcLength; // 有权网
				tempNew->arcInfo = NULL;
				tempNew->pNext = NULL;
				temp->pNext = tempNew;
				break;
			}
			temp = temp->pNext;
		}
		while (bFirstTail != 1)
		{
			if (tempTail->pNext == NULL)
			{
				ALGraphArc* tempNew = (ALGraphArc*)malloc(1 * sizeof(ALGraphArc));
				if (tempNew != NULL)
				{
					tempNew->adjvexIndex = headIndex;
					tempNew->adj = arcLength; // 有权网
					tempNew->arcInfo = NULL;
					tempNew->pNext = NULL;
					tempTail->pNext = tempNew;
					break;
				}
				else
				{
					printf("malloc failed!\n");
				}
			}
			tempTail = tempTail->pNext;
		}
	}
	return G;
}
// 创建邻接表图
PALGraph ALGraphCreateGraph(PALGraph G)
{
	printf("情输入需要创建的图的类型:(0:有向图, 1:有向网, 2:无向图, 3:无向网)");
	int graphKind;
	scanf_s("%d", &graphKind);
	G->graphKind = (GraphKind)graphKind;
	switch (graphKind)
	{
	case 0:
		ALGraphCreateDG(G);
		break;
	case 1:
		ALGraphCreateDN(G);
		break;
	case 2:
		ALGraphCreateUDG(G);
		break;
	case 3:
		ALGraphCreateUDN(G);
		break;
	default:
		printf("Invalid number!");
	}
	return G;
}
// 邻接表有向图反转
ALGraph ALGraphDGraphReverse(PALGraph G)
{
	if (G->graphKind == DG || G->graphKind == DN)
	{
		ALGraph ret;
		PALGraph PRet = &ret;
		PRet->arcNum = G->arcNum;
		PRet->graphKind = G->graphKind;
		PRet->vertexNum = G->vertexNum;
		PRet->vertices = (PALGraphVex)malloc(G->vertexNum * sizeof(ALGraphVex));
		if (PRet->vertices == NULL)
		{
			printf("malloc failed!\n");
			return;
		}
		for (int n = 0; n < G->vertexNum; ++n)
		{
			PRet->vertices[n].data = G->vertices[n].data;
			PRet->vertices[n].pFirstArc = NULL;
		}
		for (int i = 0; i < G->vertexNum; ++i)
		{
			PALGraphArc temp = G->vertices[i].pFirstArc;
			while (temp != NULL)
			{
				PALGraphArc newTemp = (PALGraphArc)malloc(sizeof(ALGraphArc));
				if (newTemp == NULL)
				{
					printf("malloc failed!\n");
					return;
				}
				newTemp->adj = temp->adj;
				newTemp->adjvexIndex = i;
				newTemp->arcInfo = temp->arcInfo;
				newTemp->pNext = NULL;
				PALGraphArc tTemp = PRet->vertices[temp->adjvexIndex].pFirstArc;
				if (tTemp != NULL)
				{
					while (tTemp->pNext != NULL)
					{
						tTemp = tTemp->pNext;
					}
					tTemp->pNext = newTemp;
				}
				else
				{
					PRet->vertices[temp->adjvexIndex].pFirstArc = newTemp;
				}
				temp = temp->pNext;
			}
		}
		return ret;
		// 如果是返回 指针，这里是 return PRet;
	}
	else
	{
		return;
	}
}
// 邻接表复制
ALGraph ALGraphCopy(PALGraph G)
{
	ALGraph ret;
	PALGraph PRet = &ret;
	PRet->arcNum = G->arcNum;
	PRet->graphKind = G->graphKind;
	PRet->vertexNum = G->vertexNum;
	PRet->vertices = (PALGraphVex)malloc(G->vertexNum * sizeof(ALGraphVex));
	if (PRet->vertices == NULL)
	{
		printf("malloc failed!\n");
		return;
	}
	for (int n = 0; n < G->vertexNum; ++n)
	{
		PRet->vertices[n].data = G->vertices[n].data;
		PRet->vertices[n].pFirstArc = NULL;
	}
	for (int i = 0; i < G->vertexNum; ++i)
	{
		PALGraphArc temp = G->vertices[i].pFirstArc;
		while (temp != NULL)
		{
			PALGraphArc newTemp = (PALGraphArc)malloc(sizeof(ALGraphArc));
			if (newTemp == NULL)
			{
				printf("malloc failed!\n");
				return;
			}
			newTemp->adj = temp->adj;
			newTemp->adjvexIndex = temp->adjvexIndex;
			newTemp->arcInfo = temp->arcInfo;
			newTemp->pNext = NULL;
			PALGraphArc tTemp = PRet->vertices[i].pFirstArc;
			if (tTemp != NULL)
			{
				while (tTemp->pNext != NULL)
				{
					tTemp = tTemp->pNext;
				}
				tTemp->pNext = newTemp;
			}
			else
			{
				PRet->vertices[i].pFirstArc = newTemp;
			}
			temp = temp->pNext;
		}
	}
	return ret;
}
// 邻接表图输出
void ALGraphPrint(PALGraph G)
{
	if (G->graphKind == DG || G->graphKind == DN)
	{
		for (int n = 0; n < G->vertexNum; ++n)
		{
			VERTEXTYPE head = G->vertices[n].data;
			ALGraphArc* temp = G->vertices[n].pFirstArc;
			while (temp != NULL)
			{
				printf("%d —%d—> %d\t", head, temp->adj, G->vertices[temp->adjvexIndex].data);
				temp = temp->pNext;
			}
			printf("\n");
		}
	}
	else if (G->graphKind == UDN || G->graphKind == UDG)
	{
		for (int n = 0; n < G->vertexNum; ++n)
		{
			VERTEXTYPE head = G->vertices[n].data;
			ALGraphArc* temp = G->vertices[n].pFirstArc;
			while (temp != NULL)
			{
				printf("%d —%d— %d\t", head, temp->adj, G->vertices[temp->adjvexIndex].data);
				temp = temp->pNext;
			}
			printf("\n");
		}
	}
}
// 邻接表图销毁
void ALGraphDestroy(PALGraph G)
{
	if (G->graphKind == UDG || G->graphKind == UDN)
	{
		PALGraphArc* arr = (PALGraphArc*)malloc(2 * G->arcNum * sizeof(PALGraphArc));
		if (arr == NULL)
		{
			printf("malloc failed!\n");
		}
		int index = 0;
		for (int n = 0; n < G->vertexNum; ++n)
		{
			ALGraphArc* temp = G->vertices[n].pFirstArc;
			while (temp != NULL)
			{
				arr[index++] = temp;
				temp = temp->pNext;
			}
		}
		for (int i = 0; i < 2 * G->arcNum; ++i)
		{
			free(arr[i]);
		}
		free(G->vertices);
		free(arr);
	}
	else
	{
		PALGraphArc* arr = (PALGraphArc*)malloc(G->arcNum * sizeof(PALGraphArc));
		if (arr == NULL)
		{
			printf("malloc failed!\n");
		}
		int index = 0;
		int totalArc = 0;
		for (int n = 0; n < G->vertexNum; ++n)
		{
			ALGraphArc* temp = G->vertices[n].pFirstArc;
			while (temp != NULL)
			{
				arr[index++] = temp;
				temp = temp->pNext;
				totalArc++;
			}
		}
		for (int i = 0; i < totalArc; ++i)
		{
			free(arr[i]);
		}
		free(G->vertices);
		free(arr);
	}
}

/* 图的十字链表储存方式(可以看为将 !|有向图|! 的邻接表和逆邻接表结合起来得到的一种链表)
* 表链表的结点总数是|E|
* 空间复杂度是O(|V|+|E|)
* 求顶点的出度和入度的时间复杂度都是O(1)~O(|E|)
*/
#define MAX_VERTEX_NUM 20
#define VERTEXTYPE int
#define ARCINFOTYPE char
#define ARCTYPE int // 弧长
// 十字链表图类型
typedef enum OLGraphType
{
	OLDG, OLDN
}OLGraphType;
// 十字链表弧信息结点
typedef struct OLGraphArc
{
	int headVexIndex, tailVexIndex; // 该弧的尾和头结点的位置
	ARCTYPE arcLength;				// 弧长
	struct OLGraphArc* pHead;           // 弧头相同的链域
	struct OLGraphArc* pTail;           // 弧尾相同的链域
	ARCINFOTYPE* info;				// 其他信息
}OLGraphArc, * POLGraphArc;
// 十字链表结点信息结点
typedef struct OLGraphVex
{
	VERTEXTYPE data;
	OLGraphArc* firstIn;
	OLGraphArc* firstOut;
}OLGraphVex, * POLGraphVex, OLGraphVexArr[MAX_VERTEX_NUM];
// 十字链表图
typedef struct OLGraph
{
	POLGraphVex vList;
	int vexNum, arcNum;
	OLGraphType graphKind;
}OLGraph, * POLGraph;
int OLGraphLocateVex(POLGraph G, VERTEXTYPE v)
{
	for (int n = 0; n < G->vexNum; ++n)
	{
		if (G->vList[n].data == v)
		{
			return n;
		}
	}
	return -1;
}
// 十字链表有向图
POLGraph OLGraphCreateDG(POLGraph G)
{
	printf("请依次输入顶点、弧的个数:");
	scanf_s("%d%d", &G->vexNum, &G->arcNum);
	G->vList = (POLGraphVex)malloc(G->vexNum * sizeof(OLGraphVex));
	if (G->vList == NULL)
	{
		printf("malloc failed!\n");
	}
	printf("请依次输入顶点数据:");
	for (int n = 0; n < G->vexNum; ++n)
	{
		scanf_s("%d", &G->vList[n].data);
		G->vList[n].firstIn = NULL;
		G->vList[n].firstOut = NULL;
	}
	for (int n = 0; n < G->arcNum; ++n)
	{
		printf("请输入弧首、弧尾:");
		VERTEXTYPE head, tail;
		scanf_s("%d%d", &head, &tail);
		int headIndex, tailIndex;
		headIndex = OLGraphLocateVex(G, head);
		tailIndex = OLGraphLocateVex(G, tail);
		char bOutFirst = 0;
		char bInFirst = 0;
		OLGraphArc* temp;
		temp = (OLGraphArc*)malloc(1 * sizeof(OLGraphArc));
		if (temp == NULL)
		{
			printf("malloc failed!\n");
		}
		temp->arcLength = 1;
		temp->headVexIndex = headIndex;
		temp->info = NULL;
		temp->pHead = NULL;
		temp->pTail = NULL;
		temp->tailVexIndex = tailIndex;
		if (G->vList[headIndex].firstOut == NULL)
		{
			G->vList[headIndex].firstOut = temp;
			bOutFirst = 1;
		}
		OLGraphArc* tempNext = G->vList[headIndex].firstOut;
		while (bOutFirst != 1)
		{
			if (tempNext->pHead == NULL)
			{
				tempNext->pHead = temp;
				break;
			}
			else
			{
				tempNext = tempNext->pHead;
			}
		}
		// 弧尾
		tempNext = G->vList[tailIndex].firstIn;
		if (G->vList[tailIndex].firstIn == NULL)
		{
			G->vList[tailIndex].firstIn = temp;
			bInFirst = 1;
		}
		while (bInFirst != 1)
		{
			if (tempNext->pTail == NULL)
			{
				tempNext->pTail = temp;
				break;
			}
			else
			{
				tempNext = tempNext->pTail;
			}
		}
	}
	return G;
}
// 十字链表有向网
POLGraph OLGraphCreateDN(POLGraph G)
{
	printf("请依次输入顶点、弧的个数:");
	scanf_s("%d%d", &G->vexNum, &G->arcNum);
	G->vList = (POLGraphVex)malloc(G->vexNum * sizeof(OLGraphVex));
	if (G->vList == NULL)
	{
		printf("malloc failed!\n");
	}
	printf("请依次输入顶点数据:");
	for (int n = 0; n < G->vexNum; ++n)
	{
		scanf_s("%d", &G->vList[n].data);
		G->vList[n].firstIn = NULL;
		G->vList[n].firstOut = NULL;
	}
	for (int n = 0; n < G->arcNum; ++n)
	{
		printf("请输入弧首、弧尾:");
		VERTEXTYPE head, tail;
		scanf_s("%d%d", &head, &tail);
		ARCTYPE arcLength;
		printf("请输入弧长:");
		scanf_s("%d", &arcLength);
		int headIndex, tailIndex;
		headIndex = OLGraphLocateVex(G, head);
		tailIndex = OLGraphLocateVex(G, tail);
		char bOutFirst = 0;
		char bInFirst = 0;
		OLGraphArc* temp;
		temp = (OLGraphArc*)malloc(1 * sizeof(OLGraphArc));
		if (temp == NULL)
		{
			printf("malloc failed!\n");
		}
		temp->arcLength = arcLength;
		temp->headVexIndex = headIndex;
		temp->info = NULL;
		temp->pHead = NULL;
		temp->pTail = NULL;
		temp->tailVexIndex = tailIndex;
		if (G->vList[headIndex].firstOut == NULL)
		{
			G->vList[headIndex].firstOut = temp;
			bOutFirst = 1;
		}
		OLGraphArc* tempNext = G->vList[headIndex].firstOut;
		while (bOutFirst != 1)
		{
			if (tempNext->pHead == NULL)
			{
				tempNext->pHead = temp;
				break;
			}
			else
			{
				tempNext = tempNext->pHead;
			}
		}
		// 弧尾
		tempNext = G->vList[tailIndex].firstIn;
		if (G->vList[tailIndex].firstIn == NULL)
		{
			G->vList[tailIndex].firstIn = temp;
			bInFirst = 1;
		}
		while (bInFirst != 1)
		{
			if (tempNext->pTail == NULL)
			{
				tempNext->pTail = temp;
				break;
			}
			else
			{
				tempNext = tempNext->pTail;
			}
		}
	}
	return G;
}
// 创建十字链表图
POLGraph OLGraphCreateGraph(POLGraph G)
{
	printf("情输入需要创建的图的类型:(0:有向图, 1:有向网): ");
	int graphKind;
	scanf_s("%d", &graphKind);
	G->graphKind = (OLGraphType)graphKind;
	switch (graphKind)
	{
	case 0:
		OLGraphCreateDG(G);
		break;
	case 1:
		OLGraphCreateDN(G);
		break;
	default:
		printf("Invalid number!");
	}
	return G;
}
// 十字链表图的打印
void OLGraphPrint(POLGraph G)
{
	for (int n = 0; n < G->vexNum; ++n)
	{
		OLGraphArc* temp = G->vList[n].firstOut;
		while (temp != NULL)
		{
			printf("%d—%d—>%d\t", G->vList[temp->headVexIndex].data, temp->arcLength, G->vList[temp->tailVexIndex].data);
			temp = temp->pHead;
		}
		printf("\n");
		temp = G->vList[n].firstIn;
		while (temp != NULL)
		{
			printf("%d<—%d—%d\t", G->vList[temp->tailVexIndex].data, temp->arcLength, G->vList[temp->headVexIndex].data);
			temp = temp->pTail;
		}
		printf("\n\n");
	}
}
// 十字链表复制
OLGraph OLGraphCopy(POLGraph G)
{
	OLGraph ret;
	ret.arcNum = G->arcNum;
	ret.graphKind = G->graphKind;
	ret.vexNum = G->vexNum;
	ret.vList = (OLGraphVex*)malloc(G->vexNum * sizeof(OLGraphVex));
	if (ret.vList != NULL)
	{
		for (int i = 0; i < G->vexNum; ++i)
		{
			ret.vList[i].firstIn = NULL;
			ret.vList[i].firstOut = NULL;
		}
	}
	else
	{
		printf("malloc failed!");
	}

	for (int n = 0; n < G->vexNum; ++n)
	{
		ret.vList[n].data = G->vList[n].data;
		POLGraphArc temp = G->vList[n].firstOut;
		while (temp != NULL)
		{
			POLGraphArc newTemp = (POLGraphArc)malloc(sizeof(OLGraphArc));
			if (newTemp != NULL)
			{
				newTemp->arcLength = temp->arcLength;
				newTemp->headVexIndex = temp->headVexIndex;
				newTemp->info = temp->info;
				newTemp->tailVexIndex = temp->tailVexIndex;
				newTemp->pHead = NULL;
				newTemp->pTail = NULL;
				POLGraphArc tempInsert = ret.vList[n].firstOut;
				if (tempInsert == NULL)
				{
					ret.vList[n].firstOut = newTemp;
				}
				else
				{
					while (tempInsert->pHead != NULL)
					{
						tempInsert = tempInsert->pHead;
					}
					tempInsert->pHead = newTemp;
				}
				tempInsert = ret.vList[temp->tailVexIndex].firstIn;
				if (tempInsert == NULL)
				{
					ret.vList[temp->tailVexIndex].firstIn = newTemp;
				}
				else
				{
					while (tempInsert->pTail != NULL)
					{
						tempInsert = tempInsert->pTail;
					}
					tempInsert->pTail = newTemp;
				}
			}
			else
			{
				printf("malloc failed!");
			}
			temp = temp->pHead;
		}
	}
	return ret;
}
// 十字链表图反转
OLGraph OLGraphReverse(POLGraph G)
{
	OLGraph ret;
	ret.arcNum = G->arcNum;
	ret.graphKind = G->graphKind;
	ret.vexNum = G->vexNum;
	ret.vList = (OLGraphVex*)malloc(G->vexNum * sizeof(OLGraphVex));
	if (ret.vList != NULL)
	{
		for (int i = 0; i < G->vexNum; ++i)
		{
			ret.vList[i].firstIn = NULL;
			ret.vList[i].firstOut = NULL;
		}
	}
	else
	{
		printf("malloc failed!");
	}

	for (int n = 0; n < G->vexNum; ++n)
	{
		ret.vList[n].data = G->vList[n].data;
		POLGraphArc temp = G->vList[n].firstOut;
		while (temp != NULL)
		{
			POLGraphArc newTemp = (POLGraphArc)malloc(sizeof(OLGraphArc));
			if (newTemp != NULL)
			{
				newTemp->arcLength = temp->arcLength;
				newTemp->headVexIndex = temp->tailVexIndex;
				newTemp->info = temp->info;
				newTemp->tailVexIndex = temp->headVexIndex;
				newTemp->pHead = NULL;
				newTemp->pTail = NULL;
				POLGraphArc tempInsert = ret.vList[temp->tailVexIndex].firstOut;
				if (tempInsert == NULL)
				{
					ret.vList[temp->tailVexIndex].firstOut = newTemp;
				}
				else
				{
					while (tempInsert->pHead != NULL)
					{
						tempInsert = tempInsert->pHead;
					}
					tempInsert->pHead = newTemp;
				}
				tempInsert = ret.vList[n].firstIn;
				if (tempInsert == NULL)
				{
					ret.vList[n].firstIn = newTemp;
				}
				else
				{
					while (tempInsert->pTail != NULL)
					{
						tempInsert = tempInsert->pTail;
					}
					tempInsert->pTail = newTemp;
				}
			}
			else
			{
				printf("malloc failed!");
			}
			temp = temp->pHead;
		}
	}
	return ret;
}
// 十字链表图的销毁
void OLGraphDestroy(POLGraph G)
{
	// free 出度方向的弧
	POLGraphArc* deleteArr = (POLGraphArc*)malloc(G->arcNum * sizeof(POLGraphArc));
	if (deleteArr == NULL)
	{
		printf("malloc failed!\n");
	}
	int index = 0;
	for (int n = 0; n < G->vexNum; ++n)
	{
		OLGraphArc* temp = G->vList[n].firstOut;
		while (temp != NULL)
		{
			deleteArr[index++] = temp;
			temp = temp->pHead;
		}
	}
	for (int i = 0; i < index; ++i)
	{
		free(deleteArr[i]);
	}
	free(G->vList);
	free(deleteArr);
}
/*
* 图的邻接多重表存储表示(邻接多重表是 无向图 的另一种链式存储结构)
* 边链表的结点总数为 |E|
* 空间复杂度是O(|V|+|E|)
* 删除边和顶点方便。在进行搜索操作的无向图的问题中采用邻接多重表作储存结构更为适宜
* 对于无向图而言，其邻接多重表和邻接表的区别仅仅在于同一条边在邻接表中用两个结点表示，而在邻接多重表中只有一个结点.可见在邻接表中，边结点有冗余
*/
#define MAX_VERTEX_NUM 20
#define INFOTYPE char
#define VERTEXTYPE int
#define EDGETYPE int
// 邻接多重表的类型
typedef enum AMLGraphType
{
	AMLUDG, AMLUDN
}AMLGraphType;
// 邻接多重表访问标志
typedef enum AMLGraphVisitMark
{
	UNVISITED, VISITED
}AMLGraphVisitMark;
// 邻接多重表边信息
typedef struct AMLGraphArc
{
	AMLGraphVisitMark visitMark;         // 访问标志
	EDGETYPE edgeLength;         // 边的长度
	int iVex, jVex;              // 该边依附的两个顶点的位置
	struct AMLGraphArc* iLink, * jLink; // 分别指向依附这两个顶点的下一条边
	INFOTYPE* info;
}AMLGraphArc, * PAMLGraphArc;
// 邻接多重表顶点信息
typedef struct AMLGraphVex
{
	VERTEXTYPE data;
	PAMLGraphArc firstEdge;
}AMLGraphVex, * PAMLGraphVex;
// 邻接多重表
typedef struct AMLGraph
{
	PAMLGraphVex vexs;
	AMLGraphType graphKind;
	int vexNum, edgeNum; // 无向图的当前顶点数和边数
}AMLGraph, * PAMLGraph;
// 邻接多重表顶点定位
int AMLGraphLocateVex(PAMLGraph G, VERTEXTYPE vex)
{
	for (int n = 0; n < G->vexNum; ++n)
	{
		if (G->vexs[n].data == vex)
		{
			return n;
		}
	}
	return -1;
}
// 创建邻接多重表无向图
PAMLGraph AMLGraphCreateUDG(PAMLGraph G)
{
	printf("请分别输入顶点数、边数: ");
	scanf_s("%d%d", &G->vexNum, &G->edgeNum);
	G->vexs = (PAMLGraphVex)malloc(G->vexNum * sizeof(AMLGraphVex));
	if (G->vexs == NULL)
	{
		printf("malloc failed!\n");
	}
	printf("请分别输入顶点数据: ");
	// 顶点信息载入
	for (int n = 0; n < G->vexNum; ++n)
	{
		scanf_s("%d", &G->vexs[n].data);
		G->vexs[n].firstEdge = NULL;
	}
	// 边信息载入
	for (int n = 0; n < G->edgeNum; ++n)
	{
		printf("请分别输入边头、边尾: ");
		VERTEXTYPE headVex, tailVex;
		scanf_s("%d%d", &headVex, &tailVex);
		int headVexIndex, tailVexIndex;
		headVexIndex = AMLGraphLocateVex(G, headVex);
		tailVexIndex = AMLGraphLocateVex(G, tailVex);
		// 创建边
		PAMLGraphArc tempEdgeNew = (PAMLGraphArc)malloc(1 * sizeof(AMLGraphArc));
		if (tempEdgeNew == NULL)
		{
			printf("malloc failed!\n");
		}
		tempEdgeNew->edgeLength = 1;
		tempEdgeNew->iLink = NULL;
		tempEdgeNew->info = NULL;
		tempEdgeNew->jLink = NULL;
		tempEdgeNew->iVex = headVexIndex;
		tempEdgeNew->jVex = tailVexIndex;
		tempEdgeNew->visitMark = UNVISITED;
		char bFirstHead = 0;
		char bFirstTail = 0;
		if (G->vexs[headVexIndex].firstEdge == NULL)
		{
			G->vexs[headVexIndex].firstEdge = tempEdgeNew;
			bFirstHead = 1;
		}
		if (G->vexs[tailVexIndex].firstEdge == NULL)
		{
			G->vexs[tailVexIndex].firstEdge = tempEdgeNew;
			bFirstTail = 1;
		}
		PAMLGraphArc temp = G->vexs[headVexIndex].firstEdge;
		while (bFirstHead != 1)
		{
			if (temp->iLink != NULL && temp->iVex == headVexIndex)
			{
				temp = temp->iLink;
			}
			else if (temp->iLink == NULL && temp->iVex == headVexIndex)
			{
				temp->iLink = tempEdgeNew;
				break;
			}
			if (temp->jLink != NULL && temp->jVex == headVexIndex)
			{
				temp = temp->jLink;
			}
			else if (temp->jLink == NULL && temp->jVex == headVexIndex)
			{
				temp->jLink = tempEdgeNew;
				break;
			}
		}
		temp = G->vexs[tailVexIndex].firstEdge;
		while (bFirstTail != 1)
		{
			if (temp->iLink != NULL && temp->iVex == tailVexIndex)
			{
				temp = temp->iLink;
			}
			else if (temp != NULL && temp->iLink == NULL && temp->iVex == tailVexIndex)
			{
				temp->iLink = tempEdgeNew;
				break;
			}
			if (temp != NULL && temp->jLink != NULL && temp->jVex == tailVexIndex)
			{
				temp = temp->jLink;
			}
			else if (temp != NULL && temp->jLink == NULL && temp->jVex == tailVexIndex)
			{
				temp->jLink = tempEdgeNew;
				break;
			}
		}
	}
	return G;
}
// 创建邻接多重表无向网
PAMLGraph AMLGraphCreateUDN(PAMLGraph G)
{
	printf("请分别输入顶点数、边数: ");
	scanf_s("%d%d", &G->vexNum, &G->edgeNum);
	G->vexs = (PAMLGraphVex)malloc(G->vexNum * sizeof(AMLGraphVex));
	if (G->vexs == NULL)
	{
		printf("malloc failed!\n");
	}
	printf("请分别输入顶点数据: ");
	// 顶点信息载入
	for (int n = 0; n < G->vexNum; ++n)
	{
		scanf_s("%d", &G->vexs[n].data);
	}
	// 顶点first指针初始化
	for (int i = 0; i < G->vexNum; ++i)
	{
		G->vexs[i].firstEdge = NULL;
	}
	// 边信息载入
	for (int n = 0; n < G->edgeNum; ++n)
	{
		printf("请分别输入边头、边尾: ");
		VERTEXTYPE headVex, tailVex;
		scanf_s("%d%d", &headVex, &tailVex);
		EDGETYPE edgeLength;
		printf("请输入边的长度: ");
		scanf_s("%d", &edgeLength);
		int headVexIndex, tailVexIndex;
		headVexIndex = AMLGraphLocateVex(G, headVex);
		tailVexIndex = AMLGraphLocateVex(G, tailVex);
		// 创建边
		PAMLGraphArc tempEdgeNew = (PAMLGraphArc)malloc(1 * sizeof(AMLGraphArc));
		if (tempEdgeNew == NULL)
		{
			printf("malloc failed!\n");
		}
		tempEdgeNew->edgeLength = edgeLength;
		tempEdgeNew->iLink = NULL;
		tempEdgeNew->info = NULL;
		tempEdgeNew->jLink = NULL;
		tempEdgeNew->iVex = headVexIndex;
		tempEdgeNew->jVex = tailVexIndex;
		tempEdgeNew->visitMark = UNVISITED;
		char bFirstHead = 0;
		char bFirstTail = 0;
		if (G->vexs[headVexIndex].firstEdge == NULL)
		{
			G->vexs[headVexIndex].firstEdge = tempEdgeNew;
			bFirstHead = 1;
		}
		if (G->vexs[tailVexIndex].firstEdge == NULL)
		{
			G->vexs[tailVexIndex].firstEdge = tempEdgeNew;
			bFirstTail = 1;
		}
		PAMLGraphArc temp = G->vexs[headVexIndex].firstEdge;
		while (bFirstHead != 1)
		{
			if (temp->iLink != NULL && temp->iVex == headVexIndex)
			{
				temp = temp->iLink;
			}
			else if (temp->iLink == NULL && temp->iVex == headVexIndex)
			{
				temp->iLink = tempEdgeNew;
				break;
			}
			if (temp->jLink != NULL && temp->jVex == headVexIndex)
			{
				temp = temp->jLink;
			}
			else if (temp->jLink == NULL && temp->jVex == headVexIndex)
			{
				temp->jLink = tempEdgeNew;
				break;
			}
		}
		temp = G->vexs[tailVexIndex].firstEdge;
		while (bFirstTail != 1)
		{
			if (temp->iLink != NULL && temp->iVex == tailVexIndex)
			{
				temp = temp->iLink;
			}
			else if (temp != NULL && temp->iLink == NULL && temp->iVex == tailVexIndex)
			{
				temp->iLink = tempEdgeNew;
				break;
			}
			if (temp != NULL && temp->jLink != NULL && temp->jVex == tailVexIndex)
			{
				temp = temp->jLink;
			}
			else if (temp != NULL && temp->jLink == NULL && temp->jVex == tailVexIndex)
			{
				temp->jLink = tempEdgeNew;
				break;
			}
		}
	}
	return G;
}
// 创建邻接多重表图
PAMLGraph AMLGraphCreateGraph(PAMLGraph G)
{
	printf("情输入需要创建的图的类型:(0:无向图, 1:无向网): ");
	int graphKind;
	scanf_s("%d", &graphKind);
	G->graphKind = (AMLGraphType)graphKind;
	switch (graphKind)
	{
	case 0:
		AMLGraphCreateUDG(G);
		break;
	case 1:
		AMLGraphCreateUDN(G);
		break;
	default:
		printf("Invalid number!");
	}
	return G;
}
// 邻接多重表图打印
void AMLGraphPrint(PAMLGraph G)
{
	for (int n = 0; n < G->vexNum; ++n)
	{
		PAMLGraphArc temp = G->vexs[n].firstEdge;
		while (temp != NULL)
		{
			if (temp->iVex == n)
			{
				printf("%d—%d—%d\t", G->vexs[n].data, temp->edgeLength, G->vexs[temp->jVex].data);
				temp = temp->iLink;
				continue;
			}
			if (temp->jVex == n)
			{
				printf("%d—%d—%d\t", G->vexs[n].data, temp->edgeLength, G->vexs[temp->iVex].data);
				temp = temp->jLink;
				continue;
			}
		}
		printf("\n");
	}
}
// 邻接多重表复制
AMLGraph AMLGraphCopy(PAMLGraph G)
{
	AMLGraph ret;
	ret.edgeNum = G->edgeNum;
	ret.graphKind = G->graphKind;
	ret.vexNum = G->vexNum;
	ret.vexs = (PAMLGraphVex)malloc(G->vexNum * sizeof(AMLGraphVex));
	for (int i = 0; i < G->vexNum; ++i)
	{
		ret.vexs[i].data = G->vexs[i].data;
		ret.vexs[i].firstEdge = NULL;
	}
	for (int n = 0; n < G->vexNum; ++n)
	{
		PAMLGraphArc tempG = G->vexs[n].firstEdge;
		PAMLGraphArc temp;
		while (tempG != NULL)
		{
			if (tempG->visitMark == UNVISITED)
			{
				PAMLGraphArc newTemp = (PAMLGraphArc)malloc(sizeof(AMLGraphArc));
				newTemp->edgeLength = tempG->edgeLength;
				newTemp->iVex = tempG->iVex;
				newTemp->iLink = NULL;
				newTemp->jVex = tempG->jVex;
				newTemp->jLink = NULL;
				newTemp->visitMark = tempG->visitMark;
				newTemp->info = tempG->info;
				char bFirstHead = 0;
				char bFirstTail = 0;

				int headVexIndex = tempG->iVex;
				if (ret.vexs[headVexIndex].firstEdge == NULL)
				{
					ret.vexs[headVexIndex].firstEdge = newTemp;
					bFirstHead = 1;
				}
				temp = ret.vexs[headVexIndex].firstEdge;
				while (bFirstHead != 1)
				{
					if (temp->iLink != NULL && temp->iVex == headVexIndex)
					{
						temp = temp->iLink;
					}
					else if (temp->iLink == NULL && temp->iVex == headVexIndex)
					{
						temp->iLink = newTemp;
						break;
					}
					if (temp->jLink != NULL && temp->jVex == headVexIndex)
					{
						temp = temp->jLink;
					}
					else if (temp->jLink == NULL && temp->jVex == headVexIndex)
					{
						temp->jLink = newTemp;
						break;
					}
				}

				int tailVexIndex = tempG->jVex;

				if (ret.vexs[tailVexIndex].firstEdge == NULL)
				{
					ret.vexs[tailVexIndex].firstEdge = newTemp;
					bFirstTail = 1;
				}

				temp = ret.vexs[tailVexIndex].firstEdge;
				while (bFirstTail != 1)
				{
					if (temp->iLink != NULL && temp->iVex == tailVexIndex)
					{
						temp = temp->iLink;
					}
					else if (temp != NULL && temp->iLink == NULL && temp->iVex == tailVexIndex)
					{
						temp->iLink = newTemp;
						break;
					}
					if (temp != NULL && temp->jLink != NULL && temp->jVex == tailVexIndex)
					{
						temp = temp->jLink;
					}
					else if (temp != NULL && temp->jLink == NULL && temp->jVex == tailVexIndex)
					{
						temp->jLink = newTemp;
						break;
					}
				}
				if (tempG->iVex == n)
				{
					tempG->visitMark = VISITED;
					tempG = tempG->iLink;
					continue;
				}
				else if (tempG->jVex == n)
				{
					tempG->visitMark = VISITED;
					tempG = tempG->jLink;
					continue;
				}
			}
			else
			{
				tempG->visitMark = UNVISITED;
			}
			if (tempG->iVex == n)
			{
				tempG = tempG->iLink;
			}
			else if (tempG->jVex == n)
			{
				tempG = tempG->jLink;
			}
		}
	}
	return ret;
}
// 邻接多重表图销毁
void AMLGraphDestroy(PAMLGraph G)
{
	PAMLGraphArc* deleteArr = (PAMLGraphArc*)malloc((G->edgeNum) * sizeof(PAMLGraphArc));
	if (deleteArr == NULL)
	{
		printf("malloc failed!\n");
	}
	int index = 0;
	for (int n = 0; n < G->vexNum; ++n)
	{
		PAMLGraphArc temp = G->vexs[n].firstEdge;
		while (temp != NULL)
		{
			if (temp->iVex == n)
			{
				if (temp->visitMark == UNVISITED)
				{
					deleteArr[index++] = temp;
					temp->visitMark = VISITED;
				}
				temp = temp->iLink;
				continue;
			}
			if (temp->jVex == n)
			{
				if (temp->visitMark == UNVISITED)
				{
					deleteArr[index++] = temp;
					temp->visitMark = VISITED;
				}
				temp = temp->jLink;
				continue;
			}
		}
	}
	// 内存释放
	for (int n = 0; n < index; ++n)
	{
		free(deleteArr[n]);
	}
	free(G->vexs);
	free(deleteArr);
}

/*
*				图的遍历
* 广度优先搜索(BFS)  类似于树的层次遍历
* 深度优先搜索(DFS)	 类似于树的先根遍历
*		  有向图与无向图都适用
* 需要设一个辅助数组 visited[0..n-1], 避免同一个结点被访问多次
* 对有向图，若为强连通图则只需调用一次BFS或DFS即可完整遍历，若不是强连通图，需要调用多次
*/
// 邻接矩阵图广度优先搜索遍历
#define VERTEXTYPE int
VERTEXTYPE* MGraphBFS(PMGraph G, VERTEXTYPE firstVisit)
{
	// 访问辅助数组, n 为图在vexs中的索引
	char* bVisited = (char*)malloc(G->vexNum * sizeof(char));
	if (bVisited == NULL)
	{
		printf("malloc failed!\n");
	}
	for (int n = 0; n < G->vexNum; ++n)
	{
		bVisited[n] = 0; // 初始化为未访问
	}
	// 结点访问先后数组
	VERTEXTYPE* visitedVex = (VERTEXTYPE*)malloc(G->vexNum * sizeof(VERTEXTYPE));
	if (visitedVex == NULL)
	{
		printf("malloc failed!\n");
	}
	int visitedVexIndex = 0;
	int firstVexIndex = MGraphLocateVex(G, firstVisit); // 第一个访问的结点
	if (firstVexIndex != -1)
	{
		visitedVex[visitedVexIndex++] = firstVisit;
		bVisited[firstVexIndex] = 1;
	}
	else
	{
		printf("No such vertex!");
		free(visitedVex);
	}

	QueueInfo MGraphQueue;
	QueueInit(&MGraphQueue);
	int rowIndex = firstVexIndex;
	while (1)
	{
		for (int n = 0; n < G->vexNum; ++n)
		{
			if (G->arcs[rowIndex][n].adj != 0 && bVisited[n] == 0)
			{
				QueueEn(&MGraphQueue, G->vexs[n]);
				visitedVex[visitedVexIndex++] = G->vexs[n];
				bVisited[n] = 1;
			}
		}
		if (MGraphQueue.length == 0)
		{
			break;
		}
		VERTEXTYPE queueHead = QueueDe(&MGraphQueue);
		rowIndex = MGraphLocateVex(G, queueHead);
	}
	free(bVisited);
	return visitedVex;
}
// 邻接表图广度优先搜索遍历
VERTEXTYPE* ALGraphBFS(PALGraph G, VERTEXTYPE firstVisit)
{
	// 访问辅助数组, n 为图在vertices中的索引
	char* bVisited = (char*)malloc(G->vertexNum * sizeof(char));
	if (bVisited == NULL)
	{
		printf("malloc failed!\n");
	}
	for (int n = 0; n < G->vertexNum; ++n)
	{
		bVisited[n] = 0; // 初始化为未访问
	}
	// 结点访问先后数组
	VERTEXTYPE* visitedVex = (VERTEXTYPE*)malloc(G->vertexNum * sizeof(VERTEXTYPE));
	if (visitedVex == NULL)
	{
		printf("malloc failed!\n");
	}
	int visitedVexIndex = 0;
	int firstVexIndex = ALGraphLocateVex(G, firstVisit); // 第一个访问的结点
	if (firstVexIndex != -1)
	{
		bVisited[firstVexIndex] = 1;
		visitedVex[visitedVexIndex++] = firstVisit;
	}
	else
	{
		printf("No such vertex!");
		free(visitedVex);
	}
	QueueInfo ALGraphQueue;
	QueueInit(&ALGraphQueue);
	PALGraphArc temp = G->vertices[firstVexIndex].pFirstArc;
	while (1)
	{
		while (temp != NULL)
		{
			if (bVisited[temp->adjvexIndex] == 0)
			{
				VERTEXTYPE tempVex = G->vertices[temp->adjvexIndex].data;
				QueueEn(&ALGraphQueue, tempVex);
				visitedVex[visitedVexIndex++] = tempVex;
				bVisited[temp->adjvexIndex] = 1;
			}
			temp = temp->pNext;
		}
		if (ALGraphQueue.length == 0)
		{
			break;
		}
		VERTEXTYPE vexQueueDe = QueueDe(&ALGraphQueue);
		temp = G->vertices[ALGraphLocateVex(G, vexQueueDe)].pFirstArc;
	}
	free(bVisited);
	return visitedVex;
}
// 十字链表图广度优先搜索遍历
VERTEXTYPE* OLGraphBFS(POLGraph G, VERTEXTYPE firstVisit)
{
	// 访问辅助数组, n 为图在vertices中的索引
	char* bVisited = (char*)malloc(G->vexNum * sizeof(char));
	if (bVisited == NULL)
	{
		printf("malloc failed!\n");
	}
	for (int n = 0; n < G->vexNum; ++n)
	{
		bVisited[n] = 0; // 初始化为未访问
	}
	// 结点访问先后数组
	VERTEXTYPE* visitedVex = (VERTEXTYPE*)malloc(G->vexNum * sizeof(VERTEXTYPE));
	if (visitedVex == NULL)
	{
		printf("malloc failed!\n");
	}
	int visitedVexIndex = 0;
	int firstVexIndex = OLGraphLocateVex(G, firstVisit); // 第一个访问的结点
	if (firstVexIndex != -1)
	{
		bVisited[firstVexIndex] = 1;
		visitedVex[visitedVexIndex++] = firstVisit;
	}
	else
	{
		printf("No such vertex!");
		free(visitedVex);
	}
	QueueInfo OLGraphQueue;
	QueueInit(&OLGraphQueue);
	POLGraphArc temp = G->vList[firstVexIndex].firstOut;
	while (1)
	{
		while (temp != NULL)
		{
			if (bVisited[temp->tailVexIndex] == 0)
			{
				VERTEXTYPE tempVex = G->vList[temp->tailVexIndex].data;
				QueueEn(&OLGraphQueue, tempVex);
				visitedVex[visitedVexIndex++] = tempVex;
				bVisited[temp->tailVexIndex] = 1;
			}
			temp = temp->pHead;
		}
		if (OLGraphQueue.length == 0)
		{
			break;
		}
		VERTEXTYPE queueDeVex = QueueDe(&OLGraphQueue);
		temp = G->vList[OLGraphLocateVex(G, queueDeVex)].firstOut;
	}
	free(bVisited);
	return visitedVex;
}
// 邻接多重表图广度优先搜索遍历
VERTEXTYPE* AMLGraphBFS(PAMLGraph G, VERTEXTYPE firstVisit)
{
	// 访问辅助数组, n 为图在vexs中的索引
	char* bVisited = (char*)malloc(G->vexNum * sizeof(char));
	if (bVisited == NULL)
	{
		printf("malloc failed!\n");
	}
	for (int n = 0; n < G->vexNum; ++n)
	{
		bVisited[n] = 0; // 初始化为未访问
	}
	// 结点访问先后数组
	VERTEXTYPE* visitedVex = (VERTEXTYPE*)malloc(G->vexNum * sizeof(VERTEXTYPE));
	if (visitedVex == NULL)
	{
		printf("malloc failed!\n");
	}
	int visitedVexIndex = 0;
	int firstVexIndex = AMLGraphLocateVex(G, firstVisit); // 第一个访问的结点
	if (firstVexIndex != -1)
	{
		bVisited[firstVexIndex] = 1;
		visitedVex[visitedVexIndex++] = firstVisit;
	}
	else
	{
		printf("No such vertex!");
		free(visitedVex);
	}
	QueueInfo AMLGraphQueue;
	QueueInit(&AMLGraphQueue);
	PAMLGraphArc temp = G->vexs[firstVexIndex].firstEdge;
	int index = firstVexIndex;
	while (1)
	{
		while (temp != NULL)
		{
			if (temp->iVex == index)
			{
				if (bVisited[temp->jVex] == 0)
				{
					VERTEXTYPE tempVex = G->vexs[temp->jVex].data;
					QueueEn(&AMLGraphQueue, tempVex);
					visitedVex[visitedVexIndex++] = tempVex;
					bVisited[temp->jVex] = 1;
				}
				temp = temp->iLink;
				continue;
			}
			if (temp->jVex == index)
			{
				if (bVisited[temp->iVex] == 0)
				{
					VERTEXTYPE tempVex = G->vexs[temp->iVex].data;
					QueueEn(&AMLGraphQueue, tempVex);
					visitedVex[visitedVexIndex++] = tempVex;
					bVisited[temp->iVex] = 1;
				}
				temp = temp->jLink;
				continue;
			}
		}
		if (AMLGraphQueue.length == 0)
		{
			break;
		}
		VERTEXTYPE queueDeVex = QueueDe(&AMLGraphQueue);
		index = AMLGraphLocateVex(G, queueDeVex);
		temp = G->vexs[index].firstEdge;
	}
	free(bVisited);
	return visitedVex;
}

// 邻接矩阵图深度优先搜索遍历
VERTEXTYPE* MGraphDFS(PMGraph G, VERTEXTYPE firstVisit)
{
	char* bVisited = (char*)malloc(G->vexNum * sizeof(char));
	if (bVisited == NULL)
	{
		printf("malloc failed!\n");
	}
	for (int n = 0; n < G->vexNum; ++n)
	{
		bVisited[n] = 0; // 初始化为未访问
	}
	// 结点访问先后数组
	VERTEXTYPE* visitedVex = (VERTEXTYPE*)malloc(G->vexNum * sizeof(VERTEXTYPE));
	if (visitedVex == NULL)
	{
		printf("malloc failed!\n");
	}
	int visitedVexIndex = 0;
	int firstVexIndex = MGraphLocateVex(G, firstVisit);
	if (firstVexIndex != -1)
	{
		bVisited[firstVexIndex] = 1;
		visitedVex[visitedVexIndex++] = firstVisit;
	}
	else
	{
		printf("No such vertex!");
		free(visitedVex);
	}
	StackInfo MGraphStack;
	StackInit(&MGraphStack);
	StackPush(&MGraphStack, firstVisit); // 注意该步不可少，每访问一个节点都应该进栈
	int rowIndex = firstVexIndex;
	while (1)
	{
		for (int n = 0; n < G->vexNum; ++n)
		{
			if (G->arcs[rowIndex][n].adj != 0 && bVisited[n] == 0)
			{
				rowIndex = n;
				StackPush(&MGraphStack, G->vexs[n]);
				bVisited[n] = 1;
				visitedVex[visitedVexIndex++] = G->vexs[n];
				break;
			}
			else if (n == G->vexNum - 1)
			{
				if (MGraphStack.size == 0)
				{
					goto WHILEOUT;
				}
				VERTEXTYPE stackDeTemp = StackPop(&MGraphStack);
				rowIndex = MGraphLocateVex(G, stackDeTemp);
			}
		}
	}
WHILEOUT:
	free(bVisited);
	return visitedVex;
}
// 邻接表图深度优先搜索遍历
VERTEXTYPE* ALGraphDFS(PALGraph G, VERTEXTYPE firstVisit)
{
	char* bVisited = (char*)malloc(G->vertexNum * sizeof(char));
	if (bVisited == NULL)
	{
		printf("malloc failed!\n");
	}
	for (int n = 0; n < G->vertexNum; ++n)
	{
		bVisited[n] = 0; // 初始化为未访问
	}
	// 结点访问先后数组
	VERTEXTYPE* visitedVex = (VERTEXTYPE*)malloc(G->vertexNum * sizeof(VERTEXTYPE));
	if (visitedVex == NULL)
	{
		printf("malloc failed!\n");
	}
	int visitedVexIndex = 0;
	int firstVexIndex = ALGraphLocateVex(G, firstVisit);
	if (firstVexIndex != -1)
	{
		bVisited[firstVexIndex] = 1;
		visitedVex[visitedVexIndex++] = firstVisit;
	}
	else
	{
		printf("No such vertex!");
		free(visitedVex);
	}
	StackInfo ALGraphStack;
	StackInit(&ALGraphStack);
	StackPush(&ALGraphStack, firstVisit); // 注意该步不可少，每访问一个节点都应该进栈
	PALGraphArc temp = G->vertices[firstVexIndex].pFirstArc;
	while (1)
	{
		while (temp != NULL)
		{
			if (bVisited[temp->adjvexIndex] == 0)
			{
				VERTEXTYPE temVex = G->vertices[temp->adjvexIndex].data;
				StackPush(&ALGraphStack, temVex);
				visitedVex[visitedVexIndex++] = temVex;
				bVisited[temp->adjvexIndex] = 1;
				temp = G->vertices[temp->adjvexIndex].pFirstArc;
			}
			else
			{
				temp = temp->pNext;
			}
		}
		if (ALGraphStack.size == 0)
		{
			break;
		}
		VERTEXTYPE vexStackTemp = StackPop(&ALGraphStack);
		temp = G->vertices[ALGraphLocateVex(G, vexStackTemp)].pFirstArc;
	}
	free(bVisited);
	return visitedVex;
}
// 十字链表图深度优先搜索遍历
VERTEXTYPE* OLGraphDFS(POLGraph G, VERTEXTYPE firstVisit)
{
	char* bVisited = (char*)malloc(G->vexNum * sizeof(char));
	if (bVisited == NULL)
	{
		printf("malloc failed!\n");
	}
	for (int n = 0; n < G->vexNum; ++n)
	{
		bVisited[n] = 0; // 初始化为未访问
	}
	// 结点访问先后数组
	VERTEXTYPE* visitedVex = (VERTEXTYPE*)malloc(G->vexNum * sizeof(VERTEXTYPE));
	if (visitedVex == NULL)
	{
		printf("malloc failed!\n");
	}
	int visitedVexIndex = 0;
	int firstVexIndex = OLGraphLocateVex(G, firstVisit);
	if (firstVexIndex != -1)
	{
		bVisited[firstVexIndex] = 1;
		visitedVex[visitedVexIndex++] = firstVisit;
	}
	else
	{
		printf("No such vertex!");
		free(visitedVex);
	}
	StackInfo OLGraphStack;
	StackInit(&OLGraphStack);
	StackPush(&OLGraphStack, firstVisit); // 注意该步不可少，每访问一个节点都应该进栈
	POLGraphArc temp = G->vList[firstVexIndex].firstOut;
	while (1)
	{
		while (temp != NULL)
		{
			if (bVisited[temp->tailVexIndex] == 0)
			{
				VERTEXTYPE tempVex = G->vList[temp->tailVexIndex].data;
				StackPush(&OLGraphStack, tempVex);
				visitedVex[visitedVexIndex++] = tempVex;
				bVisited[temp->tailVexIndex] = 1;
				temp = G->vList[temp->tailVexIndex].firstOut;
			}
			else
			{
				temp = temp->pHead;
			}
		}
		if (OLGraphStack.size == 0)
		{
			break;
		}
		VERTEXTYPE stackPopVex = StackPop(&OLGraphStack);
		temp = G->vList[OLGraphLocateVex(G, stackPopVex)].firstOut;
	}
	free(bVisited);
	return visitedVex;
}
// 邻接多重表图深度优先搜索遍历
VERTEXTYPE* AMLGraphDFS(PAMLGraph G, VERTEXTYPE firstVisit)
{
	char* bVisited = (char*)malloc(G->vexNum * sizeof(char));
	if (bVisited == NULL)
	{
		printf("malloc failed!\n");
	}
	for (int n = 0; n < G->vexNum; ++n)
	{
		bVisited[n] = 0; // 初始化为未访问
	}
	// 结点访问先后数组
	VERTEXTYPE* visitedVex = (VERTEXTYPE*)malloc(G->vexNum * sizeof(VERTEXTYPE));
	if (visitedVex == NULL)
	{
		printf("malloc failed!\n");
	}
	int visitedVexIndex = 0;
	int firstVexIndex = AMLGraphLocateVex(G, firstVisit);
	if (firstVexIndex != -1)
	{
		bVisited[firstVexIndex] = 1;
		visitedVex[visitedVexIndex++] = firstVisit;
	}
	else
	{
		printf("No such vertex!");
		free(visitedVex);
	}
	StackInfo AMLGraphStack;
	StackInit(&AMLGraphStack);
	StackPush(&AMLGraphStack, firstVisit); // 注意该步不可少，每访问一个节点都应该进栈
	PAMLGraphArc temp = G->vexs[firstVexIndex].firstEdge;
	int index = firstVexIndex;
	while (1)
	{
		while (temp != NULL)
		{
			if (temp->iVex == index)
			{
				if (bVisited[temp->jVex] == 0)
				{
					VERTEXTYPE tempVex = G->vexs[temp->jVex].data;
					StackPush(&AMLGraphStack, tempVex);
					visitedVex[visitedVexIndex++] = tempVex;
					bVisited[temp->jVex] = 1;
					index = temp->jVex;
					temp = G->vexs[index].firstEdge;
				}
				else
				{
					temp = temp->iLink;
				}
				continue;
			}
			if (temp->jVex == index)
			{
				if (bVisited[temp->iVex] == 0)
				{
					VERTEXTYPE tempVex = G->vexs[temp->iVex].data;
					StackPush(&AMLGraphStack, tempVex);
					visitedVex[visitedVexIndex++] = tempVex;
					bVisited[temp->iVex] = 1;
					index = temp->iVex;
					temp = G->vexs[index].firstEdge;
				}
				else
				{
					temp = temp->jLink;
				}
			}
		}
		if (AMLGraphStack.size == 0)
		{
			break;
		}
		VERTEXTYPE stackPopVex = StackPop(&AMLGraphStack);
		index = AMLGraphLocateVex(G, stackPopVex);
		temp = G->vexs[index].firstEdge;
	}
	free(bVisited);
	return visitedVex;
}

/*
*									构建最小生成树
* 普里姆(Prim)算法: 按顶点构建生成树; 适用于稠密图(边多); 时间复杂度: O(|V|^2)或O(|n|^2)
* 克鲁斯卡尔(Kruskal)算法: 按边构建生成树; 适用于稀疏图(边少); 时间复杂度: O(|E|log|E|)
* note :: 不提供无权图的"最小生成树"(无意义)
*/
// 构建邻接矩阵图最小生成树
MGraph MGraphPrim(PMGraph G, VERTEXTYPE firstVisit)
{
	if (G->graphKind == UDN)
	{
		// 到剩余各个顶点的权值, 0代表在已生成树的顶点, -1代表无法一次性到达该顶点
		ARCTYPE* weight = (ARCTYPE*)malloc(G->vexNum * sizeof(ARCTYPE));
		if (weight == NULL)
		{
			printf("malloc failed!\n");
			return;
		}
		// 创建并初始化返回图
		MGraph RetMraphMain;
		PMGraph PRetMraph = &RetMraphMain;
		PRetMraph->graphKind = G->graphKind;
		PRetMraph->arcNum = G->vexNum - 1; // 最小生成树树枝数等于 节点数-1
		PRetMraph->vexNum = G->vexNum;
		PRetMraph->vexs = (VERTEXTYPE*)malloc(G->vexNum * sizeof(VERTEXTYPE));
		PRetMraph->arcs = (PMGraphArc*)malloc(G->vexNum * sizeof(PMGraphArc));
		if (PRetMraph->vexs == NULL || PRetMraph->arcs == NULL)
		{
			printf("malloc failed!\n");
			return;
		}
		for (int n = 0; n < G->vexNum; ++n)
		{
			PRetMraph->vexs[n] = G->vexs[n];
			PRetMraph->arcs[n] = (PMGraphArc)malloc(G->vexNum * sizeof(MGraphArc));
			if (PRetMraph->arcs[n] == NULL)
			{
				printf("malloc failed!\n");
			}
			for (int m = 0; m < G->vexNum; ++m)
			{
				PRetMraph->arcs[n][m].adj = 0;
				PRetMraph->arcs[n][m].arcInfo = NULL;
			}
			// 初始化 weight 数组
			weight[n] = -1;
		}
		int rowIndex = MGraphLocateVex(G, firstVisit);
		// 最小边的权值
		ARCTYPE minArc;
		int minArcIndex = -1;
		while (1)
		{
			// weight
			for (int i = 0; i < G->vexNum; ++i)
			{
				if (i == rowIndex)
				{
					weight[rowIndex] = 0;
				}
				ARCTYPE temp = G->arcs[rowIndex][i].adj;
				if (temp != 0 && (weight[i] == -1 || weight[i] > temp))
				{
					weight[i] = temp;
					if (minArcIndex == -1 || minArc > temp)
					{
						minArc = temp;
						minArcIndex = i;
					}
				}
			}
			if (minArcIndex == -1)
			{
				for (int n = 0; n < G->vexNum; ++n)
				{
					if ((minArcIndex == -1 && weight[n] > 0) || (minArcIndex != -1 && weight[n] > 0 && weight[n] < minArc))
					{
						minArc = weight[n];
						minArcIndex = n;
						for (int i = 0; i < G->vexNum; ++i)
						{
							if (G->arcs[n][i].adj == 5 && weight[i] == 0)
							{
								rowIndex = i;
							}
						}
						continue;
					}
				}
			}
			if (minArcIndex == -1)
			{
				break;
			}
			else
			{
				PRetMraph->arcs[rowIndex][minArcIndex].adj = minArc;
				PRetMraph->arcs[minArcIndex][rowIndex].adj = minArc;
				rowIndex = minArcIndex;
				minArcIndex = -1;
			}
		}
		free(weight);
		return RetMraphMain;
	}
	else
	{
		return;
	}
}
// 构建邻接表图最小生成树
ALGraph ALGraphPrim(PALGraph G, VERTEXTYPE firstVisit)
{
	if (G->graphKind == UDN)
	{
		typedef struct Weight
		{
			int i, j; // i 是 已在树中
			ARCTYPE w;
		}Weight;
		typedef struct MinArc
		{
			ARCTYPE minarc;
			int i, j;
		}MinArc;
		ALGraph ret;
		ret.graphKind = UDN;
		ret.arcNum = G->vertexNum - 1; // 最小生成树树枝数等于 节点数-1
		ret.vertexNum = G->vertexNum;
		ret.vertices = (PALGraphVex)malloc(G->vertexNum * sizeof(ALGraphVex));
		Weight* weight = (Weight*)malloc(G->vertexNum * sizeof(Weight));
		if (ret.vertices == NULL || weight == NULL)
		{
			printf("malloc failed!\n");
		}
		for (int n = 0; n < G->vertexNum; ++n)
		{
			weight[n].w = -1;
			ret.vertices[n].data = G->vertices[n].data;
			ret.vertices[n].pFirstArc = NULL;
		}
		int index = ALGraphLocateVex(G, firstVisit);
		PALGraphArc temp = G->vertices[index].pFirstArc;
		while (1)
		{
			MinArc minArc;
			minArc.minarc = 0;
			while (temp != NULL)
			{
				weight[index].w = 0;
				int adjIndex = temp->adjvexIndex;
				if (weight[adjIndex].w == -1 || weight[adjIndex].w > temp->adj)
				{
					weight[adjIndex].w = temp->adj;
					weight[adjIndex].i = index;
					weight[adjIndex].j = adjIndex;
				}
				temp = temp->pNext;
			}
			for (int n = 0; n < G->vertexNum; ++n)
			{
				if ((minArc.minarc == 0 && weight[n].w > 0) || (minArc.minarc > weight[n].w && weight[n].w > 0))
				{
					minArc.minarc = weight[n].w;
					minArc.i = weight[n].i;
					minArc.j = weight[n].j;
				}
			}
			if (minArc.minarc != 0)
			{
				PALGraphArc tempArc = (PALGraphArc)malloc(sizeof(ALGraphArc));
				if (tempArc == NULL)
				{
					printf("malloc failed!\n");
				}
				tempArc->adj = minArc.minarc;
				tempArc->adjvexIndex = minArc.j;
				tempArc->arcInfo = NULL;
				tempArc->pNext = NULL;
				PALGraphArc tempArcNext = ret.vertices[minArc.i].pFirstArc;
				if (tempArcNext != NULL)
				{
					while (tempArcNext->pNext != NULL)
					{
						tempArcNext = tempArcNext->pNext;
					}
					tempArcNext->pNext = tempArc;
				}
				else
				{
					ret.vertices[minArc.i].pFirstArc = tempArc;
				}

				tempArc = (PALGraphArc)malloc(sizeof(ALGraphArc));
				if (tempArc == NULL)
				{
					printf("malloc failed!\n");
				}
				tempArc->adj = minArc.minarc;
				tempArc->adjvexIndex = minArc.i;
				tempArc->arcInfo = NULL;
				tempArc->pNext = NULL;
				tempArcNext = ret.vertices[minArc.j].pFirstArc;
				if (tempArcNext != NULL)
				{
					while (tempArcNext->pNext != NULL)
					{
						tempArcNext = tempArcNext->pNext;
					}
					tempArcNext->pNext = tempArc;
				}
				else
				{
					ret.vertices[minArc.j].pFirstArc = tempArc;
				}

				index = minArc.j;
				temp = G->vertices[index].pFirstArc;
			}
			else
			{
				break;
			}
		}
		free(weight);
		return ret;
	}
	else
	{
		return;
	}
}
// 构建邻接多重表图最小生成树
AMLGraph AMLGraphPrim(PAMLGraph G, VERTEXTYPE firstVisit)
{
	if (G->graphKind == AMLUDN)
	{
		typedef struct Weight
		{
			int i, j; // i 是 已在树中
			ARCTYPE w;
		}Weight;
		typedef struct MinArc
		{
			ARCTYPE minarc;
			int i, j;
		}MinArc;
		AMLGraph ret;
		ret.graphKind = G->graphKind;
		ret.vexNum = G->vexNum;
		ret.edgeNum = G->vexNum - 1;
		ret.vexs = (PAMLGraphVex)malloc(G->vexNum * sizeof(AMLGraphVex));
		Weight* weight = (Weight*)malloc(G->vexNum * sizeof(Weight));
		if (ret.vexs == NULL || weight == NULL)
		{
			printf("malloc failed!\n");
		}
		for (int n = 0; n < G->vexNum; ++n)
		{
			ret.vexs[n].data = G->vexs[n].data;
			ret.vexs[n].firstEdge = NULL;
			weight[n].w = -1;
		}
		int index = AMLGraphLocateVex(G, firstVisit);
		PAMLGraphArc temp = G->vexs[index].firstEdge;
		while (1)
		{
			MinArc minArc;
			minArc.minarc = 0;
			while (temp != NULL)
			{
				weight[index].w = 0;
				weight[index].i = index;
				if (temp->iVex == index && (weight[temp->jVex].w == -1 || weight[temp->jVex].w > temp->edgeLength))
				{
					weight[temp->jVex].i = index;
					weight[temp->jVex].j = temp->jVex;
					weight[temp->jVex].w = temp->edgeLength;
					temp = temp->iLink;
					continue;
				}
				else if (temp->jVex == index && (weight[temp->iVex].w == -1 || weight[temp->iVex].w > temp->edgeLength))
				{
					weight[temp->iVex].i = index;
					weight[temp->iVex].j = temp->iVex;
					weight[temp->iVex].w = temp->edgeLength;
					temp = temp->jLink;
					continue;
				}
				if (temp->iVex == index)
				{
					temp = temp->iLink;
				}
				else
				{
					temp = temp->jLink;
				}
			}
			for (int n = 0; n < G->vexNum; ++n)
			{
				if ((minArc.minarc > weight[n].w && weight[n].w > 0) || (minArc.minarc == 0 && weight[n].w > 0))
				{
					minArc.minarc = weight[n].w;
					minArc.i = weight[n].i;
					minArc.j = weight[n].j;
				}
			}
			if (minArc.minarc != 0)
			{
				PAMLGraphArc tempArc = (PAMLGraphArc)malloc(sizeof(AMLGraphArc));
				if (tempArc == NULL)
				{
					printf("malloc failed!\n");
				}
				tempArc->edgeLength = minArc.minarc;
				tempArc->iVex = minArc.i;
				tempArc->jVex = minArc.j;
				tempArc->info = NULL;
				tempArc->visitMark = UNVISITED;
				tempArc->iLink = NULL;
				tempArc->jLink = NULL;
				PAMLGraphArc tempArcNext = ret.vexs[minArc.i].firstEdge;
				if (tempArcNext != NULL)
				{
					while (1)
					{
						if (tempArcNext->iLink != NULL && tempArcNext->iVex == minArc.i)
						{
							tempArcNext = tempArcNext->iLink;
						}
						else if (tempArcNext->jLink != NULL && tempArcNext->jVex == minArc.i)
						{
							tempArcNext = tempArcNext->jLink;
						}
						else if (tempArcNext->iLink == NULL && tempArcNext->iVex == minArc.i)
						{
							tempArcNext->iLink = tempArc;
							break;
						}
						else if (tempArcNext->jLink == NULL && tempArcNext->jVex == minArc.i)
						{
							tempArcNext->jLink = tempArc;
							break;
						}
					}
				}
				else
				{
					ret.vexs[minArc.i].firstEdge = tempArc;
				}
				tempArcNext = ret.vexs[minArc.j].firstEdge;
				if (tempArcNext != NULL)
				{
					while (1)
					{
						if (tempArcNext->iLink != NULL && tempArcNext->iVex == minArc.i)
						{
							tempArcNext = tempArc->iLink;
						}
						else if (tempArcNext->jLink != NULL && tempArcNext->jVex == minArc.i)
						{
							tempArcNext = tempArc->jLink;
						}
						else if (tempArcNext->iLink == NULL && tempArcNext->iVex == minArc.i)
						{
							tempArcNext->iLink = tempArc;
							break;
						}
						else if (tempArcNext->jLink == NULL && tempArcNext->jVex == minArc.i)
						{
							tempArcNext->jLink = tempArc;
							break;
						}
					}
				}
				else
				{
					ret.vexs[minArc.j].firstEdge = tempArc;
				}
				index = minArc.j;
				temp = G->vexs[index].firstEdge;
			}
			else
			{
				break;
			}
		}

		free(weight);
		return ret;
	}
	else
	{
		return;
	}
}
// 构建邻接矩阵图最小生成树(Kruskal 算法)
MGraph MGraphKruskal(PMGraph G)
{
	if (G->graphKind == UDG || G->graphKind == UDN)
	{
		// 使用 并查表
		PKruskalSort sortedArr = (PKruskalSort)malloc(G->arcNum * sizeof(KruskalSort));
		if (sortedArr == NULL)
		{
			printf("malloc failed!\n");
		}
		int tempIndexOfSortedArr = 0; // 此索引仅供下一个循环使用
		for (int n = 0; n < G->vexNum; ++n)
		{
			for (int m = n; m < G->vexNum; ++m)
			{
				if (G->arcs[n][m].adj != 0)
				{
					sortedArr[tempIndexOfSortedArr].arc = G->arcs[n][m].adj;
					sortedArr[tempIndexOfSortedArr].i = n;
					sortedArr[tempIndexOfSortedArr++].j = m;
				}
			}
		}
		QuickSort(sortedArr, 0, G->arcNum - 1, 1);
		MGraph ret;
		ret.arcNum = G->vexNum - 1;
		ret.graphKind = G->graphKind;
		ret.vexNum = G->vexNum;
		ret.vexs = (VERTEXTYPE*)malloc(G->vexNum * sizeof(VERTEXTYPE));
		ret.arcs = (PMGraphArc*)malloc(G->vexNum * sizeof(PMGraphArc));
		if (ret.vexs == NULL || ret.arcs == NULL)
		{
			printf("malloc failed!\n");
		}
		for (int n = 0; n < G->vexNum; ++n)
		{
			ret.vexs[n] = G->vexs[n];
			ret.arcs[n] = (PMGraphArc)malloc(G->vexNum * sizeof(MGraphArc));
			if (ret.arcs[n] == NULL)
			{
				printf("malloc failed!\n");
			}
		}
		for (int i = 0; i < G->vexNum; i++)
		{
			for (int n = 0; n < G->vexNum; ++n)
			{
				ret.arcs[i][n].adj = 0;
				ret.arcs[i][n].arcInfo = NULL;
			}
		}
		typedef struct Check
		{
			int parent;
			char hasParent;
		}Check;
		Check* checkArr = (Check*)malloc(G->arcNum * sizeof(Check));
		if (checkArr == NULL)
		{
			printf("malloc failed!\n");
		}
		for (int n = 0; n < G->arcNum; ++n)
		{
			checkArr[n].hasParent = 0;
		}
		for (int n = 0; n < G->vexNum - 1; ++n)
		{
			if (checkArr[sortedArr[n].i].hasParent == 0 || checkArr[sortedArr[n].j].hasParent == 0)
			{
				checkArr[sortedArr[n].i].parent = sortedArr[n].i;
				checkArr[sortedArr[n].j].parent = sortedArr[n].i;
				checkArr[sortedArr[n].i].hasParent = 1;
				checkArr[sortedArr[n].j].hasParent = 1;
				ret.arcs[sortedArr[n].i][sortedArr[n].j].adj = sortedArr[n].arc;
				ret.arcs[sortedArr[n].j][sortedArr[n].i].adj = sortedArr[n].arc;
			}
			else
			{
				if (checkArr[sortedArr[n].i].parent != checkArr[sortedArr[n].j].parent)
				{
					checkArr[sortedArr[n].i].parent = checkArr[sortedArr[n].j].parent;
					ret.arcs[sortedArr[n].i][sortedArr[n].j].adj = sortedArr[n].arc;
					ret.arcs[sortedArr[n].j][sortedArr[n].i].adj = sortedArr[n].arc;
				}
			}
		}
		free(checkArr);
		free(sortedArr);
		return ret;
	}
	else
	{
		return;
	}
}
// 构建邻接表图最小生成树(Kruskal 算法)
ALGraph ALGraphKruskal(PALGraph G)
{
	if (G->graphKind == UDG || G->graphKind == UDN)
	{
		PKruskalSort sortedArr = (PKruskalSort)malloc(G->arcNum * sizeof(KruskalSort));
		if (sortedArr == NULL)
		{
			printf("malloc failed!\n");
		}
		int tempIndexOfSortedArr = 0;
		// 根据邻接表的储存结构特点来判定是否重复录入同一条弧
		for (int n = 0; n < G->vertexNum; ++n)
		{
			PALGraphArc temp = G->vertices[n].pFirstArc;
			while (temp != NULL)
			{
				if (temp->adjvexIndex > n)
				{
					sortedArr[tempIndexOfSortedArr].arc = temp->adj;
					sortedArr[tempIndexOfSortedArr].i = n;
					sortedArr[tempIndexOfSortedArr++].j = temp->adjvexIndex;
				}
				temp = temp->pNext;
			}
		}
		QuickSort(sortedArr, 0, G->arcNum - 1, 1);
		ALGraph ret;
		ret.arcNum = G->vertexNum - 1;
		ret.graphKind = G->graphKind;
		ret.vertexNum = G->vertexNum;
		ret.vertices = (PALGraphVex)malloc(G->vertexNum * sizeof(ALGraphVex));
		if (ret.vertices == NULL)
		{
			printf("malloc failed!\n");
		}
		for (int n = 0; n < G->vertexNum; ++n)
		{
			ret.vertices[n].data = G->vertices[n].data;
			ret.vertices[n].pFirstArc = NULL;
		}
		typedef struct Check
		{
			int parent;
			char hasParent;
		}Check;
		Check* checkArr = (Check*)malloc(G->arcNum * sizeof(Check));
		if (checkArr == NULL)
		{
			printf("malloc failed!\n");
		}
		for (int n = 0; n < G->arcNum; ++n)
		{
			checkArr[n].hasParent = 0;
		}
		// note: 不使用 G->arcNum 的原因是ret中边的数目只能是 G->vertexNum-1
		for (int n = 0; n < G->vertexNum - 1; ++n)
		{
			if (checkArr[sortedArr[n].i].hasParent == 0 || checkArr[sortedArr[n].j].hasParent == 0)
			{
				PALGraphArc temp = (PALGraphArc)malloc(sizeof(ALGraphArc));
				if (temp == NULL)
				{
					printf("malloc failed!\n");
				}
				temp->adj = sortedArr[n].arc;
				temp->adjvexIndex = sortedArr[n].j;
				temp->arcInfo = NULL;
				temp->pNext = NULL;
				PALGraphArc tempTemp = ret.vertices[sortedArr[n].i].pFirstArc;
				if (tempTemp == NULL)
				{
					ret.vertices[sortedArr[n].i].pFirstArc = temp;
				}
				else
				{
					while (tempTemp->pNext != NULL)
					{
						tempTemp = tempTemp->pNext;
					}
					tempTemp->pNext = temp;
				}
				temp = (PALGraphArc)malloc(sizeof(ALGraphArc));
				if (temp == NULL)
				{
					printf("malloc failed!\n");
				}
				temp->adj = sortedArr[n].arc;
				temp->adjvexIndex = sortedArr[n].i;
				temp->arcInfo = NULL;
				temp->pNext = NULL;
				tempTemp = ret.vertices[sortedArr[n].j].pFirstArc;
				if (tempTemp == NULL)
				{
					ret.vertices[sortedArr[n].j].pFirstArc = temp;
				}
				else
				{
					while (tempTemp->pNext != NULL)
					{
						tempTemp = tempTemp->pNext;
					}
					tempTemp->pNext = temp;
				}
				checkArr[sortedArr[n].i].hasParent = 1;
				checkArr[sortedArr[n].j].hasParent = 1;
				checkArr[sortedArr[n].i].parent = sortedArr[n].i;
				checkArr[sortedArr[n].j].parent = sortedArr[n].i;
			}
			else
			{
				if (checkArr[sortedArr[n].i].parent != checkArr[sortedArr[n].j].parent)
				{
					PALGraphArc temp = (PALGraphArc)malloc(sizeof(ALGraphArc));
					if (temp == NULL)
					{
						printf("malloc failed!\n");
					}
					temp->adj = sortedArr[n].arc;
					temp->adjvexIndex = sortedArr[n].j;
					temp->arcInfo = NULL;
					temp->pNext = NULL;
					PALGraphArc tempTemp = ret.vertices[sortedArr[n].i].pFirstArc;
					if (tempTemp == NULL)
					{
						ret.vertices[sortedArr[n].i].pFirstArc = temp;
					}
					else
					{
						while (tempTemp->pNext != NULL)
						{
							tempTemp = tempTemp->pNext;
						}
						tempTemp->pNext = temp;
					}
					temp = (PALGraphArc)malloc(sizeof(ALGraphArc));
					if (temp == NULL)
					{
						printf("malloc failed!\n");
					}
					temp->adj = sortedArr[n].arc;
					temp->adjvexIndex = sortedArr[n].i;
					temp->arcInfo = NULL;
					temp->pNext = NULL;
					tempTemp = ret.vertices[sortedArr[n].j].pFirstArc;
					if (tempTemp == NULL)
					{
						ret.vertices[sortedArr[n].j].pFirstArc = temp;
					}
					else
					{
						while (tempTemp->pNext != NULL)
						{
							tempTemp = tempTemp->pNext;
						}
						tempTemp->pNext = temp;
					}
					checkArr[sortedArr[n].j].parent = checkArr[sortedArr[n].i].parent;
				}
			}
		}
		free(sortedArr);
		free(checkArr);
		return ret;
	}
	else
	{
		return;
	}
}
// 构建邻接多重表图最小生成树(Kruskal 算法)
AMLGraph AMLGraphKruskal(PAMLGraph G)
{
	if (G->graphKind == AMLUDG || G->graphKind == AMLUDN)
	{
		PKruskalSort sortedArr = (PKruskalSort)malloc(G->edgeNum * sizeof(KruskalSort));
		if (sortedArr == NULL)
		{
			printf("malloc failed!\n");
		}
		int tempIndexOfSortedArr = 0;
		// 根据邻接表的储存结构特点来判定是否重复录入同一条弧
		for (int n = 0; n < G->vexNum; ++n)
		{
			PAMLGraphArc temp = G->vexs[n].firstEdge;
			while (temp != NULL)
			{
				if (temp->iVex == n)
				{
					if (temp->jVex > n)
					{
						sortedArr[tempIndexOfSortedArr].arc = temp->edgeLength;
						sortedArr[tempIndexOfSortedArr].i = n;
						sortedArr[tempIndexOfSortedArr++].j = temp->jVex;
					}
					temp = temp->iLink;
				}
				else
				{
					if (temp->iVex > n)
					{
						sortedArr[tempIndexOfSortedArr].arc = temp->edgeLength;
						sortedArr[tempIndexOfSortedArr].i = n;
						sortedArr[tempIndexOfSortedArr++].j = temp->iVex;
					}
					temp = temp->jLink;
				}
			}
		}
		QuickSort(sortedArr, 0, G->edgeNum - 1, 1);
		AMLGraph ret;
		ret.edgeNum = G->vexNum - 1;
		ret.vexNum = G->vexNum;
		ret.graphKind = G->graphKind;
		ret.vexs = (PAMLGraphVex)malloc(G->vexNum * sizeof(AMLGraphVex));
		if (ret.vexs == NULL)
		{
			printf("malloc failed!\n");
		}
		for (int n = 0; n < G->vexNum; ++n)
		{
			ret.vexs[n].data = G->vexs[n].data;
			ret.vexs[n].firstEdge = NULL;
		}
		typedef struct Check
		{
			int parent;
			char hasParent;
		}Check;
		Check* checkArr = (Check*)malloc(G->edgeNum * sizeof(Check));
		if (checkArr == NULL)
		{
			printf("malloc failed!\n");
		}
		for (int n = 0; n < G->edgeNum; ++n)
		{
			checkArr[n].hasParent = 0;
		}
		for (int n = 0; n < G->vexNum - 1; ++n)
		{
			if (checkArr[sortedArr[n].i].hasParent == 0 || checkArr[sortedArr[n].j].hasParent == 0)
			{
				PAMLGraphArc temp = (PAMLGraphArc)malloc(sizeof(AMLGraphArc));
				if (temp == NULL)
				{
					printf("malloc failed!\n");
				}
				temp->edgeLength = sortedArr[n].arc;
				temp->iVex = sortedArr[n].i;
				temp->jVex = sortedArr[n].j;
				temp->iLink = NULL;
				temp->jLink = NULL;
				temp->info = NULL;
				temp->visitMark = UNVISITED;
				PAMLGraphArc tempTemp = ret.vexs[sortedArr[n].i].firstEdge;
				if (tempTemp == NULL)
				{
					ret.vexs[sortedArr[n].i].firstEdge = temp;
				}
				else
				{
					char isI = 0;
					while (1)
					{
						if (tempTemp->iVex == sortedArr[n].i)
						{
							if (tempTemp->iLink == NULL)
							{
								isI = 1;
								break;
							}
							tempTemp = tempTemp->iLink;
						}
						else if (tempTemp->jVex == sortedArr[n].i)
						{
							if (tempTemp->jLink == NULL)
							{
								isI = 0;
								break;
							}
							tempTemp = tempTemp->jLink;
						}
					}
					if (isI == 1)
					{
						tempTemp->iLink = temp;
					}
					else
					{
						tempTemp->jLink = temp;
					}
				}
				// 另一个顶点连接边
				tempTemp = ret.vexs[sortedArr[n].j].firstEdge;
				if (tempTemp == NULL)
				{
					ret.vexs[sortedArr[n].j].firstEdge = temp;
				}
				else
				{
					char isI = 0;
					while (1)
					{
						if (tempTemp->iVex == sortedArr[n].j)
						{
							if (tempTemp->iLink == NULL)
							{
								isI = 1;
								break;
							}
							tempTemp = tempTemp->iLink;
						}
						else if (tempTemp->jVex == sortedArr[n].j)
						{
							if (tempTemp->jLink == NULL)
							{
								isI = 0;
								break;
							}
							tempTemp = tempTemp->jLink;
						}
					}
					if (isI == 1)
					{
						tempTemp->iLink = temp;
					}
					else
					{
						tempTemp->jLink = temp;
					}
				}
				checkArr[sortedArr[n].i].hasParent = 1;
				checkArr[sortedArr[n].j].hasParent = 1;
				checkArr[sortedArr[n].i].parent = sortedArr[n].i;
				checkArr[sortedArr[n].j].parent = sortedArr[n].i;
			}
			else
			{
				if (checkArr[sortedArr[n].i].parent != checkArr[sortedArr[n].j].parent)
				{
					PAMLGraphArc temp = (PAMLGraphArc)malloc(sizeof(AMLGraphArc));
					if (temp == NULL)
					{
						printf("malloc failed!\n");
					}
					temp->edgeLength = sortedArr[n].arc;
					temp->iVex = sortedArr[n].i;
					temp->jVex = sortedArr[n].j;
					temp->iLink = NULL;
					temp->jLink = NULL;
					temp->info = NULL;
					temp->visitMark = UNVISITED;
					PAMLGraphArc tempTemp = ret.vexs[sortedArr[n].i].firstEdge;
					if (tempTemp == NULL)
					{
						ret.vexs[sortedArr[n].i].firstEdge = temp;
					}
					else
					{
						char isI = 0;
						while (1)
						{
							if (tempTemp->iVex == sortedArr[n].i)
							{
								if (tempTemp->iLink == NULL)
								{
									isI = 1;
									break;
								}
								tempTemp = tempTemp->iLink;
							}
							else if (tempTemp->jVex == sortedArr[n].i)
							{
								if (tempTemp->jLink == NULL)
								{
									isI = 0;
									break;
								}
								tempTemp = tempTemp->jLink;
							}
						}
						if (isI == 1)
						{
							tempTemp->iLink = temp;
						}
						else
						{
							tempTemp->jLink = temp;
						}
					}
					// 另一个顶点连接边
					tempTemp = ret.vexs[sortedArr[n].j].firstEdge;
					if (tempTemp == NULL)
					{
						ret.vexs[sortedArr[n].j].firstEdge = temp;
					}
					else
					{
						char isI = 0;
						while (1)
						{
							if (tempTemp->iVex == sortedArr[n].j)
							{
								if (tempTemp->iLink == NULL)
								{
									isI = 1;
									break;
								}
								tempTemp = tempTemp->iLink;
							}
							else if (tempTemp->jVex == sortedArr[n].j)
							{
								if (tempTemp->jLink == NULL)
								{
									isI = 0;
									break;
								}
								tempTemp = tempTemp->jLink;
							}
						}
						if (isI == 1)
						{
							tempTemp->iLink = temp;
						}
						else
						{
							tempTemp->jLink = temp;
						}
					}
					checkArr[sortedArr[n].j].parent = checkArr[sortedArr[n].i].parent;
				}
			}
		}
		free(checkArr);
		free(sortedArr);
		return ret;
	}
	else
	{
		return;
	}
}
/*
*									求最短路径
* ① 单源最短路径: 广度优先搜索BFS(无权图), 迪杰斯特拉算法Dijkstra(无权图, 带权图)
* ② 多源最短路径: 佛洛依德Floyd(无权图, 带权图)
* Dijkstra 算法原理: 初始化:1)出发点是第一个已确定最短路径的顶点
*							2)更新与出发点有路径的顶点的最短路径和前驱顶点
*					   循环:1)从未确定最短路径的顶点中选取最短路径最小的顶点为新确定最短路径的顶点
*							2)更新与新确定的顶点有路径的顶点的最短路径和前驱顶点。（如果新路径最短就更新，新路径更长则不更新）
*/
// 邻接矩阵最小路径，支持有向图
#define  ARCTYPE int
MGraph MGraphDijkstra(PMGraph G, VERTEXTYPE origin)
{
	// 构建图
	MGraph RetMraphMain;
	PMGraph PRetMraph = &RetMraphMain;
	PRetMraph->graphKind = DN;
	PRetMraph->arcNum = G->vexNum - 1;
	PRetMraph->vexNum = G->vexNum;
	PRetMraph->vexs = (VERTEXTYPE*)malloc(G->vexNum * sizeof(VERTEXTYPE));
	PRetMraph->arcs = (PMGraphArc*)malloc(G->vexNum * sizeof(PMGraphArc));
	if (PRetMraph->vexs == NULL || PRetMraph->arcs == NULL)
	{
		printf("malloc failed!\n");
		return;
	}
	for (int n = 0; n < G->vexNum; ++n)
	{
		PRetMraph->vexs[n] = G->vexs[n];
		PRetMraph->arcs[n] = (PMGraphArc)malloc(G->vexNum * sizeof(MGraphArc));
		if (PRetMraph->arcs[n] == NULL)
		{
			printf("malloc failed!\n");
		}
		for (int m = 0; m < G->vexNum; ++m)
		{
			PRetMraph->arcs[n][m].adj = 0;
			PRetMraph->arcs[n][m].arcInfo = NULL;
		}
	}
	// 已确定最短路径的顶点
	char* bInFinal = (char*)malloc(G->vexNum * sizeof(char));
	// 最短路径
	ARCTYPE* dist = (ARCTYPE*)malloc(G->vexNum * sizeof(ARCTYPE));
	// 前驱顶点(索引)
	int* preVex = (int*)malloc(G->vexNum * sizeof(int));
	if (bInFinal == NULL || dist == NULL || preVex == NULL)
	{
		printf("malloc failed!\n");
	}
	// 对以上三个数组初始化
	for (int i = 0; i < G->vexNum; ++i)
	{
		bInFinal[i] = 0;
		dist[i] = -1; // 以 -1 代表无穷大
		preVex[i] = -1; // -1 代表无前驱顶点
	}
	int originIndex = MGraphLocateVex(G, origin);
	bInFinal[originIndex] = 1;
	dist[originIndex] = 0; // 源到自身的最短路径为 0
	preVex[originIndex] = -1; // 源无前驱顶点
	for (int i = 0; i < G->vexNum; ++i)
	{
		ARCTYPE tempDist = G->arcs[originIndex][i].adj;
		if (tempDist != 0)
		{
			dist[i] = tempDist;
			preVex[i] = originIndex;
		}
	}
	// 正式进入循环:
	for (int i = 0; i < G->vexNum; ++i)
	{
		ARCTYPE tempMinArc = -1;
		int minArcIndex = -1;
		for (int n = 0; n < G->vexNum; ++n)
		{
			ARCTYPE tempDist = dist[n];
			if (bInFinal[n] == 0 && tempDist != -1 && ((tempMinArc == -1 && tempDist > 0) || tempDist < tempMinArc))
			{
				tempMinArc = tempDist;
				minArcIndex = n;
			}
		}
		if (minArcIndex != -1)
		{
			bInFinal[minArcIndex] = 1;
			//PRetMraph->arcs[minArcIndex][preVex[minArcIndex]].adj = dist[minArcIndex];
			PRetMraph->arcs[preVex[minArcIndex]][minArcIndex].adj = dist[minArcIndex];
			// 其他顶点的dist, preVex 是否需要更新，还需要溯源
			for (int m = 0; m < G->vexNum; ++m)
			{
				if (bInFinal[m] == 0 && G->arcs[minArcIndex][m].adj != 0)
				{
					ARCTYPE sumArc = G->arcs[minArcIndex][m].adj;
					int tempPreVexIndex = preVex[minArcIndex];
					int tempPreAhead = minArcIndex;
					while (tempPreVexIndex != -1)
					{
						sumArc += G->arcs[tempPreVexIndex][tempPreAhead].adj;
						tempPreAhead = tempPreVexIndex;
						tempPreVexIndex = preVex[tempPreVexIndex];
					}
					if ((dist[m] != -1 && sumArc < dist[m]) || dist[m] == -1)
					{
						dist[m] = sumArc;
						preVex[m] = minArcIndex;
					}
				}
			}
		}
		else
		{
			break;
		}
	}

	free(bInFinal);
	free(dist);
	free(preVex);
	return RetMraphMain;
}
// 邻接表最短路径，支持有向图(箭头的前值为前驱顶点，中值为origin到后值顶点的距离)
ALGraph ALGraphDijkstra(PALGraph G, VERTEXTYPE origin)
{
	ALGraph ret;
	PALGraph PRet = &ret;
	ret.arcNum = G->vertexNum - 1;
	ret.graphKind = DN;
	ret.vertexNum = G->vertexNum;
	ret.vertices = (PALGraphVex)malloc(G->vertexNum * sizeof(ALGraphVex));
	if (ret.vertices == NULL)
	{
		printf("malloc failed!\n");
	}
	for (int n = 0; n < G->vertexNum; ++n)
	{
		ret.vertices[n].data = G->vertices[n].data;
		ret.vertices[n].pFirstArc = NULL;
	}
	// 已确定最短路径的顶点
	char* bInFinal = (char*)malloc(G->vertexNum * sizeof(char));
	// 最短路径
	ARCTYPE* dist = (ARCTYPE*)malloc(G->vertexNum * sizeof(ARCTYPE));
	// 前驱顶点(索引)
	int* preVex = (int*)malloc(G->vertexNum * sizeof(int));
	if (bInFinal == NULL || dist == NULL || preVex == NULL)
	{
		printf("malloc failed!\n");
	}
	// 对以上三个数组初始化
	for (int i = 0; i < G->vertexNum; ++i)
	{
		bInFinal[i] = 0;
		dist[i] = -1; // 以 -1 代表无穷大
		preVex[i] = -1; // -1 代表无前驱顶点
	}
	int originIndex = ALGraphLocateVex(G, origin);
	bInFinal[originIndex] = 1;
	dist[originIndex] = 0; // 源到自身的最短路径为 0
	preVex[originIndex] = -1; // 源无前驱顶点
	PALGraphArc temp = G->vertices[originIndex].pFirstArc;
	while (temp != NULL)
	{
		dist[temp->adjvexIndex] = temp->adj;
		preVex[temp->adjvexIndex] = originIndex;
		temp = temp->pNext;
	}
	// 正式进入循环
	while (1)
	{
		ARCTYPE tempMinArc = -1;
		int minArcIndex = -1;
		for (int n = 0; n < G->vertexNum; ++n)
		{
			ARCTYPE tempDist = dist[n];
			if (bInFinal[n] == 0 && tempDist != -1 && ((tempMinArc == -1 && tempDist > 0) || tempDist < tempMinArc))
			{
				tempMinArc = tempDist;
				minArcIndex = n;
			}
		}
		if (minArcIndex != -1)
		{
			bInFinal[minArcIndex] = 1;
			PALGraphArc temp = PRet->vertices[preVex[minArcIndex]].pFirstArc;
			if (temp == NULL)
			{
				PALGraphArc tempNew = (ALGraphArc*)malloc(1 * sizeof(ALGraphArc));
				if (tempNew == NULL)
				{
					printf("malloc failed!\n");
				}
				tempNew->adj = dist[minArcIndex];
				tempNew->adjvexIndex = minArcIndex;
				tempNew->arcInfo = NULL;
				tempNew->pNext = NULL;
				PRet->vertices[preVex[minArcIndex]].pFirstArc = tempNew;
			}
			else
			{
				while (temp->pNext != NULL)
				{
					temp = temp->pNext;
				}
				PALGraphArc tempNew = (ALGraphArc*)malloc(1 * sizeof(ALGraphArc));
				if (tempNew == NULL)
				{
					printf("malloc failed!\n");
				}
				tempNew->adj = dist[minArcIndex];
				tempNew->adjvexIndex = minArcIndex;
				tempNew->arcInfo = NULL;
				tempNew->pNext = NULL;
				temp->pNext = tempNew;
			}
			// 其他顶点的dist, preVex 是否需要更新，还需要溯源
			temp = G->vertices[minArcIndex].pFirstArc;
			while (temp != NULL)
			{
				if (bInFinal[temp->adjvexIndex] == 0)
				{
					ARCTYPE sumArc = temp->adj;
					int tempPreVexIndex = preVex[minArcIndex];
					int tempPreAhead = minArcIndex;
					while (tempPreVexIndex != -1)
					{
						PALGraphArc tempFind = G->vertices[tempPreVexIndex].pFirstArc;
						if (tempFind != NULL)
						{
							while (tempFind != NULL && tempFind->adjvexIndex != tempPreAhead)
							{
								tempFind = tempFind->pNext;
							}
							if (tempFind != NULL && tempFind->adjvexIndex == tempPreAhead)
							{
								sumArc += tempFind->adj;
								tempPreAhead = tempPreVexIndex;
								tempPreVexIndex = preVex[tempPreVexIndex];
							}
						}
					}
					int tempIndex = temp->adjvexIndex;
					if ((dist[tempIndex] != -1 && sumArc < dist[tempIndex]) || dist[tempIndex] == -1)
					{
						dist[tempIndex] = sumArc;
						preVex[tempIndex] = minArcIndex;
					}
				}
				temp = temp->pNext;
			}
		}
		else
		{
			break;
		}
	}
	free(bInFinal);
	free(dist);
	free(preVex);
	return ret;
}
// 暂不提供有向图的最短路径
/*
OLGraph OLGraphDijkstra(POLGraph G, VERTEXTYPE origin)
{
}*/
AMLGraph AMLGraphDijkstra(PAMLGraph G, VERTEXTYPE origin)
{
	AMLGraph ret;
	PAMLGraph PRet = &ret;
	ret.edgeNum = G->vexNum - 1;
	ret.vexNum = G->vexNum;
	ret.graphKind = G->graphKind;
	ret.vexs = (PAMLGraphVex)malloc(G->vexNum * sizeof(AMLGraphVex));
	if (ret.vexs == NULL)
	{
		printf("malloc failed!\n");
	}
	for (int n = 0; n < G->vexNum; ++n)
	{
		ret.vexs[n].data = G->vexs[n].data;
		ret.vexs[n].firstEdge = NULL;
	}
	// 已确定最短路径的顶点
	char* bInFinal = (char*)malloc(G->vexNum * sizeof(char));
	// 最短路径
	ARCTYPE* dist = (ARCTYPE*)malloc(G->vexNum * sizeof(ARCTYPE));
	// 前驱顶点(索引)
	int* preVex = (int*)malloc(G->vexNum * sizeof(int));
	if (bInFinal == NULL || dist == NULL || preVex == NULL)
	{
		printf("malloc failed!\n");
	}
	// 对以上三个数组初始化
	for (int i = 0; i < G->vexNum; ++i)
	{
		bInFinal[i] = 0;
		dist[i] = -1; // 以 -1 代表无穷大
		preVex[i] = -1; // -1 代表无前驱顶点
	}
	int originIndex = AMLGraphLocateVex(G, origin);
	bInFinal[originIndex] = 1;
	dist[originIndex] = 0; // 源到自身的最短路径为 0
	preVex[originIndex] = -1; // 源无前驱顶点
	PAMLGraphArc temp = G->vexs[originIndex].firstEdge;
	while (temp != NULL)
	{
		if (temp->iVex == originIndex)
		{
			dist[temp->jVex] = temp->edgeLength;
			preVex[temp->jVex] = originIndex;
			temp = temp->iLink;
		}
		else if (temp->jVex == originIndex)
		{
			dist[temp->iVex] = temp->edgeLength;
			preVex[temp->iVex] = originIndex;
			temp = temp->jLink;
		}
	}
	// 进入循环
	while (1)
	{
		ARCTYPE tempMinArc = -1;
		int minArcIndex = -1;
		for (int n = 0; n < G->vexNum; ++n)
		{
			ARCTYPE tempDist = dist[n];
			if (bInFinal[n] == 0 && tempDist != -1 && ((tempMinArc == -1 && tempDist > 0) || tempDist < tempMinArc))
			{
				tempMinArc = tempDist;
				minArcIndex = n;
			}
		}
		if (minArcIndex != -1)
		{
			bInFinal[minArcIndex] = 1;
			PAMLGraphArc tempNew = (PAMLGraphArc)malloc(1 * sizeof(AMLGraphArc));
			if (tempNew == NULL)
			{
				printf("malloc failed!\n");
			}
			tempNew->edgeLength = dist[minArcIndex];
			tempNew->iVex = minArcIndex;
			tempNew->jVex = preVex[minArcIndex];
			tempNew->iLink = NULL;
			tempNew->jLink = NULL;
			tempNew->info = NULL;
			tempNew->visitMark = UNVISITED;
			PAMLGraphArc temp = PRet->vexs[minArcIndex].firstEdge;
			// 新弧入图
			while (1)
			{
				if (temp != NULL)
				{
					if (temp->iVex == minArcIndex && temp->iLink != NULL)
					{
						temp = temp->iLink;
					}
					else if (temp->jVex == minArcIndex && temp->jLink != NULL)
					{
						temp = temp->jLink;
					}
					else if (temp->iVex == minArcIndex && temp->iLink == NULL)
					{
						temp->iLink = tempNew;
						break;
					}
					else if (temp->jVex == minArcIndex && temp->jLink == NULL)
					{
						temp->jLink = tempNew;
						break;
					}
				}
				else
				{
					PRet->vexs[minArcIndex].firstEdge = tempNew;
					break;
				}
			}
			temp = PRet->vexs[preVex[minArcIndex]].firstEdge;
			while (1)
			{
				if (temp != NULL)
				{
					if (temp->iVex == preVex[minArcIndex] && temp->iLink != NULL)
					{
						temp = temp->iLink;
					}
					else if (temp->jVex == preVex[minArcIndex] && temp->jLink != NULL)
					{
						temp = temp->jLink;
					}
					else if (temp->iVex == preVex[minArcIndex] && temp->iLink == NULL)
					{
						temp->iLink = tempNew;
						break;
					}
					else if (temp->jVex == preVex[minArcIndex] && temp->jLink == NULL)
					{
						temp->jLink = tempNew;
						break;
					}
				}
				else
				{
					PRet->vexs[preVex[minArcIndex]].firstEdge = tempNew;
					break;
				}
			}
			// 其他顶点的dist, preVex 是否需要更新，还需要溯源
			temp = G->vexs[minArcIndex].firstEdge;
			if (temp != NULL)
			{
				while (1)
				{
					if (temp == NULL)
					{
						break;
					}
					if (temp->iVex == minArcIndex)
					{
						if (bInFinal[temp->jVex] == 0)
						{
							ARCTYPE sumArc = temp->edgeLength;
							int tempPreVexIndex = preVex[minArcIndex];
							int tempPreAhead = minArcIndex;
							while (tempPreVexIndex != -1)
							{
								PAMLGraphArc tempFind = G->vexs[tempPreVexIndex].firstEdge;
								while (tempFind != NULL)
								{
									if ((tempFind->iVex == tempPreVexIndex && tempFind->jVex == tempPreAhead) || (tempFind->jVex == tempPreVexIndex && tempFind->iVex == tempPreAhead))
									{
										sumArc += tempFind->edgeLength;
										tempPreAhead = tempPreVexIndex;
										tempPreVexIndex = preVex[tempPreVexIndex];
										break;
									}
									if (tempFind->iVex == tempPreVexIndex)
									{
										tempFind = tempFind->iLink;
									}
									else if (tempFind->jVex == tempPreVexIndex)
									{
										tempFind = tempFind->jLink;
									}
								}
							}
							int tempIndex = temp->jVex;
							if ((dist[tempIndex] != -1 && sumArc < dist[tempIndex]) || dist[tempIndex] == -1)
							{
								dist[tempIndex] = sumArc;
								preVex[tempIndex] = minArcIndex;
							}
						}
						temp = temp->iLink;
					}
					else if (temp->jVex == minArcIndex)
					{
						if (bInFinal[temp->iVex] == 0)
						{
							ARCTYPE sumArc = temp->edgeLength;
							int tempPreVexIndex = preVex[minArcIndex];
							int tempPreAhead = minArcIndex;
							while (tempPreVexIndex != -1)
							{
								PAMLGraphArc tempFind = G->vexs[tempPreVexIndex].firstEdge;
								while (tempFind != NULL)
								{
									if ((tempFind->jVex == tempPreVexIndex && tempFind->iVex == tempPreAhead) || (tempFind->iVex == tempPreVexIndex && tempFind->jVex == tempPreAhead))
									{
										sumArc += tempFind->edgeLength;
										tempPreAhead = tempPreVexIndex;
										tempPreVexIndex = preVex[tempPreVexIndex];
										break;
									}
									if (tempFind->iVex == tempPreVexIndex)
									{
										tempFind = tempFind->iLink;
									}
									else if (tempFind->jVex == tempPreVexIndex)
									{
										tempFind = tempFind->jLink;
									}
								}
							}
							int tempIndex = temp->iVex;
							if ((dist[tempIndex] != -1 && sumArc < dist[tempIndex]) || dist[tempIndex] == -1)
							{
								dist[tempIndex] = sumArc;
								preVex[tempIndex] = minArcIndex;
							}
						}
						temp = temp->jLink;
					}
				}
			}
		}
		else
		{
			break;
		}
	}

	free(bInFinal);
	free(dist);
	free(preVex);
	return ret;
}

/*
*							拓扑排序
* AOV网(Activity on vertex network, 用顶点表示活动的图): 用顶点表示活动，用有向边(弧)表示活动时间先后关系的有向无环图(DAG)
* 拓扑排序的实现:1)从图中选择一个没有前驱的顶点并输出
*				 2)从图中删除该顶点和全部以它为起点的有向边
*				 3)重复步骤1)2)直至图为空
*/
#define  ARCTYPE int
VERTEXTYPE* MGraphTopologicalSorting(PMGraph G)
{
	if (G->graphKind == DG || G->graphKind == DN)
	{
		VERTEXTYPE* ret = malloc(G->vexNum * sizeof(VERTEXTYPE));
		int retIndex = 0;
		// 图复制
		MGraph TopoGraph;
		TopoGraph.arcNum = G->arcNum;
		TopoGraph.graphKind = G->graphKind;
		TopoGraph.vexNum = G->vexNum;
		TopoGraph.vexs = (VERTEXTYPE*)malloc(G->vexNum * sizeof(VERTEXTYPE));
		TopoGraph.arcs = (PMGraphArc*)malloc(G->vexNum * sizeof(PMGraphArc));
		if (ret == NULL || TopoGraph.vexs == NULL || TopoGraph.arcs == NULL)
		{
			printf("malloc failed!\n");
		}
		for (int n = 0; n < G->vexNum; ++n)
		{
			TopoGraph.vexs[n] = 0; // 0 代表未进排序序列, 1代表已进
			TopoGraph.arcs[n] = (PMGraphArc)malloc(G->vexNum * sizeof(MGraphArc));
			if (TopoGraph.arcs[n] == NULL)
			{
				printf("malloc failed!\n");
			}
			for (int m = 0; m < G->vexNum; ++m)
			{
				TopoGraph.arcs[n][m].adj = G->arcs[n][m].adj;
				TopoGraph.arcs[n][m].arcInfo = NULL;
			}
		}
		// 寻找入度为0的顶点
		for (int i = 0; i < G->vexNum; ++i)
		{
			int noIndegreeVexIndex = -1;
			for (int n = 0; n < G->vexNum; ++n)
			{
				char noInDegree = 1;
				if (TopoGraph.vexs[n] == 0)
				{
					for (int m = 0; m < G->vexNum; ++m)
					{
						if (TopoGraph.arcs[m][n].adj != 0)
						{
							noInDegree = 0;
						}
					}
					if (noInDegree == 1)
					{
						TopoGraph.vexs[n] = 1;
						noIndegreeVexIndex = n;
						break;
					}
				}
			}
			if (noIndegreeVexIndex != -1)
			{
				ret[retIndex++] = G->vexs[noIndegreeVexIndex];
				for (int k = 0; k < G->vexNum; ++k)
				{
					TopoGraph.arcs[noIndegreeVexIndex][k].adj = 0;
				}
			}
			else
			{
				MGraphDestroy(&TopoGraph);
				free(ret);
				printf("该有向图含环，不可进行拓扑排序\n");
				return NULL;
			}
		}
		MGraphDestroy(&TopoGraph);
		return ret;
	}
	else
	{
		return NULL;
	}
}
// 邻接矩阵逆拓扑排序
VERTEXTYPE* MGraphTopologicalSortingInverse(PMGraph G)
{
	if (G->graphKind == DG || G->graphKind == DN)
	{
		VERTEXTYPE* ret = malloc(G->vexNum * sizeof(VERTEXTYPE));
		int retIndex = 0;
		// 图复制
		MGraph TopoGraph;
		TopoGraph = MGraphReverse(G);
		for (int n = 0; n < G->vexNum; ++n)
		{
			TopoGraph.vexs[n] = 0; // 0 代表未进排序序列, 1代表已进
		}
		// 寻找入度为0的顶点
		for (int i = 0; i < G->vexNum; ++i)
		{
			int noIndegreeVexIndex = -1;
			for (int n = 0; n < G->vexNum; ++n)
			{
				char noInDegree = 1;
				if (TopoGraph.vexs[n] == 0)
				{
					for (int m = 0; m < G->vexNum; ++m)
					{
						if (TopoGraph.arcs[m][n].adj != 0)
						{
							noInDegree = 0;
						}
					}
					if (noInDegree == 1)
					{
						TopoGraph.vexs[n] = 1;
						noIndegreeVexIndex = n;
						break;
					}
				}
			}
			if (noIndegreeVexIndex != -1)
			{
				ret[retIndex++] = G->vexs[noIndegreeVexIndex];
				for (int k = 0; k < G->vexNum; ++k)
				{
					TopoGraph.arcs[noIndegreeVexIndex][k].adj = 0;
				}
			}
			else
			{
				MGraphDestroy(&TopoGraph);
				free(ret);
				printf("该有向图含环，不可进行拓扑排序\n");
				return NULL;
			}
		}
		MGraphDestroy(&TopoGraph);
		return ret;
	}
	else
	{
		return NULL;
	}
}
// 邻接表图拓扑排序(程序开支很大)
VERTEXTYPE* ALGraphTopologicalSorting(PALGraph G)
{
	if (G->graphKind == DN || G->graphKind == DG)
	{
		VERTEXTYPE* ret = malloc(G->vertexNum * sizeof(VERTEXTYPE));
		int retIndex = 0;
		ALGraph reverseGraph = ALGraphDGraphReverse(G);
		for (int i = 0; i < G->vertexNum; ++i)
		{
			reverseGraph.vertices[i].data = 0; // 0 代表未入列, 1代表已入列
		}
		// 寻找入度为0的点
		while (1)
		{
			int noIndegreeVexIndex = -1;
			for (int n = 0; n < G->vertexNum; ++n)
			{
				if (reverseGraph.vertices[n].data == 0 && reverseGraph.vertices[n].pFirstArc == NULL)
				{
					noIndegreeVexIndex = n;
					break;
				}
			}
			if (noIndegreeVexIndex != -1)
			{
				ret[retIndex++] = G->vertices[noIndegreeVexIndex].data;
				reverseGraph.vertices[noIndegreeVexIndex].data = 1;
				for (int m = 0; m < G->vertexNum; ++m)
				{
					PALGraphArc temp = reverseGraph.vertices[m].pFirstArc;
					// 鉴于不出现同一个顶点与顶点间存在两条同向的边
					if (temp != NULL)
					{
						if (temp->adjvexIndex == noIndegreeVexIndex)
						{
							reverseGraph.vertices[m].pFirstArc = temp->pNext;
							free(temp);
						}
						else
						{
							while (temp->pNext != NULL && temp->pNext->adjvexIndex != noIndegreeVexIndex)
							{
								temp = temp->pNext;
							}
							if (temp->pNext != NULL && temp->pNext->adjvexIndex == noIndegreeVexIndex)
							{
								PALGraphArc del = temp->pNext;
								temp->pNext = temp->pNext->pNext;
								free(del);
							}
						}
					}
				}
			}
			else
			{
				if (retIndex != G->vertexNum)
				{
					ALGraphDestroy(&reverseGraph);
					free(ret);
					printf("该有向图含环，不可进行拓扑排序\n");
					return NULL;
				}
				break;
			}
		}
		ALGraphDestroy(&reverseGraph);
		return ret;
	}
	else
	{
		return NULL;
	}
}
// 邻接表逆拓扑排序
VERTEXTYPE* ALGraphTopologicalSortingInverse(PALGraph G)
{
	if (G->graphKind == DN || G->graphKind == DG)
	{
		VERTEXTYPE* ret = malloc(G->vertexNum * sizeof(VERTEXTYPE));
		int retIndex = 0;
		ALGraph copyGraph = ALGraphCopy(G);
		for (int i = 0; i < G->vertexNum; ++i)
		{
			copyGraph.vertices[i].data = 0; // 0 代表未入列, 1代表已入列
		}
		// 寻找入度为0的点
		while (1)
		{
			int noIndegreeVexIndex = -1;
			for (int n = 0; n < G->vertexNum; ++n)
			{
				if (copyGraph.vertices[n].data == 0 && copyGraph.vertices[n].pFirstArc == NULL)
				{
					noIndegreeVexIndex = n;
					break;
				}
			}
			if (noIndegreeVexIndex != -1)
			{
				ret[retIndex++] = G->vertices[noIndegreeVexIndex].data;
				copyGraph.vertices[noIndegreeVexIndex].data = 1;
				for (int m = 0; m < G->vertexNum; ++m)
				{
					PALGraphArc temp = copyGraph.vertices[m].pFirstArc;
					// 鉴于不出现同一个顶点与顶点间存在两条同向的边
					if (temp != NULL)
					{
						if (temp->adjvexIndex == noIndegreeVexIndex)
						{
							copyGraph.vertices[m].pFirstArc = temp->pNext;
							free(temp);
						}
						else
						{
							while (temp->pNext != NULL && temp->pNext->adjvexIndex != noIndegreeVexIndex)
							{
								temp = temp->pNext;
							}
							if (temp->pNext != NULL && temp->pNext->adjvexIndex == noIndegreeVexIndex)
							{
								PALGraphArc del = temp->pNext;
								temp->pNext = temp->pNext->pNext;
								free(del);
							}
						}
					}
				}
			}
			else
			{
				if (retIndex != G->vertexNum)
				{
					ALGraphDestroy(&copyGraph);
					free(ret);
					printf("该有向图含环，不可进行拓扑排序\n");
					return NULL;
				}
				break;
			}
		}
		ALGraphDestroy(&copyGraph);
		return ret;
	}
	else
	{
		return NULL;
	}
}
// 十字链表拓扑排序
VERTEXTYPE* OLGraphTopologicalSorting(POLGraph G)
{
	VERTEXTYPE* ret = malloc(G->vexNum * sizeof(VERTEXTYPE));
	if (ret == NULL)
	{
		printf("malloc failed!");
	}
	int retIndex = 0;
	OLGraph assistGraph = OLGraphCopy(G);
	for (int i = 0; i < G->vexNum; ++i)
	{
		assistGraph.vList[i].data = 0; // 0 表示未入列, 1表示已入列
	}
	// 寻找入度为 0 的顶点
	while (1)
	{
		int noIndegreeVexIndex = -1;
		for (int n = 0; n < G->vexNum; ++n)
		{
			if (assistGraph.vList[n].data == 0 && assistGraph.vList[n].firstIn == NULL)
			{
				noIndegreeVexIndex = n;
				assistGraph.vList[n].data = 1;
				break;
			}
		}
		if (noIndegreeVexIndex != -1)
		{
			ret[retIndex++] = G->vList[noIndegreeVexIndex].data;
			// 只需删除firstIn方向的边(实际为改变指针指向)
			POLGraphArc temp = G->vList[noIndegreeVexIndex].firstOut;
			while (temp != NULL)
			{
				int index = temp->tailVexIndex;
				POLGraphArc tTemp = assistGraph.vList[index].firstIn;
				if (tTemp->tailVexIndex == index)
				{
					assistGraph.vList[index].firstIn = tTemp->pTail;
				}
				while (tTemp->pTail != NULL && tTemp->pTail->tailVexIndex != index)
				{
					tTemp = tTemp->pTail;
				}
				if (tTemp->pTail != NULL)
				{
					tTemp->pTail = tTemp->pTail->pTail;
				}
				temp = temp->pHead;
			}
		}
		else
		{
			if (retIndex != G->vexNum)
			{
				OLGraphDestroy(&assistGraph);
				free(ret);
				printf("该有向图含环，不可进行拓扑排序\n");
				return NULL;
			}
			break;
		}
	}
	OLGraphDestroy(&assistGraph);
	return ret;
}
// 十字链表逆拓扑排序
VERTEXTYPE* OLGraphTopologicalSortingInverse(POLGraph G)
{
	OLGraph assistg = OLGraphReverse(G);
	POLGraph assistG = &assistg;
	VERTEXTYPE* ret = malloc(G->vexNum * sizeof(VERTEXTYPE));
	if (ret == NULL)
	{
		printf("malloc failed!");
	}
	int retIndex = 0;
	OLGraph assistGraph = OLGraphReverse(G);
	for (int i = 0; i < G->vexNum; ++i)
	{
		assistGraph.vList[i].data = 0; // 0 表示未入列, 1表示已入列
	}
	// 寻找入度为 0 的顶点
	while (1)
	{
		int noIndegreeVexIndex = -1;
		for (int n = 0; n < G->vexNum; ++n)
		{
			if (assistGraph.vList[n].data == 0 && assistGraph.vList[n].firstIn == NULL)
			{
				noIndegreeVexIndex = n;
				assistGraph.vList[n].data = 1;
				break;
			}
		}
		if (noIndegreeVexIndex != -1)
		{
			ret[retIndex++] = assistG->vList[noIndegreeVexIndex].data;
			// 只需删除firstIn方向的边(实际为改变指针指向)
			POLGraphArc temp = assistG->vList[noIndegreeVexIndex].firstOut;
			while (temp != NULL)
			{
				int index = temp->tailVexIndex;
				POLGraphArc tTemp = assistGraph.vList[index].firstIn;
				if (tTemp->tailVexIndex == index)
				{
					assistGraph.vList[index].firstIn = tTemp->pTail;
				}
				while (tTemp->pTail != NULL && tTemp->pTail->tailVexIndex != index)
				{
					tTemp = tTemp->pTail;
				}
				if (tTemp->pTail != NULL)
				{
					tTemp->pTail = tTemp->pTail->pTail;
				}
				temp = temp->pHead;
			}
		}
		else
		{
			if (retIndex != G->vexNum)
			{
				OLGraphDestroy(&assistGraph);
				OLGraphDestroy(assistG);
				free(ret);
				printf("该有向图含环，不可进行拓扑排序\n");
				return NULL;
			}
			break;
		}
	}
	OLGraphDestroy(assistG);
	OLGraphDestroy(&assistGraph);
	return ret;
}
/*
*						  关键路径
* 工程中最长的路径叫做关键路径，关键路径上的活动叫做关键活动
* AOE(Activity on edge network, 用边表示活动的网) 网: 用顶点表示事件的发生,
* 用有向边(弧)上的权值表示完成该活动的开销(如完成活动需要的时间)的有向无环图
* AOE 网有以下特点:
* 1)图中只有一个入度为0的顶点，称为开始顶点(源点)，表示整个工程的开始.
* 2)图中只有一个出度为0的顶点，称为结束顶点(汇点)，表示整个工程的结束.
* 3)只有在某顶点所代表的事件发生后，从该顶点出发的各有向边所代表的活动才能开始.
* 4)只有在指向某顶点的各有向边所代表的活动全部都结束后，该顶点所代表的事件才能发生.
* 5)在AOE网中，有些活动可以并行地进行.
*/
// 邻接矩阵关键路径
MGraph MGraphCriticalPath(PMGraph G)
{
	// 先判断是否符合AOE网条件
	char noIndegreeVexIndex = -1;
	char noIndegree = 1;
	char noOutdegreeVexIndex = -1;
	char noOutDegree = 1;
	for (int i = 0; i < G->vexNum; ++i)
	{
		for (int n = 0; n < G->vexNum; ++n)
		{
			if (G->arcs[n][i].adj != 0)
			{
				noIndegree = 0;
			}
			if (G->arcs[i][n].adj != 0)
			{
				noOutDegree = 0;
			}
		}
		if (noIndegree == 1)
		{
			// 不为-1代表已有入度为0的顶点
			if (noIndegreeVexIndex != -1)
			{
				printf("不满足AOE网条件");
				return;
			}
			noIndegreeVexIndex = i;
		}
		if (noOutDegree == 1)
		{
			if (noOutdegreeVexIndex != -1)
			{
				printf("不满足AOE网条件");
				return;
			}
			noOutdegreeVexIndex = i;
		}
		noIndegree = 1;
		noOutDegree = 1;
	}
	// 以下三个数组顶点位置 一一对应
	VERTEXTYPE* topoArr = MGraphTopologicalSorting(G);
	// 事件最早发生时间
	ARCTYPE* earliestTimeOfOccurrence = (ARCTYPE*)malloc(G->vexNum * sizeof(ARCTYPE));
	int earliestIndex = MGraphLocateVex(G, topoArr[0]);
	// 事件最迟发生时间
	ARCTYPE* latestTimeOfOccurrence = (ARCTYPE*)malloc(G->vexNum * sizeof(ARCTYPE));
	int latestIndex = earliestIndex;
	// 初始化
	for (int m = 0; m < G->vexNum; ++m)
	{
		earliestTimeOfOccurrence[m] = -1;
		latestTimeOfOccurrence[m] = -1;
	}
	earliestTimeOfOccurrence[earliestIndex] = 0;
	latestTimeOfOccurrence[latestIndex] = 0;
	for (int i = 1; i < G->vexNum; ++i)
	{
		earliestIndex = MGraphLocateVex(G, topoArr[i]);
		ARCTYPE arcTime = -1;
		for (int n = 0; n < G->vexNum; ++n)
		{
			// 寻找入度
			ARCTYPE temp = G->arcs[n][earliestIndex].adj;
			if (temp != 0)
			{
				if (earliestTimeOfOccurrence[n] != -1)
				{
					if (arcTime < temp + earliestTimeOfOccurrence[n])
					{
						arcTime = temp + earliestTimeOfOccurrence[n];
					}
				}
				else
				{
					if (arcTime < temp)
					{
						arcTime = temp;
					}
				}
			}
		}
		earliestTimeOfOccurrence[earliestIndex] = arcTime;
	}
	free(topoArr);
	topoArr = MGraphTopologicalSortingInverse(G);
	// latestTimeOfOccurrence数组的第一个元素与最后一个元素的值均已确定
	latestTimeOfOccurrence[G->vexNum - 1] = earliestTimeOfOccurrence[G->vexNum - 1];
	for (int i = 1; i < G->vexNum - 1; ++i)
	{
		latestIndex = MGraphLocateVex(G, topoArr[i]);
		ARCTYPE arcTime = -1;
		for (int n = 0; n < G->vexNum; ++n)
		{
			// 寻找出度
			ARCTYPE temp = G->arcs[latestIndex][n].adj;
			if (temp != 0)
			{
				if (latestTimeOfOccurrence[n] != -1)
				{
					if (arcTime != -1)
					{
						if (arcTime > latestTimeOfOccurrence[n] - temp)
						{
							arcTime = latestTimeOfOccurrence[n] - temp;
						}
					}
					else
					{
						arcTime = latestTimeOfOccurrence[n] - temp;
					}
				}
				else
				{
					if (arcTime != -1)
					{
						if (arcTime > temp)
						{
							arcTime = temp;
						}
					}
					else
					{
						arcTime = temp;
					}
				}
			}
		}
		latestTimeOfOccurrence[latestIndex] = arcTime;
	}
	MGraph ret = MGraphCopy(G);
	// 记录活动最早开始时间(earliestTimeOfOccurrence[n])、活动最晚开始时间(latestTimeOfOccurrence[m] - G->arcs[n][m].adj)
	// 两者相等则该边在包含于关键路径中
	int tempIndex = 0;
	for (int n = 0; n < G->vexNum; ++n)
	{
		for (int m = 0; m < G->vexNum; ++m)
		{
			if (G->arcs[n][m].adj != 0)
			{
				if (latestTimeOfOccurrence[m] - G->arcs[n][m].adj != earliestTimeOfOccurrence[n])
				{
					ret.arcs[n][m].adj = 0;
					ret.arcNum--;
				}
			}
		}
	}
	free(topoArr);
	free(earliestTimeOfOccurrence);
	free(latestTimeOfOccurrence);
	return ret;
}
ALGraph ALGraphCriticalPath(PALGraph G)
{
	// 先判断是否符合AOE网条件
	ALGraph assistGraph = ALGraphDGraphReverse(G);
	char noIndegreeVexIndex = -1;
	char noOutdegreeVexIndex = -1;
	for (int i = 0; i < G->vertexNum; ++i)
	{
		if (G->vertices[i].pFirstArc == NULL)
		{
			if (noOutdegreeVexIndex != -1)
			{
				printf("不满足AOE网条件");
				ALGraphDestroy(&assistGraph);
				return;
			}
			noOutdegreeVexIndex = i;
		}
		if (assistGraph.vertices[i].pFirstArc == NULL)
		{
			if (noIndegreeVexIndex != -1)
			{
				printf("不满足AOE网条件");
				ALGraphDestroy(&assistGraph);
				return;
			}
			noIndegreeVexIndex = i;
		}
	}
	// 以下三个数组顶点位置 一一对应
	VERTEXTYPE* topoArr = ALGraphTopologicalSorting(G);
	// 事件最早发生时间
	ARCTYPE* earliestTimeOfOccurrence = (ARCTYPE*)malloc(G->vertexNum * sizeof(ARCTYPE));
	int earliestIndex = ALGraphLocateVex(G, topoArr[0]);
	// 事件最迟发生时间
	ARCTYPE* latestTimeOfOccurrence = (ARCTYPE*)malloc(G->vertexNum * sizeof(ARCTYPE));
	int latestIndex = earliestIndex;
	// 初始化
	for (int m = 0; m < G->vertexNum; ++m)
	{
		earliestTimeOfOccurrence[m] = -1;
		latestTimeOfOccurrence[m] = -1;
	}
	earliestTimeOfOccurrence[earliestIndex] = 0;
	latestTimeOfOccurrence[latestIndex] = 0;
	for (int i = 1; i < G->vertexNum; i++)
	{
		earliestIndex = ALGraphLocateVex(G, topoArr[i]);
		ARCTYPE arcTime = -1;
		PALGraphArc temp = assistGraph.vertices[earliestIndex].pFirstArc;
		while (temp != NULL)
		{
			if (earliestTimeOfOccurrence[temp->adjvexIndex] != -1)
			{
				if (arcTime != -1)
				{
					if (arcTime < temp->adj + earliestTimeOfOccurrence[temp->adjvexIndex])
					{
						arcTime = temp->adj + earliestTimeOfOccurrence[temp->adjvexIndex];
					}
				}
				else
				{
					arcTime = temp->adj + earliestTimeOfOccurrence[temp->adjvexIndex];
				}
			}
			else
			{
				// arcTime = -1时也执行
				if (arcTime < temp->adj)
				{
					arcTime = temp->adj;
				}
			}
			temp = temp->pNext;
		}
		earliestTimeOfOccurrence[earliestIndex] = arcTime;
	}
	free(topoArr);
	topoArr = ALGraphTopologicalSortingInverse(G);
	// latestTimeOfOccurrence数组的第一个元素与最后一个元素的值均已确定
	latestTimeOfOccurrence[G->vertexNum - 1] = earliestTimeOfOccurrence[G->vertexNum - 1];
	for (int i = 1; i < G->vertexNum - 1; ++i)
	{
		latestIndex = ALGraphLocateVex(G, topoArr[i]);
		ARCTYPE arcTime = -1;

		// 寻找出度
		PALGraphArc temp = G->vertices[latestIndex].pFirstArc;
		while (temp != NULL)
		{
			if (latestTimeOfOccurrence[temp->adjvexIndex] != -1)
			{
				if (arcTime != -1)
				{
					if (arcTime > latestTimeOfOccurrence[temp->adjvexIndex] - temp->adj)
					{
						arcTime = latestTimeOfOccurrence[temp->adjvexIndex] - temp->adj;
					}
				}
				else
				{
					arcTime = latestTimeOfOccurrence[temp->adjvexIndex] - temp->adj;
				}
			}
			else
			{
				if (arcTime != -1)
				{
					if (arcTime > temp->adj)
					{
						arcTime = temp->adj;
					}
				}
				else
				{
					arcTime = temp->adj;
				}
			}
			temp = temp->pNext;
		}
		latestTimeOfOccurrence[latestIndex] = arcTime;
	}
	// 返回图
	ALGraph ret;
	ret.arcNum = 0;
	ret.graphKind = G->graphKind;
	ret.vertexNum = G->vertexNum;
	ret.vertices = (PALGraphVex)malloc(G->vertexNum * sizeof(ALGraphVex));
	for (int n = 0; n < G->vertexNum; ++n)
	{
		ret.vertices[n].data = G->vertices[n].data;
		ret.vertices[n].pFirstArc = NULL;
	}
	for (int k = 0; k < G->vertexNum; ++k)
	{
		PALGraphArc temp = G->vertices[k].pFirstArc;
		PALGraphArc retTemp = ret.vertices[k].pFirstArc;
		while (temp != NULL)
		{
			if (earliestTimeOfOccurrence[k] == latestTimeOfOccurrence[temp->adjvexIndex] - temp->adj)
			{
				PALGraphArc newTemp = (PALGraphArc)malloc(sizeof(ALGraphArc));
				newTemp->adj = temp->adj;
				newTemp->adjvexIndex = temp->adjvexIndex;
				newTemp->arcInfo = temp->arcInfo;
				newTemp->pNext = NULL;
				if (ret.vertices[k].pFirstArc == NULL)
				{
					ret.vertices[k].pFirstArc = newTemp;
					retTemp = ret.vertices[k].pFirstArc;
					ret.arcNum++;
				}
				else
				{
					retTemp->pNext = newTemp;
					ret.arcNum++;
					retTemp = retTemp->pNext;
				}
			}
			temp = temp->pNext;
		}
	}
	free(topoArr);
	free(earliestTimeOfOccurrence);
	free(latestTimeOfOccurrence);
	ALGraphDestroy(&assistGraph);
	return ret;
}
OLGraph OLGraphCriticalPath(POLGraph G)
{
	// 先判断是否符合AOE网条件
	char noIndegreeVexIndex = -1;
	char noOutdegreeVexIndex = -1;
	for (int i = 0; i < G->vexNum; ++i)
	{
		if (G->vList[i].firstOut == NULL)
		{
			if (noOutdegreeVexIndex != -1)
			{
				printf("不满足AOE网条件");
				return;
			}
			noOutdegreeVexIndex = i;
		}
		if (G->vList[i].firstIn == NULL)
		{
			if (noIndegreeVexIndex != -1)
			{
				printf("不满足AOE网条件");
				return;
			}
			noIndegreeVexIndex = i;
		}
	}
	// 以下三个数组顶点位置 一一对应
	VERTEXTYPE* topoArr = OLGraphTopologicalSorting(G);
	// 事件最早发生时间
	ARCTYPE* earliestTimeOfOccurrence = (ARCTYPE*)malloc(G->vexNum * sizeof(ARCTYPE));
	int earliestIndex = OLGraphLocateVex(G, topoArr[0]);
	// 事件最迟发生时间
	ARCTYPE* latestTimeOfOccurrence = (ARCTYPE*)malloc(G->vexNum * sizeof(ARCTYPE));
	int latestIndex = earliestIndex;
	// 初始化
	for (int m = 0; m < G->vexNum; ++m)
	{
		earliestTimeOfOccurrence[m] = -1;
		latestTimeOfOccurrence[m] = -1;
	}
	earliestTimeOfOccurrence[earliestIndex] = 0;
	latestTimeOfOccurrence[latestIndex] = 0;
	for (int i = 1; i < G->vexNum; i++)
	{
		earliestIndex = OLGraphLocateVex(G, topoArr[i]);
		ARCTYPE arcTime = -1;
		POLGraphArc temp = G->vList[earliestIndex].firstIn;
		while (temp != NULL)
		{
			if (earliestTimeOfOccurrence[temp->headVexIndex] != -1)
			{
				if (arcTime != -1)
				{
					if (arcTime < temp->arcLength + earliestTimeOfOccurrence[temp->headVexIndex])
					{
						arcTime = temp->arcLength + earliestTimeOfOccurrence[temp->headVexIndex];
					}
				}
				else
				{
					arcTime = temp->arcLength + earliestTimeOfOccurrence[temp->headVexIndex];
				}
			}
			else
			{
				// arcTime = -1时也执行
				if (arcTime < temp->arcLength)
				{
					arcTime = temp->arcLength;
				}
			}
			temp = temp->pTail;
		}
		earliestTimeOfOccurrence[earliestIndex] = arcTime;
	}
	free(topoArr);
	topoArr = OLGraphTopologicalSortingInverse(G);
	// latestTimeOfOccurrence数组的第一个元素与最后一个元素的值均已确定
	latestTimeOfOccurrence[G->vexNum - 1] = earliestTimeOfOccurrence[G->vexNum - 1];
	for (int i = 1; i < G->vexNum - 1; ++i)
	{
		latestIndex = OLGraphLocateVex(G, topoArr[i]);
		ARCTYPE arcTime = -1;
		POLGraphArc temp = G->vList[latestIndex].firstOut;
		while (temp != NULL)
		{
			if (latestTimeOfOccurrence[temp->tailVexIndex] != -1)
			{
				if (arcTime != -1)
				{
					if (arcTime > latestTimeOfOccurrence[temp->tailVexIndex] - temp->arcLength)
					{
						arcTime = latestTimeOfOccurrence[temp->tailVexIndex] - temp->arcLength;
					}
				}
				else
				{
					arcTime = latestTimeOfOccurrence[temp->tailVexIndex] - temp->arcLength;
				}
			}
			else
			{
				if (arcTime != -1)
				{
					if (arcTime > temp->arcLength)
					{
						arcTime = temp->arcLength;
					}
				}
				else
				{
					arcTime = temp->arcLength;
				}
			}
			temp = temp->pHead;
		}
		latestTimeOfOccurrence[latestIndex] = arcTime;
	}
	// 返回图
	OLGraph ret;
	ret.graphKind = G->graphKind;
	ret.arcNum = 0;
	ret.vexNum = G->vexNum;
	ret.vList = (POLGraphVex)malloc(G->vexNum * sizeof(OLGraphVex));
	for (int n = 0; n < G->vexNum; ++n)
	{
		ret.vList[n].data = G->vList[n].data;
		ret.vList[n].firstIn = NULL;
		ret.vList[n].firstOut = NULL;
	}
	for (int k = 0; k < G->vexNum; ++k)
	{
		POLGraphArc temp = G->vList[k].firstOut;
		POLGraphArc retTemp = ret.vList[k].firstOut;
		POLGraphArc retTempTail = NULL;
		while (temp != NULL)
		{
			if (earliestTimeOfOccurrence[k] == latestTimeOfOccurrence[temp->tailVexIndex] - temp->arcLength)
			{
				retTempTail = ret.vList[temp->tailVexIndex].firstIn;
				POLGraphArc newTemp = (POLGraphArc)malloc(sizeof(OLGraphArc));
				newTemp->arcLength = temp->arcLength;
				newTemp->headVexIndex = temp->headVexIndex;
				newTemp->tailVexIndex = temp->tailVexIndex;
				newTemp->info = temp->info;
				newTemp->pHead = NULL;
				newTemp->pTail = NULL;
				if (ret.vList[k].firstOut == NULL)
				{
					ret.vList[k].firstOut = newTemp;
					retTemp = ret.vList[k].firstOut;
					ret.arcNum++;
				}
				else
				{
					retTemp->pHead = newTemp;
					ret.arcNum++;
					retTemp = retTemp->pHead;
				}
				if (ret.vList[temp->tailVexIndex].firstIn == NULL)
				{
					ret.vList[temp->tailVexIndex].firstIn = newTemp;
				}
				else
				{
					while (retTempTail->pTail != NULL)
					{
						retTempTail = retTempTail->pTail;
					}
					retTempTail->pTail = newTemp;
				}
			}
			temp = temp->pHead;
		}
	}
	free(topoArr);
	free(earliestTimeOfOccurrence);
	free(latestTimeOfOccurrence);
	return ret;
}
int main(void)
{
	// 邻接矩阵图
	MGraph MGraphTest1;
	MGraphCreateGraph(&MGraphTest1);
	MGraphPrint(&MGraphTest1);
	printf("\n\n有向图拓扑排序\n");
	VERTEXTYPE* MGraphTest6 = MGraphTopologicalSorting(&MGraphTest1);
	if (MGraphTest6 != NULL)
	{
		for (int n = 0; n < MGraphTest1.vexNum; ++n)
		{
			printf("%d\t", MGraphTest6[n]);
		}
		free(MGraphTest6);
	}
	printf("\n\n有向图逆拓扑排序\n");
	VERTEXTYPE* MGraphTest9 = MGraphTopologicalSortingInverse(&MGraphTest1);
	if (MGraphTest9 != NULL)
	{
		for (int n = 0; n < MGraphTest1.vexNum; ++n)
		{
			printf("%d\t", MGraphTest9[n]);
		}
		free(MGraphTest9);
	}
	printf("\n\n有向图复制\n");
	MGraph MGraphTest7 = MGraphCopy(&MGraphTest1);
	MGraphPrint(&MGraphTest7);
	printf("\n\n有向图反转\n");
	MGraph MGraphTest8 = MGraphReverse(&MGraphTest1);
	MGraphPrint(&MGraphTest8);
	printf("\n\n有向图关键路径\n");
	MGraph MGraphTest10 = MGraphCriticalPath(&MGraphTest1);
	MGraphPrint(&MGraphTest10);
	MGraphDestroy(&MGraphTest10);
	MGraphDestroy(&MGraphTest7);
	MGraphDestroy(&MGraphTest8);
	VERTEXTYPE* MGraphTest2 = MGraphDFS(&MGraphTest1, 1);
	printf("优先搜索\n");
	for (int n = 0; n < MGraphTest1.vexNum; ++n)
	{
		printf("%d\t", MGraphTest2[n]);
	}
	free(MGraphTest2);
	printf("\n 最小生成树 \n");
	MGraph MGraphTest3 = MGraphPrim(&MGraphTest1, 1);
	MGraphPrint(&MGraphTest3);
	printf("\n\n");
	MGraph MGraphgTest4 = MGraphKruskal(&MGraphTest1);
	MGraphPrint(&MGraphgTest4);
	printf("\n\n");
	printf("最短路径生成图(数值大小表示源到该顶点的距离, 行值代表前驱顶点，列值代表目标顶点)\n");
	MGraph MGraphgTest5 = MGraphDijkstra(&MGraphTest1, 1);
	MGraphPrint(&MGraphgTest5);
	MGraphDestroy(&MGraphgTest5);
	MGraphDestroy(&MGraphgTest4);
	MGraphDestroy(&MGraphTest3);
	MGraphDestroy(&MGraphTest1);
	// 邻接表图
	ALGraph ALGraphTest1;
	ALGraphCreateGraph(&ALGraphTest1);
	ALGraphPrint(&ALGraphTest1);
	printf("\n\n拓扑排序\n");
	VERTEXTYPE* ALGraphTest6 = ALGraphTopologicalSorting(&ALGraphTest1);
	if (ALGraphTest6 != NULL)
	{
		for (int n = 0; n < ALGraphTest1.vertexNum; ++n)
		{
			printf("%d\t", ALGraphTest6[n]);
		}
		free(ALGraphTest6);
	}
	printf("\n\n逆拓扑排序\n");
	VERTEXTYPE* ALGraphTest8 = ALGraphTopologicalSortingInverse(&ALGraphTest1);
	if (ALGraphTest8 != NULL)
	{
		for (int n = 0; n < ALGraphTest1.vertexNum; ++n)
		{
			printf("%d\t", ALGraphTest8[n]);
		}
		free(ALGraphTest8);
	}
	printf("\n\ncopy\n");
	ALGraph ALGraphTest7 = ALGraphCopy(&ALGraphTest1);
	ALGraphPrint(&ALGraphTest7);
	printf("\n\n关键路径\n");
	ALGraph ALGraphTest9 = ALGraphCriticalPath(&ALGraphTest1);
	ALGraphPrint(&ALGraphTest9);
	ALGraphDestroy(&ALGraphTest9);
	ALGraphDestroy(&ALGraphTest7);
	VERTEXTYPE* ALGraphTest2 = ALGraphDFS(&ALGraphTest1, 1);
	for (int n = 0; n < ALGraphTest1.vertexNum; ++n)
	{
		printf("%d\t", ALGraphTest2[n]);
	}
	free(ALGraphTest2);
	printf("\n 最小生成树 \n");
	ALGraph ALGraphTest3 = ALGraphPrim(&ALGraphTest1, 1);
	ALGraphPrint(&ALGraphTest3);
	printf("\n\n");
	ALGraph ALGraphTest4 = ALGraphKruskal(&ALGraphTest1);
	ALGraphPrint(&ALGraphTest4);
	printf("\n\n");
	printf("最短路径生成图(数值大小表示源到该顶点的距离)\n");
	ALGraph ALGraphTest5 = ALGraphDijkstra(&ALGraphTest1, 1);
	ALGraphPrint(&ALGraphTest5);
	ALGraphDestroy(&ALGraphTest5);
	ALGraphDestroy(&ALGraphTest4);
	ALGraphDestroy(&ALGraphTest3);
	ALGraphDestroy(&ALGraphTest1);
	// 十字链表图
	OLGraph OLGraphTest1;
	OLGraphCreateGraph(&OLGraphTest1);
	OLGraphPrint(&OLGraphTest1);
	VERTEXTYPE* OLGraphTest2 = OLGraphDFS(&OLGraphTest1, 1);
	for (int n = 0; n < OLGraphTest1.vexNum; ++n)
	{
		printf("%d\t", OLGraphTest2[n]);
	}
	free(OLGraphTest2);
	printf("\n\n复制\n");
	OLGraph OLGraphTest3 = OLGraphCopy(&OLGraphTest1);
	OLGraphPrint(&OLGraphTest3);
	printf("\n\n反转\n");
	OLGraph OLGraphTest4 = OLGraphReverse(&OLGraphTest1);
	OLGraphPrint(&OLGraphTest4);
	printf("\n\n拓扑排序\n");
	VERTEXTYPE* OLGraphTest5 = OLGraphTopologicalSorting(&OLGraphTest1);
	if (OLGraphTest5 != NULL)
	{
		for (int n = 0; n < OLGraphTest1.vexNum; ++n)
		{
			printf("%d\t", OLGraphTest5[n]);
		}
		free(OLGraphTest5);
	}
	printf("\n\n逆拓扑排序\n");
	VERTEXTYPE* OLGraphTest6 = OLGraphTopologicalSortingInverse(&OLGraphTest1);
	if (OLGraphTest6 != NULL)
	{
		for (int n = 0; n < OLGraphTest1.vexNum; ++n)
		{
			printf("%d\t", OLGraphTest6[n]);
		}
		free(OLGraphTest6);
	}
	printf("\n关键路径\n");
	OLGraph OLGraphTest7 = OLGraphCriticalPath(&OLGraphTest1);
	OLGraphPrint(&OLGraphTest7);
	OLGraphDestroy(&OLGraphTest7);
	OLGraphDestroy(&OLGraphTest4);
	OLGraphDestroy(&OLGraphTest3);
	OLGraphDestroy(&OLGraphTest1);
	// 邻接多重表
	AMLGraph AMLGraphTest1;
	AMLGraphCreateGraph(&AMLGraphTest1);
	AMLGraphPrint(&AMLGraphTest1);
	VERTEXTYPE* AMLGraphTest2 = AMLGraphDFS(&AMLGraphTest1, 1);
	for (int n = 0; n < AMLGraphTest1.vexNum; ++n)
	{
		printf("%d\t", AMLGraphTest2[n]);
	}
	free(AMLGraphTest2);
	printf("\n 最小生成树 \n");
	AMLGraph AMLGraphTest3 = AMLGraphPrim(&AMLGraphTest1, 1);
	AMLGraphPrint(&AMLGraphTest3);
	printf("\n\n");
	AMLGraph AMLGraphTest4 = AMLGraphKruskal(&AMLGraphTest1);
	AMLGraphPrint(&AMLGraphTest4);
	printf("\n\n");
	printf("最短路径生成图(数值大小表示源到该顶点的距离)\n");
	AMLGraph AMLGraphTest5 = AMLGraphDijkstra(&AMLGraphTest1, 1);
	AMLGraphPrint(&AMLGraphTest5);
	printf("\n copy \n");
	AMLGraph AMLGraphTest6 = AMLGraphCopy(&AMLGraphTest1);
	AMLGraphPrint(&AMLGraphTest6);
	AMLGraphDestroy(&AMLGraphTest6);
	AMLGraphDestroy(&AMLGraphTest5);
	AMLGraphDestroy(&AMLGraphTest4);
	AMLGraphDestroy(&AMLGraphTest3);
	AMLGraphDestroy(&AMLGraphTest1);

	_CrtDumpMemoryLeaks();
	return 0;
}
