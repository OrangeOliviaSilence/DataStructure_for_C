/************����������ʽ�洢�ṹ************/
#include <stdio.h>
#include <malloc.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define endMark -731
typedef int Status;
typedef int elemType;

//���������ĵ�1�ֶ��巽ʽ����������������
typedef struct BiTNode1{
    elemType data;
    struct BiTNode *lchild, *rchild;
}BiTNode1, *BiTree1;

//���������ĵ�2�ֶ��巽ʽ�����������������������˼����˵���Ǵ�����������
typedef struct BiTNode2{        //�ȶ�������Ľ�����һ������ָ��
    elemType data;
    struct BiTNode *lchild, *rchild, *parent;
}BiTNode2, *BiTree2;

