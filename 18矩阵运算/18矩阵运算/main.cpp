#include <iostream>
#include <fstream>
#define N 10
using namespace std;

//����ӷ�
int jia(int a[N][N], int b[N][N], int n)
{
    int c[N][N];
    cout << endl << "����ӷ�Ϊ��" << endl;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
        {
            c[i][j] = a[i][j] + b[i][j];
            cout << c[i][j] << "  ";
            if(j == (n - 1))  cout << endl;
        }
    return c[N][N];
}
//�������
int jian(int a[N][N], int b[N][N], int n)
{
    int d[N][N];
    cout << endl << "�������Ϊ��" << endl;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
        {
            d[i][j] = a[i][j] - b[i][j];
            cout << d[i][j] << "  ";
            if(j == (n - 1))  cout << endl;
        }
    return d[N][N];
}
//����˷�
int cheng(int a[N][N], int b[N][N], int n)
{
    int e[N][N];
    cout << endl << "����˷�Ϊ��" << endl;
    for(int i = 0; i < n; i++) //���г��������ܹ��ó���ǰ���е�ֵ
        for(int j = 0; j < n; j++)
        {
            int s = 0;
            for(int k = 0; k < n; k++)
                s = s + a[i][k] * b[k][j]; //��Ҫ��������֮���ټ�
            e[i][j] = s;
            cout << s << "  ";
            if(j == (n - 1))  cout << endl; //������������֮�� Ҫ����
        }
		cout << endl;
    return e[N][N];
}

//��ӡ������
void display(int a[N][N], int n)
{
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
        {
            cout << a[i][j] << " ";
            if(j == n - 1)
                cout << endl;
        }
}

void main()
{
    int n = 1; //�������
    int a[N][N], b[N][N], c[N][N], d[N][N], e[N][N]; //abcde�ֱ��ʾ��һ���ڶ����ӷ����������˷�����

	ifstream infile;                       //��istream��18.txt
	infile.open("18.txt",ios::in);          //��18.txt

	infile>>n;  //ȡ�ļ��еĵ�һ������Ϊ�������

	for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
			infile >> a[i][j];
    cout<<"��һ������Ϊ��"<<endl;
    display(a, n);

	for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            infile >> b[i][j];
	cout<<endl<<"�ڶ�������Ϊ��"<<endl;
    display(b, n);

    c[N][N] = jia(a, b, n);
    d[N][N] = jian(a, b, n);
    e[N][N] = cheng(a, b, n);
	infile.close();  //�رմ򿪵��ļ�
}