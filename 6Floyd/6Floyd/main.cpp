//算法6.11　弗洛伊德算法
#include <iostream>
#include <fstream>
using namespace std;
#define MaxInt 32767  //表示边的权值的极大值，即∞
#define MVNum 100  //最大顶点数

typedef char VerTexType;  //假设顶点的数据类型为字符型
typedef int ArcType;  //假设边的权值类型为整型

int Path[MVNum][MVNum];  //最短路径上顶点vj的前一顶点的序号
int D[MVNum][MVNum];  //记录顶点vi和vj之间的最短路径长度

//图的邻接矩阵
typedef struct
{
    VerTexType vexs[MVNum];  //顶点表
    ArcType arcs[MVNum][MVNum];  //邻接矩阵
    int vexnum, arcnum; //图的当前点数和边数
} AMGraph;

//确定点v在G中的位置
int LocateVex(AMGraph G , VerTexType v)
{
    for(int i = 0; i < G.vexnum; ++i)
        if(G.vexs[i] == v)  //如果在顶点表中有V这个顶点，那么就把顶点的位置i传回去
            return i;
    return -1;  //如果没有这个顶点，那么邻接矩阵中的距离则变为MaxInt
}//LocateVex

//采用邻接矩阵表示法，创建有向网G
void CreateUDN(AMGraph &G)
{
    int i , j , k;
	ifstream infile;  //打开6.txt来读取数据
	infile.open("6.txt",ios::in);
	infile >> G.vexnum >> G.arcnum;  //输入总顶点数，总边数
    //cout << "请输入总顶点数，总边数，以空格隔开:";
    //cin >> G.vexnum >> G.arcnum;  //输入总顶点数，总边数

    /*cout << endl << "输入点的名称，如a" << endl;*/
    for(i = 0; i < G.vexnum; ++i)
    {
		infile >> G.vexs[i];  //依次输入点的信息 。char vexs[MVNum];  //顶点表
		cout << "输入的第" << (i + 1) << "个点的名称为:" << G.vexs[i]<<endl ;
        //cin >> G.vexs[i];  //依次输入点的信息 。char vexs[MVNum];  //顶点表
    }
	cout<<endl ;
    for(i = 0; i < G.vexnum; ++i)   //初始化邻接矩阵，边的权值均置为极大值MaxInt。vexnum总顶点数
    {
        for(j = 0; j < G.vexnum; ++j)
        {
            if(j == i)  //相等则表示同一个点，距离为0
                G.arcs[i][j] = 0;  //int arcs[MVNum][MVNum];  //邻接矩阵
            else
                G.arcs[i][j] = MaxInt;
        }//for(i)
    }//for(i)

    /*cout << endl << "输入边依附的顶点及权值，如a b 3" << endl;*/
    for(k = 0; k < G.arcnum; ++k)  //构造邻接矩阵.arcnum边的总数
    {
        VerTexType v1 , v2;  //VerTexType相当于char，字符型
        ArcType w;  //ArcType相当于int，整型
		infile >> v1 >> v2 >> w;  //输入一条边依附的顶点及权值
		cout << "输入的第" << (k + 1) << "条边依附的顶点及权值为:" << v1 <<"  "<< v2 << "  "<< w << endl;
        //cin >> v1 >> v2 >> w;  //输入一条边依附的顶点及权值
        i = LocateVex(G, v1);
        j = LocateVex(G, v2);  //确定v1和v2在G中的位置，即顶点数组的下标
        G.arcs[i][j] = w;  //顶点为<v1, v2>的边的权值置为w
    }//for
	infile.close();
}//CreateUDN


//用Floyd算法求有向网G中各对顶点i和j之间的最短路径
void ShortestPath_Floyed(AMGraph G)
{
    int i , j , k ;
    for (i = 0; i < G.vexnum; ++i)  //各对结点之间初始已知路径及距离
        for(j = 0; j < G.vexnum; ++j)
        {
            D[i][j] = G.arcs[i][j];  //int D[MVNum][MVNum]; 记录顶点vi和vj之间的最短路径长度
            if(D[i][j] < MaxInt && i != j)
                Path[i][j] = i; //如果i和j之间有弧，则将j的前驱置为i
            //int Path[MVNum][MVNum];最短路径上顶点vj的前一顶点的序号
            else
                Path [i][j] = -1;  //如果i和j之间无弧，则将j的前驱置为-1
        }//for
    for(k = 0; k < G.vexnum; ++k)
        for(i = 0; i < G.vexnum; ++i)
            for(j = 0; j < G.vexnum; ++j)
                if(D[i][k] + D[k][j] < D[i][j])   //如果从i经k到j的一条路径更短
                {
                    D[i][j] = D[i][k] + D[k][j]; //如果经过k路径更短，那么更新D[i][j]，i和j之间的最短路径
                    Path[i][j] = Path[k][j];  //更改j的前驱为k
                }//if
}//ShortestPath_Floyed

//显示最短路径
void DisplayPath(AMGraph G , int begin , int temp )  //temp终点
{
    if(Path[begin][temp] != -1)  //Path [i][j] = -1;  //如果i和j之间无弧，则将j的前驱置为-1
    {
        DisplayPath(G , begin , Path[begin][temp]);  //递归输出路径
        cout << G.vexs[Path[begin][temp]] << "--->";
    }
}//DisplayPath

void main()
{
    cout << "************算法6.11　弗洛伊德算法求最短路径**************" << endl << endl ;

    AMGraph G;
    char start , destination;  //起点和终点
    int num_start , num_destination;  //用于表示起点和终点的位置

    CreateUDN(G);  //采用邻接矩阵表示法，创建有向网G
	cout<<endl ;

    //cout << endl << "有向网G创建完成！" << endl;
    ShortestPath_Floyed(G);  //用Floyd算法求有向网G中各对顶点i和j之间的最短路径

    //cout << "请依次输入路径的起点与终点的名称：";
    for(int i = 0; i < G.vexnum; i++) //两个循环是为了输出每两个有路径的点的距离
    {
        for(int j = 0; j < G.vexnum; j++)
        {
            start = G.vexs[i];  //起点名称
            destination = G.vexs[j];
            num_start = LocateVex(G , start);  //找到起点和终点在图中的位置
            num_destination = LocateVex(G , destination);

            DisplayPath(G , num_start , num_destination);  //显示出最短路径，参数为图G，起点num_start，终点num_destination

            if(D[num_start][num_destination] == 0 || D[num_start][num_destination] == 32767) //如果两个点之间的距离为0或者32767，则不输出这个路径
                continue;
            else
            {
                cout << G.vexs[num_destination] << endl;
                cout << "最短路径的长度为：" << D[num_start][num_destination] << endl;
                cout << endl;
            }
        }
    }

}//main
