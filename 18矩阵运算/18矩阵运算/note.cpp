//18、矩阵运算
//输入：待运算矩阵
//功能要求：输出矩阵加法、减法和乘法的运算结果
/*
//[实验任务五]：文件输入输出以及数据处理  底云飞
//从文件f1.txt中读取数据，并按照从小到大的顺序排列，
//将结果输出在屏幕中，同时存入f2.txt文件中。
#include <iostream>
#include <fstream>
using namespace std;
void main()
{
	int a[10],i,j,t,N=10;
	ifstream infile;                       //用istream打开f1.txt
	infile.open("f1.txt",ios::in);          //打开f1.txt
	ofstream outfile("f2.txt",ios::out);
	for(i=0;i<10;i++)
	{
		infile>>a[i];                     //把读取的数放在a【i】中
	}

	for(i=0;i<N-1;i++)            //冒泡排序
		for(j=0;j<N-i-1;j++)
			if(a[j]>a[j+1])
			{
				t=a[j];
				a[j]=a[j+1];
				a[j+1]=t;
			}

	for(i=0;i<10;i++)
	{
		cout<<a[i]<<"  ";
		outfile<<a[i]<<"  ";
	}

	infile.close();
	outfile.close();
}
*/