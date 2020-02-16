/************树的3种常用存储结构************/
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

//1、双亲表示法（顺序存储）

//2、孩子表示法
typedef struct CTNode{
    int childNum;       //该孩子节点的序号
    struct CTNode *next;        //指向该孩子节点的次亲弟
} *ChildPtr;
typedef struct CTBox{
    elemType data;      //该节点的数据
    ChildPtr firstChild;        //指向该节点的长子
    //int Parent;     //该节点的父节点序号，加上这个就变成了“带双亲的孩子链表”
} CTBox;
typedef struct {
    int n, r;       //分别表示该树的节点数、根节点的序号
    CTBox nodes[MAX_TREE_SIZE];         //这个顺序表中存放着该树中所有的节点
} CTree;

//3、孩子兄弟表示法
typedef struct CSNode{
    elemType data;
    struct CSNode *firstChild, *nextSibling;
} CSNode, *CSTree;