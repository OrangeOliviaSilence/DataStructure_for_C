//
// Created by 13715 on 2020/2/17.
//

#ifndef DATASTRUCT_FORSTUDY_Q4BITREE_H
#define DATASTRUCT_FORSTUDY_Q4BITREE_H

//二叉树结点的第1种定义方式————二叉链表
typedef struct BiTNode1{
    char data;
    struct BiTNode1 *lchild, *rchild;
}BiTNode1, *BiTree1;        //BiTree表示根指针

typedef int Status1;
typedef BiTree1 elemType1;

typedef struct QNode{
    elemType1 data;          //数据域
    struct QNode* next;     //指针域
} QNode, *queuePtr;         //队列中的任意一个结点
typedef struct {
    queuePtr head;          //队列头指针
    queuePtr tail;          //队列尾指针
} linkedQueue;              //单链队列

Status1 initLinkedQueue(linkedQueue *Q);
int lengthLinkedQueue(linkedQueue Q);
Status1 destroyLinkedQueue(linkedQueue *Q);
Status1 clearLinkedQueue(linkedQueue *Q);
Status1 isEmptyLinkedQueue(linkedQueue Q);
Status1 enterLinkedQueue(linkedQueue *Q, elemType1 e);
Status1 deleteLinkedQueue(linkedQueue *Q, elemType1 *e);

#endif //DATASTRUCT_FORSTUDY_Q4BITREE_H
