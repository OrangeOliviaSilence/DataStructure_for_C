//
// Created by 13715 on 2020/2/17.
//

/************单链队列（带头结点）************/
#include "stdio.h"
#include "stdlib.h"         //为了使用exit
#include "malloc.h"         //为了使用malloc、realloc、free等
#include "q4BiTree.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status1;
typedef BiTree1 elemType1;

/*****************1.1、初始化队列*******************/
Status1 initLinkedQueue(linkedQueue *Q){
    Q->head = Q->tail = (QNode*)malloc(sizeof(QNode));      //初始化得到一个头结点
    if(Q->head == NULL) exit(OVERFLOW);         //exit()函数在stdlib.h库中
    Q->head->next = NULL;
    return OK;
}//initLinkedQueue      √
/*****************1.2、求队列长*******************/
int lengthLinkedQueue(linkedQueue Q){
    int length;
    queuePtr p;
    for(length=0, p=Q.head->next; p!=NULL; length++, p=p->next);
    //判断条件不可以写p<=Q.tail，因为这是链队列，各结点地址不连续
    return length;
}//lengthLinkedQueue      √
/*****************1.3、销毁队列*******************/
Status1 destroyLinkedQueue(linkedQueue *Q){
    queuePtr p = Q->head, q;
    while(p != NULL){
        q = p->next;
        free(p);
        p = q;
    }//while        //销毁和清空的区别在于，前者将头结点也free掉
    Q->head = Q->tail = NULL;
    return OK;
}//destroyLinkedQueue      √
/*****************1.4、清空队列*******************/
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
}//clearLinkedQueue      √
/*****************1.5、查队列空*******************/
Status1 isEmptyLinkedQueue(linkedQueue Q){
    if(Q.head == Q.tail) {printf("QVQ "); return TRUE;}     //若队列的头指针、尾指针指向同一个结点，则队列空
    else {printf("YES "); return FALSE;}
}//isEmptyLinkedQueue      √
/*****************1.6、数据入队列********S***********/
Status1 enterLinkedQueue(linkedQueue *Q, elemType1 e){
    queuePtr s = (QNode*)malloc(sizeof(QNode));
    if(s == NULL) {printf("TAT"); exit(OVERFLOW);}
    s->data = e;
    s->next = Q->tail->next;
    Q->tail->next = s;
    Q->tail = s;
    printf("OHO ");
    return OK;
}//enterLinkedQueue      √
/*****************1.7、数据出队列*******************/
Status1 deleteLinkedQueue(linkedQueue *Q, elemType1 *e){
    if(isEmptyLinkedQueue(*Q)) return ERROR;
    *e = Q->head->next->data;
    queuePtr p = Q->head->next;
    Q->head->next = p->next;
    free(p);
    return OK;
}//deleteLinkedQueue      √
/* 使用malloc分配一段内存后，使用free函数释放内存时，free的参数是malloc分配的内存段的首地址，并且会将内存段整个释放*/

