#include <stdio.h>
#include <malloc.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define endMark -731
typedef int elemType;
typedef int Status;

typedef struct LNode{           //结点类型
    elemType data;
    struct LNode* next;
}*Link, *Position;              //Link代表头、尾指针，Position代表其他结点指针

typedef struct {                //链表类型
    Link head, tail;            //分别为指向头、尾结点的指针
    int len;                    //表长
}linkList;

/**************************1、链表初始化*****************************/
Status init_llist(linkList *L){
    (*L).head = (*L).tail = (struct LNode*)malloc(sizeof(struct LNode));
    if(!(*L).head) return OVERFLOW;
    (*L).len = 0;
    (*L).head->next = NULL;
    return OK;
}



int main() {
    printf("Hello, World!\n");

    return 0;
}
