//18����������
//���룺���������
//����Ҫ���������ӷ��������ͳ˷���������
/*
//[ʵ��������]���ļ���������Լ����ݴ���  ���Ʒ�
//���ļ�f1.txt�ж�ȡ���ݣ������մ�С�����˳�����У�
//������������Ļ�У�ͬʱ����f2.txt�ļ��С�
#include <iostream>
#include <fstream>
using namespace std;
void main()
{
	int a[10],i,j,t,N=10;
	ifstream infile;                       //��istream��f1.txt
	infile.open("f1.txt",ios::in);          //��f1.txt
	ofstream outfile("f2.txt",ios::out);
	for(i=0;i<10;i++)
	{
		infile>>a[i];                     //�Ѷ�ȡ��������a��i����
	}

	for(i=0;i<N-1;i++)            //ð������
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