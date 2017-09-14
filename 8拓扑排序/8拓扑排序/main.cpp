//算法6.12　拓扑排序
#include <iostream>
#include <fstream>
using namespace std;
#define MVNum 100  //最大顶点数
#define OK 1
#define ERROR 0

typedef char VerTexType;
//图的邻接表存储表示
typedef struct ArcNode  //边结点
{
	int adjvex;  //该边所指向的顶点的位置
	struct ArcNode *nextarc;  //指向下一条边的指针
} ArcNode;

typedef struct VNode
{
	VerTexType data;  //顶点信息
	ArcNode *firstarc;  //指向第一条依附该顶点的边的指针
} VNode, AdjList[MVNum];  //AdjList表示邻接表类型

typedef struct
{
	AdjList vertices;  //邻接表
	AdjList converse_vertices;  //逆邻接表
	int vexnum, arcnum;  //图的当前顶点数和边数
} ALGraph;

//- - - - -顺序栈的定义- - - - -
typedef struct
{
	int *base;
	int *top;
	int stacksize;  //栈的大小
} spStack;

int indegree[MVNum];  //数组indegree存放各顶点的入度
spStack S;

//栈的操作
void InitStack(spStack &S)
{
	S.base = new int[MVNum];  //初始化栈
	if(!S.base)
		exit(1);
	S.top = S.base;
	S.stacksize = MVNum;  //栈中最大存放100个顶点
}//InitStack

//进栈
void Push(spStack &S , int i)
{
	if(S.top - S.base == S.stacksize)
		return;
	*S.top++ = i;
}//Push

//出栈
void Pop(spStack &S , int &i)
{
	if(S.top == S.base)
		return;
	i = *--S.top;
}//Pop

//判断栈是否为空
bool StackEmpty(spStack S)
{
	if(S.top == S.base)
		return true;
	return false;
}//StackEmpty

//确定点v在G中的位置
int LocateVex(ALGraph G , VerTexType v)
{
	for(int i = 0; i < G.vexnum; ++i)
		if(G.vertices[i].data == v)
			return i;
	return -1;
}//LocateVex


//创建有向图G的邻接表、逆邻接表
int CreateUDG(ALGraph &G)
{
	ifstream infile;
	infile.open("8.txt",ios::in);
	//cout << "请输入总顶点数，总边数，以空格隔开:";
	infile >> G.vexnum >> G.arcnum;  //输入总顶点数，总边数
	cout << "输入的总顶点数和总边数为:" << G.vexnum << "  " << G.arcnum <<endl;
	//cin >> G.vexnum >> G.arcnum;  //输入总顶点数，总边数

	cout << endl << "输入点的名称，如a" << endl;
	for(int i = 0; i < G.vexnum; ++i)  //输入各点，构造表头结点表
	{
		infile >> G.vertices[i].data;  //输入顶点值
		cout << "输入的第" << (i + 1) << "个点的值为:" << G.vertices[i].data << endl;
		//cin >> G.vertices[i].data;  //输入顶点值
		G.converse_vertices[i].data = G.vertices[i].data;

		G.vertices[i].firstarc = NULL;  //初始化邻接表头结点的指针域为NULL
		G.converse_vertices[i].firstarc = NULL; //初始化逆邻接表头结点的指针域为NULL
	}

	cout << endl << "输入边依附的顶点，如a b" << endl;
	for(int k = 0; k < G.arcnum; ++k)  //输入各边，构造邻接表
	{
		VerTexType v1 , v2;
		int i , j;
		infile >> v1 >> v2;  //输入一条边依附的两个顶点
		cout << "输入的第" << (k + 1) << "条边依附的顶点:" << v1 << "  " << v2 <<endl ;
		//cout << "请输入第" << (k + 1) << "条边依附的顶点:";
		//cin >> v1 >> v2;  //输入一条边依附的两个顶点
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		//确定v1和v2在G中位置，即顶点在G.vertices中的序号，找到顶点在v1和v2中的位置顺序

		ArcNode *p1 = new ArcNode;  //生成一个新的边结点*p1
		p1->adjvex = j;  //邻接点序号为j
		p1->nextarc = G.vertices[i].firstarc;
		G.vertices[i].firstarc = p1;
		//将新结点*p1插入顶点vi的边表头部

		ArcNode *p2 = new ArcNode;  //生成一个新的边结点*p2
		p2->adjvex = i;  //逆邻接点序号为i
		p2->nextarc = G.converse_vertices[j].firstarc;
		G.converse_vertices[j].firstarc = p2;
		//将新结点*p2插入顶点vi的边表头部
	}
	return OK;
	infile.close();
}//CreateUDG

//求出各顶点的入度存入数组indegree中
void FindInDegree(ALGraph G)
{
	int i, count;  //count用于入度的计数，最后赋值给indegree数组
	for(i = 0 ; i < G.vexnum ; i++)
	{
		count = 0;
		ArcNode *p = G.converse_vertices[i].firstarc;
		if(p)
		{
			while(p)
			{
				p = p->nextarc;
				count++;
			}
		}
		indegree[i] = count;
	}
}//FindInDegree

//有向图G采用邻接表存储结构.若G无回路，则生成G的一个拓扑序列topo[]并返回OK，否则ERROR
int TopologicalSort(ALGraph G , int topo[])
{
	int i , m;
	FindInDegree(G);  //求出各顶点的入度存入数组indegree中
	InitStack(S);  //栈S初始化为空
	for(i = 0; i < G.vexnum; ++i)
		if(!indegree[i]) Push(S, i);  //入度为0者进栈
	m = 0;  //对输出顶点计数，初始为0
	while(!StackEmpty(S))  //栈S非空
	{
		Pop(S, i);  //将栈顶顶点vi出栈
		topo[m] = i;  //将vi保存在拓扑序列数组topo中
		++m;  //对输出顶点计数
		ArcNode *p = G.vertices[i].firstarc;  //p指向vi的第一个邻接点
		while(p)
		{
			int k = p->adjvex;  //vk为vi的邻接点
			--indegree[k];  //vi的每个邻接点的入度减1
			if(indegree[k] == 0)  
				Push(S, k);  //若入度减为0，则入栈
			p = p->nextarc;  //p指向顶点vi下一个邻接结点
		}//while(p)
	}//while(!StackEmpty(S))

	if(m < G.vexnum)  
		return ERROR;  //该有向图有回路
	else 
		return OK;
}//TopologicalSort

int main()
{
	//cout << "************算法6.12　拓扑排序**************" << endl << endl;
	ALGraph G;
	CreateUDG(G);
	int *topo = new int [G.vexnum];  //topo  G的拓扑序列

	cout << endl;
	//cout << "有向图的邻接表、逆邻接表创建完成!" << endl << endl;

	if(TopologicalSort(G , topo))
	{
		cout << "是AOV网，该有向图的拓扑排序序列为：";
		for(int j = 0 ; j < G.vexnum; j++)
		{
			if(j != G.vexnum - 1)
				cout << G.vertices[topo[j]].data << " , ";
			else
				cout << G.vertices[topo[j]].data << endl << endl;
		}//for
	}
	else
		cout << "网中存在环，不是AOV网，无法进行拓扑排序！" << endl << endl;
	return OK;
}//main