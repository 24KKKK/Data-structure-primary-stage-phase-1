//3���ɱ������лָ�������
//���룺��������
//����Ҫ�������������̬����������������ֱ�������
/*
�ٸ�����

��֪ǰ����ABCDEFG ������CBEDAFG �������

���ȴ�ȡǰ���1����ĸ(A) ������ĸ������ֳ����� (CBED) (AFG)
A���� (CBED)�������� (FG)������
�ٰ����Ȱ�ǰ�����Ĳ��ֳַ�(BCDE) (FG)

�����ת����
��֪ǰ����BCDE ������CBED �������
��
�Ѿ�ǰ����FG ������FG �������

�ݹ����.
����Ĳ���ʡ�Է���.
ǰ�� ���� : �� �������ֽ� �������ֽ�
BCDE CBED : B   (C) (C)    (ED) (DE)
C    C    : C
DE�� ED   : D   (E) (E)
E    E    : E

FG   FG   : F              (G) (G)
G    G    : G
�ó��Ķ���������
     A
    / \
   B   F
  / \   \
 C   D   G
    /
   E
*/

////ǰ��������
//void PrePrint(NODE *pRoot)
//{
//    if(pRoot == NULL)
//        return;
//    cout << pRoot->chValue << " ";
//    PrePrint(pRoot->pLeft);
//    PrePrint(pRoot->pRight);
//}
////����������
//void InPrint(NODE *pRoot)
//{
//    if(pRoot == NULL)
//        return;
//    InPrint(pRoot->pLeft);
//    cout << pRoot->chValue << " ";
//    InPrint(pRoot->pRight);
//}