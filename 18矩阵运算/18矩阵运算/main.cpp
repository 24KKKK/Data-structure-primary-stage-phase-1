#include <iostream>
#include <fstream>
#define N 10
using namespace std;

//矩阵加法
int jia(int a[N][N], int b[N][N], int n)
{
    int c[N][N];
    cout << endl << "矩阵加法为：" << endl;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
        {
            c[i][j] = a[i][j] + b[i][j];
            cout << c[i][j] << "  ";
            if(j == (n - 1))  cout << endl;
        }
    return c[N][N];
}
//矩阵减法
int jian(int a[N][N], int b[N][N], int n)
{
    int d[N][N];
    cout << endl << "矩阵减法为：" << endl;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
        {
            d[i][j] = a[i][j] - b[i][j];
            cout << d[i][j] << "  ";
            if(j == (n - 1))  cout << endl;
        }
    return d[N][N];
}
//矩阵乘法
int cheng(int a[N][N], int b[N][N], int n)
{
    int e[N][N];
    cout << endl << "矩阵乘法为：" << endl;
    for(int i = 0; i < n; i++) //横行乘以竖列能够得出当前行列的值
        for(int j = 0; j < n; j++)
        {
            int s = 0;
            for(int k = 0; k < n; k++)
                s = s + a[i][k] * b[k][j]; //需要三个数乘之后再加
            e[i][j] = s;
            cout << s << "  ";
            if(j == (n - 1))  cout << endl; //计算完三个数之后 要换行
        }
		cout << endl;
    return e[N][N];
}

//打印出矩阵
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
    int n = 1; //矩阵阶数
    int a[N][N], b[N][N], c[N][N], d[N][N], e[N][N]; //abcde分别表示第一，第二，加法，减法，乘法矩阵

	ifstream infile;                       //用istream打开18.txt
	infile.open("18.txt",ios::in);          //打开18.txt

	infile>>n;  //取文件中的第一个数作为矩阵阶数

	for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
			infile >> a[i][j];
    cout<<"第一个矩阵为："<<endl;
    display(a, n);

	for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            infile >> b[i][j];
	cout<<endl<<"第二个矩阵为："<<endl;
    display(b, n);

    c[N][N] = jia(a, b, n);
    d[N][N] = jian(a, b, n);
    e[N][N] = cheng(a, b, n);
	infile.close();  //关闭打开的文件
}