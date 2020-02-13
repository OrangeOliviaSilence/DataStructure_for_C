#include <stdio.h>
#include <malloc.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define endMark -731
#define elemType int
typedef int Status;
typedef struct CLNode {           //定义单链表结点
    elemType data;               //结点数据域
    struct CLNode* next;          // 结点指针域。指向逻辑上的下一个结点
}CLNode, * clinkList;              //linkList结构体指针的类型名，专门用来表示————头指针变量

/******************************1、循环链表初始化***********************************/
Status init_cllist(clinkList* head){
    *head = (CLNode*)malloc(sizeof(CLNode));
    if(!head) return OVERFLOW;
    (*head)->next = *head;
    return OK;
}//init_cllist
/****************************2、销毁表*********************************/

/****************************3、清空表*********************************/
void clear_cllist(clinkList *head){
    clinkList p = (*head)->next;
    while(p==*head){
        (*head)->next = p->next;
        free(p);
        p = (*head)->next;
    }
}//clear_cllist
/****************************4、求表长*********************************/
int length_cllist(clinkList head) {
    int length;
    clinkList p = head->next;
    for (length = 0; p!=head; length++)
        p = p->next;
    return length;
}//length_cllist
/****************************5、查表空*********************************/
void empty_cllist(clinkList L){
    if(L->next==L) printf("clinklist is empty!\n");
    else printf("clinklist isn't empty!\n");
}//empty_cllist
/****************************6、取元素（取表中某一位置的元素）*********************************/
Status getelem_cllist(clinkList head, int i, int* e) {            //纯C语言不支持引用参数，C++才支持
    if (i<1 || i>length_cllist(head)) {*e= endMark; return ERROR;}        //若i<1或者i>链表长度，则是非法的，直接报错
    clinkList p = head->next;
    for (int j = 1; j < i; j++)
        p = p->next;
    *e = p->data;
    return OK;
}//getelem_cllist
/****************************7、在表中定位某个元素（取第一个满足的）*********************************/
int locate_llist(clinkList head, int e){
    int i;
    clinkList p;
    for(i=1, p = head->next; p!=head && p->data!=e; i++, p=p->next);
    if(!p) return endMark;        //因为位置下标不可能小于1，所以返回-731表示在链表中没有定位到
    else return i;
}//locate_llist
/****************************8、求前驱*********************************/
Status prior_cllist(clinkList L, int i, elemType *e){
    if (i<=1 || i>length_cllist(L)) {*e= endMark; return ERROR;}
    int j;
    clinkList p;
    for(j=1, p=L->next; j<i-1;j++, p=p->next);
    *e = p->data;
    return OK;
}//prior_llist
/****************************9、求后继*********************************/

/****************************10、插入元素*********************************/

/****************************11、删除元素*********************************/

/****************************12、手动输入创建单链表————头插法*********************************/
Status head_create_cllist(clinkList *head) {
    init_cllist(head);                  //申请头结点
    clinkList s;
    elemType e;
    printf("创建表，请按序输入数据：");
    scanf_s("%d", &e);
    while (e != endMark) {
        s = (CLNode*)malloc(sizeof(CLNode)); if (!s) return ERROR;
        s->data = e; s->next = (*head)->next;
        (*head)->next = s;
        scanf_s("%d", &e);
    }
    return OK;
}//head_create_cllist
/****************************13、手动输入创建单链表————尾插法*********************************/
Status tail_create_cllist(clinkList* head){            //和单向链表一样
    init_cllist(head);
    int e;
    clinkList p = *head, s;
    printf("创建表，请按序输入数据：");
    scanf_s("%d", &e);
    while(e!=endMark){
        s = (CLNode*)malloc(sizeof(CLNode)); if(!s) return ERROR;
        s->data = e; s->next = p->next;
        p->next = s;
        p = s;
        scanf_s("%d", &e);
    }
    printf("\n");
    return OK;
}//tail_create_cllist
/****************************14、逆置链表————头插法*********************************/

/*************15、逆置链表————将所有结点的next指针逆转，最后再让头节点指向逆置前的最后一个结点*****************/

/****************************16、遍历链表*********************************/

//不带头节点的没做QVQ

int main() {
    clinkList L;
    int i,j,e; clinkList p;
    printf("//1、init测试\n");
    tail_create_cllist(&L);
    printf("//2、length测试\n");
    printf("该链表的长度：%d\n\n", length_cllist(L));
    printf("//3、tail/head测试\n");
    printf("//该链表的元素：\n");
    for(j=1, p=L->next; p!=L;j++, p=p->next )
        printf("%d ", p->data);
    printf("\n");
    printf("\n");
    printf("//5、empty测试\n");
    empty_cllist(L);
    printf("\n");
}
