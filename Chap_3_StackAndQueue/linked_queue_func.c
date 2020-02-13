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
Status destroyLinkedQueue(linkedQueue *Q){
    queuePtr p = Q->head, q;
    while(p != NULL){
        q = p->next;
        free(p);
        p = q;
    }        //���ٺ���յ��������ڣ�ǰ�߽�ͷ���Ҳfree��
    Q->head = Q->tail = NULL;
    return OK;
}//destroyLinkedQueue      ��
/*****************1.4����ն���*******************/
Status clearLinkedQueue(linkedQueue *Q){
    queuePtr p = Q->head->next, q;
    while(p != NULL){
        q = p->next;
        free(p);
        p = q;
    }
    Q->head->next = NULL;
    Q->tail = Q->head;
    return OK;
}//clearLinkedQueue      ��
/*****************1.5������п�*******************/
Status isEmptyLinkedQueue(linkedQueue Q){
    if(Q.head == Q.tail) return TRUE;       //�����е�ͷָ�롢βָ��ָ��ͬһ����㣬����п�
    else return FALSE;
}//isEmptyLinkedQueue      ��
/*****************1.6����ͷ����*******************/
Status getHeadLinkedQueue(linkedQueue Q, elemType* e){
    if(isEmptyLinkedQueue(Q)) return ERROR;
    *e = Q.head->next->data;
    return OK;
}//getHeadLinkedQueue      ��
/*****************1.7�����������********S***********/
Status enterLinkedQueue(linkedQueue *Q, elemType e){
    queuePtr s = (QNode*)malloc(sizeof(QNode));
    if(s == NULL) exit(OVERFLOW);
    s->data = e;
    s->next = Q->tail->next;
    Q->tail->next = s;
    Q->tail = s;
    return OK;
}//enterLinkedQueue      ��
/*****************1.8�����ݳ�����*******************/
Status deleteLinkedQueue(linkedQueue *Q, elemType *e){
    if(isEmptyLinkedQueue(*Q)) return ERROR;
    *e = Q->head->next->data;
    queuePtr p = Q->head->next;
    Q->head->next = p->next;
    free(p);
    return OK;
}//deleteLinkedQueue      ��
/*TODO ʹ��malloc����һ���ڴ��ʹ��free�����ͷ��ڴ�ʱ��
        ��free�Ĳ���������ڴ���׵�ַ����������һ�����ڴ棿
        ��free�Ĳ���������ڴ��е�ĳһ���ڴ�ĵ�ַ������ֻ���������ַ����Ӧ����һ���ַ��*/
/*****************1.9����������*******************/
Status traverseLinkedQueue(linkedQueue Q){
    if(isEmptyLinkedQueue(Q)) return ERROR;
    queuePtr p = Q.head->next;
    printf("--��ǰ��������Ϊ��");
    while(p != NULL){
        visit(p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}//traverseLinkedQueue      ��


int main(){
    linkedQueue Q;
    int e;
    printf("//1��init����\n");
    initLinkedQueue(&Q);
    printf("\n");

    printf("//2��isEmpty����\n");
    if(isEmptyLinkedQueue(Q)) printf("--�ö��пգ�\n\n");
    else printf("�ö��зǿգ�\n\n");

    printf("//3��enter����\n");
    printf("--������������ݣ�");
    scanf_s("%d", &e);
    while(e!=endMark){
        enterLinkedQueue(&Q, e);
        scanf_s("%d", &e);
    }
    if(isEmptyLinkedQueue(Q)) printf("--�ö��пգ�\n\n");
    else printf("--�ö��зǿգ�\n\n");

    printf("//4��traverse����\n");
    traverseLinkedQueue(Q);
    printf("\n");

    printf("//5��length����\n");
    printf("--��ǰ���еĳ�Ϊ��%d\n\n", lengthLinkedQueue(Q));

    printf("//6��getHead����\n");
    getHeadLinkedQueue(Q, &e);
    printf("--��ǰ��ͷ����Ϊ��%d\n\n", e);

    printf("//7��delelte����\n");
    deleteLinkedQueue(&Q, &e);
    printf("--��ɾ��������Ϊ��%d\n", e);
    getHeadLinkedQueue(Q, &e);
    printf("--��ǰ��ͷ����Ϊ��%d\n", e);
    printf("--��ǰ���еĳ�Ϊ��%d\n\n", lengthLinkedQueue(Q));

    printf("//8��clear/destroy����\n");
    clearLinkedQueue(&Q);
    if(isEmptyLinkedQueue(Q)) printf("--�ö��пգ�\n\n");
    else printf("--�ö��зǿգ�\n\n");

}