//
// Created by 13715 on 2020/2/17.
//

#ifndef DATASTRUCT_FORSTUDY_Q4BITREE_H
#define DATASTRUCT_FORSTUDY_Q4BITREE_H

//���������ĵ�1�ֶ��巽ʽ����������������
typedef struct BiTNode1{
    char data;
    struct BiTNode1 *lchild, *rchild;
}BiTNode1, *BiTree1;        //BiTree��ʾ��ָ��

typedef int Status1;
typedef BiTree1 elemType1;

typedef struct QNode{
    elemType1 data;          //������
    struct QNode* next;     //ָ����
} QNode, *queuePtr;         //�����е�����һ�����
typedef struct {
    queuePtr head;          //����ͷָ��
    queuePtr tail;          //����βָ��
} linkedQueue;              //��������

Status1 initLinkedQueue(linkedQueue *Q);
int lengthLinkedQueue(linkedQueue Q);
Status1 destroyLinkedQueue(linkedQueue *Q);
Status1 clearLinkedQueue(linkedQueue *Q);
Status1 isEmptyLinkedQueue(linkedQueue Q);
Status1 enterLinkedQueue(linkedQueue *Q, elemType1 e);
Status1 deleteLinkedQueue(linkedQueue *Q, elemType1 *e);

#endif //DATASTRUCT_FORSTUDY_Q4BITREE_H
