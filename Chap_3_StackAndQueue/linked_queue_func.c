/************�������У���ͷ��㣩************/
#include "stdio.h"
#include "stdlib.h"         //Ϊ��ʹ��exit
#include "malloc.h"         //Ϊ��ʹ��malloc��realloc��free��
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define endMark -731
typedef int Status;
typedef int elemType;

typedef struct QNode{
    elemType data;          //������
    struct QNode* next;     //ָ����
} QNode, *queuePtr;         //�����е�����һ�����
typedef struct {
    queuePtr head;          //����ͷָ��
    queuePtr tail;          //����βָ��
} linkedQueue;              //��������

/**
 * ���ն˴�ӡ���
 * @param e
 */
void visit(elemType e){
    printf("%d ", e);
}//visit

/*****************1.1����ʼ������*******************/
Status initLinkedQueue(linkedQueue *Q){
    Q->head = Q->tail = (QNode*)malloc(sizeof(QNode));      //��ʼ���õ�һ��ͷ���
    if(Q->head == NULL) exit(OVERFLOW);         //exit()������stdlib.h����
    Q->head->next = NULL;
    return OK;
}//initLinkedQueue
/*****************1.2������г�*******************/
int lengthLinkedQueue(linkedQueue Q){
    int length;
    queuePtr p;
    for(length=0, p=Q.head->next; p!=NULL; length++, p=p->next);
        //�ж�����������дp<=Q.tail����Ϊ���������У�������ַ������
    return length;
}//lengthLinkedQueue
/*****************1.3�����ٶ���*******************/
Status destroyLinkedQueue(linkedQueue *Q){
    for(queuePtr p=Q->head; p!=NULL; p=p->next) free(p);        //���ٺ���յ��������ڣ�ǰ�߽�ͷ���Ҳfree��
    Q->head = Q->tail = NULL;
    return OK;
}//destroyLinkedQueue
/*****************1.4����ն���*******************/
Status clearLinkedQueue(linkedQueue *Q){
    for(queuePtr p=Q->head->next; p!=NULL; p=p->next) free(p);
    Q->head->next = NULL;
    Q->tail = Q->head;
    return OK;
}//clearLinkedQueue
/*****************1.5������п�*******************/
Status isEmptyLinkedQueue(linkedQueue Q){
    if(Q.head == Q.tail) return TRUE;       //�����е�ͷָ�롢βָ��ָ��ͬһ����㣬����п�
    else return FALSE;
}//isEmptyLinkedQueue
/*****************1.6����ͷ����*******************/
Status getHeadLinkedQueue(linkedQueue Q, elemType* e){
    if(isEmptyLinkedQueue(Q)) return ERROR;
    *e = Q.head->next->data;
    return OK;
}//getHeadLinkedQueue
/*****************1.7�����������********S***********/
Status enterLinkedQueue(linkedQueue *Q, elemType e){
    queuePtr s = (QNode*)malloc(sizeof(QNode));
    if(s == NULL) exit(OVERFLOW);
    s->data = e;
    s->next = Q->tail->next;
    Q->tail->next = s;
    Q->tail = s;
    return OK;
}//enterLinkedQueue
/*****************1.8�����ݳ�����*******************/
Status deleteLinkedQueue(linkedQueue *Q, elemType *e){
    if(isEmptyLinkedQueue(*Q)) return ERROR;

}//deleteLinkedQueue
/*****************1.9����������*******************/

int main(){

}