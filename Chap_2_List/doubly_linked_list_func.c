#include "stdio.h"
#include "malloc.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 1
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef int elemType;
typedef struct DuLNode{
    elemType data;
    struct DuLNode* prior;
    struct DuLNode* next;
}DuLNode, *DulinkList;

/******************************1、循环链表初始化***********************************/
Status init_dllist(DulinkList *L){
    *L = (DuLNode*)malloc(sizeof(DuLNode));
    if(*L==NULL) return OVERFLOW;
    (*L)->prior = (*L)->next = NULL;
    return OK;
}
/****************************2、求表长*********************************/
int length_dllist(DulinkList L) {
    int length;
    DulinkList p = L->next;
    for (length = 0; p!=NULL; length++)
        p = p->next;
    return length;
}//length_cllist
// /****************************3、插入元素*********************************/
Status insert_dllist(DulinkList *L, int e, int i){
    if(i<1 || i>length_dllist(*L)) return ERROR;
    int j;
    DulinkList p, s;
    s = (DuLNode*)malloc(sizeof(DuLNode));
    //for(j=1, p=(*L)->next; j<i-1; j++, p=p->next);
    //s->data = e;
    //p->next->prior = s; s->next = p->next;
    //p->next = s; s->prior = p;
    for(j=1, p=(*L)->next; j<i; j++, p=p->next);
    s->data = e;
    s->next = p; s->prior = p->prior;
    p->prior->next = s; p->prior = s;
    return OK;
}
/****************************4、删除元素*********************************/
Status delete_ddlist(DulinkList *L, int i){
    if(i<1 || i>length_dllist(*L)) return ERROR;
    int j;
    DulinkList p;
    for(j=1, p=(*L)->next; j<i; j++, p=p->next);
    p->next->prior = p->prior;
    p->prior->next = p->next;
    free(p);
    return OK;
}
//除了插入、删除函数，其他函数和单向链表相似

int main(){

}