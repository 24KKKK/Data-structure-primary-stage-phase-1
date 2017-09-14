//3、由遍历序列恢复二叉树
//输入：遍历序列
//功能要求：输出二叉树形态或输出二叉树的三种遍历序列
/*
举个例子

已知前序是ABCDEFG 中序是CBEDAFG 求二叉树

首先从取前序第1个字母(A) 按此字母把中序分成两段 (CBED) (AFG)
A做根 (CBED)做左子树 (FG)右子树
再按长度把前序后面的部分分成(BCDE) (FG)

问题就转换成
已知前序是BCDE 中序是CBED 求二叉树
和
已经前序是FG 中序是FG 求二叉树

递归求解.
下面的步骤省略分析.
前序 中序 : 根 左子树分解 右子树分解
BCDE CBED : B   (C) (C)    (ED) (DE)
C    C    : C
DE　 ED   : D   (E) (E)
E    E    : E

FG   FG   : F              (G) (G)
G    G    : G
得出的二叉树就是
     A
    / \
   B   F
  / \   \
 C   D   G
    /
   E
*/

////前序遍历结果
//void PrePrint(NODE *pRoot)
//{
//    if(pRoot == NULL)
//        return;
//    cout << pRoot->chValue << " ";
//    PrePrint(pRoot->pLeft);
//    PrePrint(pRoot->pRight);
//}
////中序遍历结果
//void InPrint(NODE *pRoot)
//{
//    if(pRoot == NULL)
//        return;
//    InPrint(pRoot->pLeft);
//    cout << pRoot->chValue << " ";
//    InPrint(pRoot->pRight);
//}