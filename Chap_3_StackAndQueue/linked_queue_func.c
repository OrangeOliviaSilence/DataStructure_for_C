/************单链队列（带头结点）************/
#include "stdio.h"
#include "stdlib.h"         //为了使用exit
#include "malloc.h"         //为了使用malloc、realloc、free等
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
    elemType data;          //数据域
    struct QNode* next;     //指针域
} QNode, *queuePtr;         //队列中的任意一个结点
typedef struct {
    queuePtr head;          //队列头指针
    queuePtr tail;          //队列尾指针
} linkedQueue;              //单链队列

/**
 * 在终端打印输出
 * @param e
 */
void visit(elemType e){
    printf("%d ", e);
}//visit

/*****************1.1、初始化队列*******************/
Status initLinkedQueue(linkedQueue *Q){
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
Status destroyLinkedQueue(linkedQueue *Q){
    queuePtr p = Q->head, q;
    while(p != NULL){
        q = p->next;
        free(p);
        p = q;
    }        //销毁和清空的区别在于，前者将头结点也free掉
    Q->head = Q->tail = NULL;
    return OK;
}//destroyLinkedQueue      √
/*****************1.4、清空队列*******************/
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
}//clearLinkedQueue      √
/*****************1.5、查队列空*******************/
Status isEmptyLinkedQueue(linkedQueue Q){
    if(Q.head == Q.tail) return TRUE;       //若队列的头指针、尾指针指向同一个结点，则队列空
    else return FALSE;
}//isEmptyLinkedQueue      √
/*****************1.6、队头数据*******************/
Status getHeadLinkedQueue(linkedQueue Q, elemType* e){
    if(isEmptyLinkedQueue(Q)) return ERROR;
    *e = Q.head->next->data;
    return OK;
}//getHeadLinkedQueue      √
/*****************1.7、数据入队列********S***********/
Status enterLinkedQueue(linkedQueue *Q, elemType e){
    queuePtr s = (QNode*)malloc(sizeof(QNode));
    if(s == NULL) exit(OVERFLOW);
    s->data = e;
    s->next = Q->tail->next;
    Q->tail->next = s;
    Q->tail = s;
    return OK;
}//enterLinkedQueue      √
/*****************1.8、数据出队列*******************/
Status deleteLinkedQueue(linkedQueue *Q, elemType *e){
    if(isEmptyLinkedQueue(*Q)) return ERROR;
    *e = Q->head->next->data;
    queuePtr p = Q->head->next;
    Q->head->next = p->next;
    free(p);
    return OK;
}//deleteLinkedQueue      √
/*TODO 使用malloc分配一段内存后，使用free函数释放内存时，
        若free的参数是这段内存的首地址，则销毁这一整段内存？
        若free的参数是这段内存中的某一块内存的地址，则是只销毁这个地址所对应的这一块地址吗？*/
/*****************1.9、遍历队列*******************/
Status traverseLinkedQueue(linkedQueue Q){
    if(isEmptyLinkedQueue(Q)) return ERROR;
    queuePtr p = Q.head->next;
    printf("--当前队列数据为：");
    while(p != NULL){
        visit(p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}//traverseLinkedQueue      √


int main(){
    linkedQueue Q;
    int e;
    printf("//1、init测试\n");
    initLinkedQueue(&Q);
    printf("\n");

    printf("//2、isEmpty测试\n");
    if(isEmptyLinkedQueue(Q)) printf("--该队列空！\n\n");
    else printf("该队列非空！\n\n");

    printf("//3、enter测试\n");
    printf("--请输入入队数据：");
    scanf_s("%d", &e);
    while(e!=endMark){
        enterLinkedQueue(&Q, e);
        scanf_s("%d", &e);
    }
    if(isEmptyLinkedQueue(Q)) printf("--该队列空！\n\n");
    else printf("--该队列非空！\n\n");

    printf("//4、traverse测试\n");
    traverseLinkedQueue(Q);
    printf("\n");

    printf("//5、length测试\n");
    printf("--当前队列的长为：%d\n\n", lengthLinkedQueue(Q));

    printf("//6、getHead测试\n");
    getHeadLinkedQueue(Q, &e);
    printf("--当前队头数据为：%d\n\n", e);

    printf("//7、delelte测试\n");
    deleteLinkedQueue(&Q, &e);
    printf("--被删除的数据为：%d\n", e);
    getHeadLinkedQueue(Q, &e);
    printf("--当前队头数据为：%d\n", e);
    printf("--当前队列的长为：%d\n\n", lengthLinkedQueue(Q));

    printf("//8、clear/destroy测试\n");
    clearLinkedQueue(&Q);
    if(isEmptyLinkedQueue(Q)) printf("--该队列空！\n\n");
    else printf("--该队列非空！\n\n");

}