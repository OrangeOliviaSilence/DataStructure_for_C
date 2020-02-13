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
typedef struct LNode {           //定义单链表结点
    elemType data;              //结点数据域
    struct LNode* next;         // 结点指针域。指向逻辑上的下一个结点
}LNode, * linkList;              //linkList结构体指针的类型名，专门用来表示————头指针变量


//一、带头结点的链表操作
/****************************1、单链表初始化*********************************/
Status init_llist(linkList *L) {
    *L = (LNode*)malloc(sizeof(LNode));
    if (!(*L)) return OVERFLOW;
    (*L)->next = NULL;
    return OK;
}//init_llist  √
/****************************2、销毁表*********************************/
void destroy_llist(linkList  *L){
    linkList p = *L;
    while(*L){
        (*L)->next = p->next;
        free(p);
        p = p->next;
    }
}//destroy_llist  √
/****************************3、清空表*********************************/
void clear_llist(linkList *L){
    linkList p = (*L)->next;
    while(p){
        (*L)->next = p->next;
        free(p);
        p = (*L)->next;
    }
}//clear_llist  √
/****************************4、求表长*********************************/
int length_llist(linkList L) {
    int length;
    linkList p = L->next;
    for (length = 0; p; length++)
        p = p->next;
    return length;
}//length_llist  √
/****************************5、查表空*********************************/
void empty_llist(linkList L){
    if(length_llist(L)==0) {printf("该链表空!\n");}
    else if(length_llist(L)>0) {printf("该链表不空！\n");}
    else printf("空链表判断出错！\n");
}//empty_llist  √
/****************************6、取元素（取表中某一位置的元素）*********************************/
Status getelem_llist(linkList L, int i, int* e) {            //纯C语言不支持引用参数，C++才支持
    if (i<1 || i>length_llist(L)) {*e= endMark; return ERROR;}                  //若i<1或者i>链表长度，则是非法的，直接报错
    //linkList p = L->next;
    //for(int j=1; p && j<i; j++)             //若链表不够长，则计数到i之前就会有p==NULL，跳出循环；若链表够长，则计数到i才会跳出
    // p = p->next;
    // if(!p) return ERROR;                    //若是因为链表不够长，则报错
    //*e = p->data;                           //若链表够长，则将下表为i的值返回给e
    //return OK;
    linkList p = L->next;
    for (int j = 1; j < i; j++)
        p = p->next;
    *e = p->data;
    return OK;
}//getelem_llist  √
/****************************7、在表中定位某个元素（取第一个满足的）*********************************/
int locate_llist(linkList L, int e){
    int i;
    linkList p;
    for(i=1, p = L->next; p && p->data!=e; i++, p=p->next);
    if(!p) return endMark;        //因为位置下标不可能小于1，所以返回-731表示在链表中没有定位到
    else return i;
}//locate_llist  √
/****************************8、求前驱*********************************/
Status prior_llist(linkList L, int i, elemType *e){
    if (i<=1 || i>length_llist(L)) {*e= endMark; return ERROR;}
    int j;
    linkList p;
    for(j=1, p=L->next; j<i-1;j++, p=p->next);
    *e = p->data;
    return OK;
}//prior_llist  √
/****************************9、求后继*********************************/
Status next_llist(linkList L, int i, elemType *e){
    if (i<1 || i>=length_llist(L)) {*e= endMark; return ERROR;}
    int j;
    linkList p;
    for(j=1, p=L->next; j<i+1;j++, p=p->next);
    *e = p->data;
    return OK;
}//next_llist  √
/****************************10、插入元素*********************************/
Status insert_llist(linkList *L, int e, int i) {
    if (i<1 || i>length_llist(*L) + 1) return ERROR;            //插入位置只能落在区间[1, length_llist(L)+1]内
    linkList E = (LNode *)malloc(sizeof(LNode));
    E->data = e;                    //必须得用linkList E = (LNode *)malloc(sizeof(LNode));
    // 若使用LNode，则生成的是局部变量，在函数结束后其内存会被释放
    linkList p = *L;
    for (int j = 0; j < i - 1; j++)
        p = p->next;                        //循环结束后，p指向下标为i-1的结点
    E->next = p->next;                      //使E的下一个结点为原来下标i的结点
    p->next = E;
    return OK;
}//insert_llist             插在第1个和最后一个后面是否可以？  √
/****************************11、删除元素*********************************/
Status delete_llist(linkList *L, int i, int* e) {
    if (i<1 || i>length_llist(*L)) return ERROR;
    linkList p = *L;
    for (int j = 0; j < i - 1; j++)
        p = p->next;
    linkList q = p->next; *e = q->data;
    p->next = q->next; free(q);             //释放掉这个结点的内存
    return OK;
}//delete_llist  √
/****************************12、手动输入创建单链表————头插法*********************************/
Status head_create_llist(linkList *L) {
    init_llist(L);                  //申请头结点
    linkList s;
    elemType e;
    printf("创建表，请按序输入数据：");
    scanf_s("%d", &e);
    while (e != endMark) {
        s = (LNode*)malloc(sizeof(LNode)); if (!s) return ERROR;
        s->data = e; s->next = (*L)->next;
        (*L)->next = s;
        scanf_s("%d", &e);
    }
    return OK;
}//head_create_llist  √
/****************************13、手动输入创建单链表————尾插法*********************************/
Status tail_create_llist(linkList *L) {
    init_llist(L);
    linkList s, p = *L;              //p总指向链表的尾结点
    elemType e;
    printf("创建表，请按序输入数据：");
    scanf_s("%d", &e);
    while (e != endMark) {
        s = (LNode*)malloc(sizeof(LNode)); if (!s) return ERROR;
        s->data = e; s->next = p->next;
        p->next = s;
        p = s;
        scanf_s("%d", &e);
    }
    return OK;
}//tail_create_llist  √
/****************************14、逆置链表————头插法*********************************/
Status reverse1_llist(linkList *L) {
    if ((*L)->next == NULL) return ERROR;
    linkList p, q;
    p = (*L)->next;
    (*L)->next = NULL;
    while (p) {
        q = p->next;
        p->next = (*L)->next;
        (*L)->next = p;
        p = q;
    }
    return OK;
}//reverse1_llist  √
/*************15、逆置链表————将所有结点的next指针逆转，最后再让头节点指向逆置前的最后一个结点*****************/
Status reverse2_llist(linkList *L) {
    if ((*L)->next == NULL) return ERROR;
    linkList p, q, r;
    p = (*L)->next; q = p->next;
    p->next = NULL;
    while (q) {
        r = q->next;
        q->next = p;
        p = q; q = r;
    }
    (*L)->next = p;
    return OK;
}//reverse2_llist  √
/****************************16、遍历链表*********************************/
void traverse_llist(linkList L){
    linkList p;
    int j;
    for(j=1, p=L->next; p;j++, p=p->next )
        printf("%d ", p->data);
    printf("\n");
}//traverse_llist  √
//不带头节点的没做QVQ


