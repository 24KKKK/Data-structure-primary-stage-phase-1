/*
ǰ��a b c d e x
����b c a e d x
����c b e x d a
*/
#include<iostream>
#include <fstream>
using namespace std;
#define TREELEN  100
//���ݽṹ����
struct NODE
{
	NODE *pLeft;  //������
	NODE *pRight;  //������
	char chValue;  //�ýڵ��ֵ
};
void ReBuild(char *pPreOrder, char *pInOrder, int nTreeLen, NODE **pRoot)
{
	// �����������ݣ�ReBuild(szPreOrder, szInOrder, number, &pRoot);
	if(pPreOrder == NULL || pInOrder == NULL)  //���߽����������ǰ����������Ƿ�Ϊ��
		return ;
	NODE *pTemp = new NODE;  //���ǰ������ĵ�һ���ڵ�
	pTemp->chValue = *pPreOrder;  //���������ǽ���һ���ڵ��ʼ��Ϊ��
	pTemp->pLeft = NULL;
	pTemp->pRight = NULL;
	if(*pRoot == NULL)  //����ڵ�Ϊ�գ��ѵ�ǰ�ڵ㸴�Ƶ����ڵ�
		*pRoot = pTemp;
	if(nTreeLen == 1)  //�����ǰ������Ϊ1����ô�Ѿ������һ���ڵ㣬�������ֻ��һ���ڵ�
		return;

	//Ѱ����������
	char *pOrgInOrder = pInOrder;
	char *pLeftEnd = pInOrder;
	int nTempLen = 0;  //Ϊ�˼�¼ÿ�ݹ�һ�Σ������ĳ��Ȳ�Ҫ�������г���

	while(*pPreOrder != *pLeftEnd)  //�ҵ��������Ľ�β
	{
		/* if(pPreOrder == NULL || pLeftEnd == NULL)  //ͬ19�е��ж��ظ������ܲ���Ҫ��д
		return;*/
		nTempLen++;
		//��¼��ʱ���ȣ��������
		if(nTempLen > nTreeLen)
			break;
		pLeftEnd++;
	}

	int nLeftLen = (int)(pLeftEnd - pOrgInOrder);  //Ѱ������������
	int nRightLen = nTreeLen - nLeftLen - 1;  //Ѱ�����������ȣ��ܳ��ȼ�ȥ����������ȥ�����

	if(nLeftLen > 0)  //�ؽ�������
		ReBuild(pPreOrder + 1, pInOrder, nLeftLen, &((*pRoot)->pLeft));  //&((*pRoot)->pLeft)�ݹ鵽����������һ���ڵ�
	if(nRightLen > 0)  //�ؽ�������
		ReBuild(pPreOrder + nLeftLen + 1, pInOrder + nLeftLen + 1, nRightLen, &((*pRoot)->pRight));
}
//����������
void LastPrint(NODE *pRoot)  //�ݹ�������нڵ��ֵ
{
	if(pRoot == NULL)
		return;
	LastPrint(pRoot->pLeft);
	LastPrint(pRoot->pRight);
	cout << pRoot->chValue << " ";
}
void main()
{
	char szPreOrder[TREELEN];  //ǰ�����и���
	char szInOrder[TREELEN];  //�������и���

	int number = 1; //numberΪ����Ԫ�ظ�������ʼ��Ϊ1
	ifstream infile;  //���ļ���������
	infile.open("3.txt", ios::in);
	infile >> number;
	if(number <= 0)  //��������Ԫ�ظ���С�ڵ���0����ô������������
	{
		cout << "û�ж�����" << endl;
		exit(1);
	}

	cout << "�����ǰ������Ϊ��" << endl;
	for(int i = 0; i < number; i++)
	{
		infile >> szPreOrder[i];
		cout << szPreOrder[i] << "  ";  //�������ǰ�����н�������鿴һ�£�����ʡ����һ��
		if(number == 1)  
		{
			cout << "��������Ϊ��" << endl << szPreOrder[i] << endl;
			exit(1);
		}
	}

	cout << endl << "�������������Ϊ��" << endl;
	for(int i = 0; i < number; i++)
	{
		infile >> szInOrder[i];
		cout << szInOrder[i] << "  ";
	}

	NODE *pRoot = NULL;
	ReBuild(szPreOrder, szInOrder, number, &pRoot);

	cout << endl << "������������" << endl;
	LastPrint(pRoot);
	cout << endl;

	/*cout<<"ǰ����������"<<endl;
	PrePrint(pRoot);
	cout << endl << endl;;

	cout<<"������������"<<endl;
	InPrint(pRoot);
	cout << endl;*/
}