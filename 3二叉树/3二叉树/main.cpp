/*
前序：a b c d e x
中序：b c a e d x
后序：c b e x d a
*/
#include<iostream>
#include <fstream>
using namespace std;
#define TREELEN  100
//数据结构定义
struct NODE
{
	NODE *pLeft;  //左子树
	NODE *pRight;  //右子树
	char chValue;  //该节点的值
};
void ReBuild(char *pPreOrder, char *pInOrder, int nTreeLen, NODE **pRoot)
{
	// 传过来的数据：ReBuild(szPreOrder, szInOrder, number, &pRoot);
	if(pPreOrder == NULL || pInOrder == NULL)  //检查边界条件，检查前序或者中序是否为空
		return ;
	NODE *pTemp = new NODE;  //获得前序遍历的第一个节点
	pTemp->chValue = *pPreOrder;  //下面三句是将第一个节点初始化为空
	pTemp->pLeft = NULL;
	pTemp->pRight = NULL;
	if(*pRoot == NULL)  //如果节点为空，把当前节点复制到根节点
		*pRoot = pTemp;
	if(nTreeLen == 1)  //如果当前树长度为1，那么已经是最后一个节点，则二叉树只有一个节点
		return;

	//寻找子树长度
	char *pOrgInOrder = pInOrder;
	char *pLeftEnd = pInOrder;
	int nTempLen = 0;  //为了记录每递归一次，子树的长度不要超出序列长度

	while(*pPreOrder != *pLeftEnd)  //找到左子树的结尾
	{
		/* if(pPreOrder == NULL || pLeftEnd == NULL)  //同19行的判断重复，可能不需要再写
		return;*/
		nTempLen++;
		//记录临时长度，以免溢出
		if(nTempLen > nTreeLen)
			break;
		pLeftEnd++;
	}

	int nLeftLen = (int)(pLeftEnd - pOrgInOrder);  //寻找左子树长度
	int nRightLen = nTreeLen - nLeftLen - 1;  //寻找右子树长度，总长度减去左子树，减去根结点

	if(nLeftLen > 0)  //重建左子树
		ReBuild(pPreOrder + 1, pInOrder, nLeftLen, &((*pRoot)->pLeft));  //&((*pRoot)->pLeft)递归到左子树的下一个节点
	if(nRightLen > 0)  //重建右子树
		ReBuild(pPreOrder + nLeftLen + 1, pInOrder + nLeftLen + 1, nRightLen, &((*pRoot)->pRight));
}
//后序遍历结果
void LastPrint(NODE *pRoot)  //递归输出序列节点的值
{
	if(pRoot == NULL)
		return;
	LastPrint(pRoot->pLeft);
	LastPrint(pRoot->pRight);
	cout << pRoot->chValue << " ";
}
void main()
{
	char szPreOrder[TREELEN];  //前序序列个数
	char szInOrder[TREELEN];  //中序序列个数

	int number = 1; //number为序列元素个数，初始化为1
	ifstream infile;  //从文件读入数据
	infile.open("3.txt", ios::in);
	infile >> number;
	if(number <= 0)  //如果输入的元素个数小于等于0，那么二叉树不存在
	{
		cout << "没有二叉树" << endl;
		exit(1);
	}

	cout << "输入的前序序列为：" << endl;
	for(int i = 0; i < number; i++)
	{
		infile >> szPreOrder[i];
		cout << szPreOrder[i] << "  ";  //将读入的前序序列进行输出查看一下，可以省略这一步
		if(number == 1)  
		{
			cout << "后序序列为：" << endl << szPreOrder[i] << endl;
			exit(1);
		}
	}

	cout << endl << "输入的中序序列为：" << endl;
	for(int i = 0; i < number; i++)
	{
		infile >> szInOrder[i];
		cout << szInOrder[i] << "  ";
	}

	NODE *pRoot = NULL;
	ReBuild(szPreOrder, szInOrder, number, &pRoot);

	cout << endl << "后序遍历结果：" << endl;
	LastPrint(pRoot);
	cout << endl;

	/*cout<<"前序遍历结果："<<endl;
	PrePrint(pRoot);
	cout << endl << endl;;

	cout<<"中序遍历结果："<<endl;
	InPrint(pRoot);
	cout << endl;*/
}