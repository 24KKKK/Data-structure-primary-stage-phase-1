//�㷨6.11�����������㷨
#include <iostream>
#include <fstream>
using namespace std;
#define MaxInt 32767  //��ʾ�ߵ�Ȩֵ�ļ���ֵ������
#define MVNum 100  //��󶥵���

typedef char VerTexType;  //���趥�����������Ϊ�ַ���
typedef int ArcType;  //����ߵ�Ȩֵ����Ϊ����

int Path[MVNum][MVNum];  //���·���϶���vj��ǰһ��������
int D[MVNum][MVNum];  //��¼����vi��vj֮������·������

//ͼ���ڽӾ���
typedef struct
{
    VerTexType vexs[MVNum];  //�����
    ArcType arcs[MVNum][MVNum];  //�ڽӾ���
    int vexnum, arcnum; //ͼ�ĵ�ǰ�����ͱ���
} AMGraph;

//ȷ����v��G�е�λ��
int LocateVex(AMGraph G , VerTexType v)
{
    for(int i = 0; i < G.vexnum; ++i)
        if(G.vexs[i] == v)  //����ڶ��������V������㣬��ô�ͰѶ����λ��i����ȥ
            return i;
    return -1;  //���û��������㣬��ô�ڽӾ����еľ������ΪMaxInt
}//LocateVex

//�����ڽӾ����ʾ��������������G
void CreateUDN(AMGraph &G)
{
    int i , j , k;
	ifstream infile;  //��6.txt����ȡ����
	infile.open("6.txt",ios::in);
	infile >> G.vexnum >> G.arcnum;  //�����ܶ��������ܱ���
    //cout << "�������ܶ��������ܱ������Կո����:";
    //cin >> G.vexnum >> G.arcnum;  //�����ܶ��������ܱ���

    /*cout << endl << "���������ƣ���a" << endl;*/
    for(i = 0; i < G.vexnum; ++i)
    {
		infile >> G.vexs[i];  //������������Ϣ ��char vexs[MVNum];  //�����
		cout << "����ĵ�" << (i + 1) << "���������Ϊ:" << G.vexs[i]<<endl ;
        //cin >> G.vexs[i];  //������������Ϣ ��char vexs[MVNum];  //�����
    }
	cout<<endl ;
    for(i = 0; i < G.vexnum; ++i)   //��ʼ���ڽӾ��󣬱ߵ�Ȩֵ����Ϊ����ֵMaxInt��vexnum�ܶ�����
    {
        for(j = 0; j < G.vexnum; ++j)
        {
            if(j == i)  //������ʾͬһ���㣬����Ϊ0
                G.arcs[i][j] = 0;  //int arcs[MVNum][MVNum];  //�ڽӾ���
            else
                G.arcs[i][j] = MaxInt;
        }//for(i)
    }//for(i)

    /*cout << endl << "����������Ķ��㼰Ȩֵ����a b 3" << endl;*/
    for(k = 0; k < G.arcnum; ++k)  //�����ڽӾ���.arcnum�ߵ�����
    {
        VerTexType v1 , v2;  //VerTexType�൱��char���ַ���
        ArcType w;  //ArcType�൱��int������
		infile >> v1 >> v2 >> w;  //����һ���������Ķ��㼰Ȩֵ
		cout << "����ĵ�" << (k + 1) << "���������Ķ��㼰ȨֵΪ:" << v1 <<"  "<< v2 << "  "<< w << endl;
        //cin >> v1 >> v2 >> w;  //����һ���������Ķ��㼰Ȩֵ
        i = LocateVex(G, v1);
        j = LocateVex(G, v2);  //ȷ��v1��v2��G�е�λ�ã�������������±�
        G.arcs[i][j] = w;  //����Ϊ<v1, v2>�ıߵ�Ȩֵ��Ϊw
    }//for
	infile.close();
}//CreateUDN


//��Floyd�㷨��������G�и��Զ���i��j֮������·��
void ShortestPath_Floyed(AMGraph G)
{
    int i , j , k ;
    for (i = 0; i < G.vexnum; ++i)  //���Խ��֮���ʼ��֪·��������
        for(j = 0; j < G.vexnum; ++j)
        {
            D[i][j] = G.arcs[i][j];  //int D[MVNum][MVNum]; ��¼����vi��vj֮������·������
            if(D[i][j] < MaxInt && i != j)
                Path[i][j] = i; //���i��j֮���л�����j��ǰ����Ϊi
            //int Path[MVNum][MVNum];���·���϶���vj��ǰһ��������
            else
                Path [i][j] = -1;  //���i��j֮���޻�����j��ǰ����Ϊ-1
        }//for
    for(k = 0; k < G.vexnum; ++k)
        for(i = 0; i < G.vexnum; ++i)
            for(j = 0; j < G.vexnum; ++j)
                if(D[i][k] + D[k][j] < D[i][j])   //�����i��k��j��һ��·������
                {
                    D[i][j] = D[i][k] + D[k][j]; //�������k·�����̣���ô����D[i][j]��i��j֮������·��
                    Path[i][j] = Path[k][j];  //����j��ǰ��Ϊk
                }//if
}//ShortestPath_Floyed

//��ʾ���·��
void DisplayPath(AMGraph G , int begin , int temp )  //temp�յ�
{
    if(Path[begin][temp] != -1)  //Path [i][j] = -1;  //���i��j֮���޻�����j��ǰ����Ϊ-1
    {
        DisplayPath(G , begin , Path[begin][temp]);  //�ݹ����·��
        cout << G.vexs[Path[begin][temp]] << "--->";
    }
}//DisplayPath

void main()
{
    cout << "************�㷨6.11�����������㷨�����·��**************" << endl << endl ;

    AMGraph G;
    char start , destination;  //�����յ�
    int num_start , num_destination;  //���ڱ�ʾ�����յ��λ��

    CreateUDN(G);  //�����ڽӾ����ʾ��������������G
	cout<<endl ;

    //cout << endl << "������G������ɣ�" << endl;
    ShortestPath_Floyed(G);  //��Floyd�㷨��������G�и��Զ���i��j֮������·��

    //cout << "����������·����������յ�����ƣ�";
    for(int i = 0; i < G.vexnum; i++) //����ѭ����Ϊ�����ÿ������·���ĵ�ľ���
    {
        for(int j = 0; j < G.vexnum; j++)
        {
            start = G.vexs[i];  //�������
            destination = G.vexs[j];
            num_start = LocateVex(G , start);  //�ҵ������յ���ͼ�е�λ��
            num_destination = LocateVex(G , destination);

            DisplayPath(G , num_start , num_destination);  //��ʾ�����·��������ΪͼG�����num_start���յ�num_destination

            if(D[num_start][num_destination] == 0 || D[num_start][num_destination] == 32767) //���������֮��ľ���Ϊ0����32767����������·��
                continue;
            else
            {
                cout << G.vexs[num_destination] << endl;
                cout << "���·���ĳ���Ϊ��" << D[num_start][num_destination] << endl;
                cout << endl;
            }
        }
    }

}//main
