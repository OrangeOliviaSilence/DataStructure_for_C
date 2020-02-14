/************二叉树的链式存储结构************/
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

//二叉树结点的第1种定义方式————二叉链表
typedef struct BiTNode1{
    elemType data;
    struct BiTNode *lchild, *rchild;
}BiTNode1, *BiTree1;

//二叉树结点的第2种定义方式————三叉链表（三叉的意思并非说这是代表三叉树）
typedef struct BiTNode2{        //比二叉链表的结点多了一个父亲指针
    elemType data;
    struct BiTNode *lchild, *rchild, *parent;
}BiTNode2, *BiTree2;

