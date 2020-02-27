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

//����ʹ�ú��ӱ�ʾ��
//���������
void preOrederTree(CTBox tree[], int root){
    if(root == 0) return;
    printf("%c ", tree[root].data);
    ChildPtr p = tree[root].firstChild;
    while(p){
        preOrederTree(tree, p->childNum);
        p = p->next;
    }//while
}//preOrderTree

//���������
void postOrderTree(CTBox tree[], int root){
    if(root == 0) return;
    ChildPtr p = tree[root].firstChild;
    while(p){
        postOrderTree(tree, p->childNum);
        p = p->next;
    }//while
    printf("%c ", tree[root].data);
}//postOrderTree

//�����ֵܱ�ʾ��
int depthCSTree(CSTree T){      //˼·�����ÿ�����ӵ���ȣ�ȡ���������ȣ�Ȼ����������+1��+1��ָ��Ҫ���ϸ��ڵ㣩��Ϊ�����ķ���ֵ
    if(!T) return 0;
    int depthMax = 0;
    CSTree p = T->firstChild;
    while(p){
        int depth = depthCSTree(p);
        depthMax = depth > depthMax ? depth : depthMax;
        p = p->nextSibling;
    }
    return (depth+1);
}