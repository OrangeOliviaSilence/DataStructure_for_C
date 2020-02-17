//
// Created by 13715 on 2020/2/17.
//

/************�������У���ͷ��㣩************/
#include "stdio.h"
#include "stdlib.h"         //Ϊ��ʹ��exit
#include "malloc.h"         //Ϊ��ʹ��malloc��realloc��free��
#include "q4BiTree.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status1;
typedef BiTree1 elemType1;

/*****************1.1����ʼ������*******************/
Status1 initLinkedQueue(linkedQueue *Q){
    Q->head = Q->tail = (QNode*)malloc(sizeof(QNode));      //��ʼ���õ�һ��ͷ���
    if(Q->head == NULL) exit(OVERFLOW);         //exit()������stdlib.h����
    Q->head->next = NULL;
    return OK;
}//initLinkedQueue      ��
/*****************1.2������г�*******************/
int lengthLinkedQueue(linkedQueue Q){
    int length;
    queuePtr p;
    for(length=0, p=Q.head->next; p!=NULL; length++, p=p->next);
    //�ж�����������дp<=Q.tail����Ϊ���������У�������ַ������
    return length;
}//lengthLinkedQueue      ��
/*****************1.3�����ٶ���*******************/
Status1 destroyLinkedQueue(linkedQueue *Q){
    queuePtr p = Q->head, q;
    while(p != NULL){
        q = p->next;
        free(p);
        p = q;
    }//while        //���ٺ���յ��������ڣ�ǰ�߽�ͷ���Ҳfree��
    Q->head = Q->tail = NULL;
    return OK;
}//destroyLinkedQueue      ��
/*****************1.4����ն���*******************/
Status1 clearLinkedQueue(linkedQueue *Q){
    queuePtr p = Q->head->next, q;
    while(p != NULL){
        q = p->next;
        free(p);
        p = q;
    }//while
    Q->head->next = NULL;
    Q->tail = Q->head;
    return OK;
}//clearLinkedQueue      ��
/*****************1.5������п�*******************/
Status1 isEmptyLinkedQueue(linkedQueue Q){
    if(Q.head == Q.tail) {printf("QVQ "); return TRUE;}     //�����е�ͷָ�롢βָ��ָ��ͬһ����㣬����п�
    else {printf("YES "); return FALSE;}
}//isEmptyLinkedQueue      ��
/*****************1.6�����������********S***********/
Status1 enterLinkedQueue(linkedQueue *Q, elemType1 e){
    queuePtr s = (QNode*)malloc(sizeof(QNode));
    if(s == NULL) {printf("TAT"); exit(OVERFLOW);}
    s->data = e;
    s->next = Q->tail->next;
    Q->tail->next = s;
    Q->tail = s;
    printf("OHO ");
    return OK;
}//enterLinkedQueue      ��
/*****************1.7�����ݳ�����*******************/
Status1 deleteLinkedQueue(linkedQueue *Q, elemType1 *e){
    if(isEmptyLinkedQueue(*Q)) return ERROR;
    *e = Q->head->next->data;
    queuePtr p = Q->head->next;
    Q->head->next = p->next;
    free(p);
    return OK;
}//deleteLinkedQueue      ��
/* ʹ��malloc����һ���ڴ��ʹ��free�����ͷ��ڴ�ʱ��free�Ĳ�����malloc������ڴ�ε��׵�ַ�����һὫ�ڴ�������ͷ�*/