int main() {
    linkList L;
    int i, e;
    printf("//1、init测试\n");
    tail_create_llist(&L);
    printf("//2、length测试\n");
    printf("该链表的长度：%d\n\n", length_llist(L));
    printf("//3、tail/head测试\n");
    printf("//4、traverse测试\n");
    printf("//该链表的元素：\n");
    traverse_llist(L);
    printf("\n");
    printf("//5、empty测试\n");
    empty_llist(L);
    printf("\n");

    printf("//6、insert测试\n");
    printf("你希望插入的数据：");
    scanf_s("%d", &e);
    printf("你希望插入的位置：");
    scanf_s("%d", &i);
    insert_llist(&L, e, i);
    printf("插入结束后链表的长度：%d\n", length_llist(L));
    printf("插入结束后的链表：");
    traverse_llist(L);
    printf("\n\n");

    printf("//7、delete测试\n");
    printf("你希望删除数据的下标：");
    scanf_s("%d", &i);
    delete_llist(&L, i, &e);
    printf("被删除的数据：%d\n", e);
    printf("删除结束后链表的长度：%d\n", length_llist(L));
    printf("删除结束后的链表：");
    traverse_llist(L);
    printf("\n");

    printf("//8、getelem测试\n");
    printf("\n");
    printf("你希望查找的位置：");
    scanf_s("%d", &i);
    getelem_llist(L, i, &e);
    printf("第%d位数据是：%d\n", i, e);

    printf("//9、locate测试\n");
    printf("你希望查找的数据：");
    scanf_s("%d", &e);
    i = locate_llist(L, e);
    printf("数据%d在链表的位置：%d\n\n", e, i);

    printf("//10、reverse1/2测试\n");
    reverse2_llist(&L);
    printf("反转结束后的链表：");
    traverse_llist(L);
    printf("\n");

    printf("//11、prior测试\n");
    printf("你希望查找哪一位的前驱：");
    scanf_s("%d", &i);
    prior_llist(L, i, &e);
    printf("第%d位数据的前驱：%d\n\n", i, e);

    printf("//12、next测试\n");
    printf("你希望查找哪一位的后继：");
    scanf_s("%d", &i);
    next_llist(L, i, &e);
    printf("第%d位数据的后继：%d\n\n", i, e);

    printf("//13、clear/destroy测试\n");
    clear_llist(&L);
    //printf("%p\n", L);
    empty_llist(L);

    return 0;
}