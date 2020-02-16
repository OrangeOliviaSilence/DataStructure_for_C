/************����3�ֳ��ô洢�ṹ************/
#include "stdio.h"
#include "malloc.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define endMark -731
#define MAX_TREE_SIZE
typedef int Status;
typedef int elemType;

//1��˫�ױ�ʾ����˳��洢��

//2�����ӱ�ʾ��
typedef struct CTNode{
    int childNum;       //�ú��ӽڵ�����
    struct CTNode *next;        //ָ��ú��ӽڵ�Ĵ��׵�
} *ChildPtr;
typedef struct CTBox{
    elemType data;      //�ýڵ������
    ChildPtr firstChild;        //ָ��ýڵ�ĳ���
    //int Parent;     //�ýڵ�ĸ��ڵ���ţ���������ͱ���ˡ���˫�׵ĺ�������
} CTBox;
typedef struct {
    int n, r;       //�ֱ��ʾ�����Ľڵ��������ڵ�����
    CTBox nodes[MAX_TREE_SIZE];         //���˳����д���Ÿ��������еĽڵ�
} CTree;

//3�������ֵܱ�ʾ��
typedef struct CSNode{
    elemType data;
    struct CSNode *firstChild, *nextSibling;
} CSNode, *CSTree;