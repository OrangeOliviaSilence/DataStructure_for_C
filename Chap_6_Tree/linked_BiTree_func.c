/************����������ʽ�洢�ṹ************/
/************������ʹ�õݹ��㷨************/
#include "stdio.h"
#include "malloc.h"
#include "stdlib.h"
#include "math.h"       //Ϊ�˽��ж�������
#include "q4BiTree.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
//#define OVERFLOW -2

#define endMark '\\'
typedef int Status;
typedef char elemType;

//���������ĵ�1�ֶ��巽ʽ����������������
/*typedef struct BiTNode1{
    elemType data;
    struct BiTNode1 *lchild, *rchild;
}BiTNode1, *BiTree1;        //BiTree��ʾ��ָ��*/

//���������ĵ�2�ֶ��巽ʽ�����������������������˼����˵���Ǵ�����������
typedef struct BiTNode2{        //�ȶ�������Ľ�����һ������ָ��
    elemType data;
    struct BiTNode2 *lchild, *rchild, *parent;
}BiTNode2, *BiTree2;

/***
 * ��ӡ������
 * @param e
 * @return Status
 */
Status visit(elemType e){
    printf("%c ", e);
    return OK;
}//visit

/*****************1.1����ʼ���ն�����*******************/
/**
 * �����������ĸ�
 * @param *T
 * @return Status
 */
Status initBiTree(BiTree1 *T){
    *T = (BiTNode1*)malloc(sizeof(BiTNode1));
    if(*T == NULL) exit(OVERFLOW);
    (*T)->lchild = (*T)->rchild = NULL;     //TODO �п���������
    return OK;
}//initBiTree   ��
/*****************1.2���������ٶ�����*******************/
/**
 *�ú�������ķ�������
 * @param *T
 * @return Status
 */
Status destroyBiTree(BiTree1 *T){//TODO �������ָ���ָ�����Σ�
    if(*T == NULL) return ERROR;
    destroyBiTree(&((*T)->lchild));
    destroyBiTree(&((*T)->rchild));
    free(*T);
    *T = NULL;
    return OK;
}//destroyBiTree   ��
/*****************1.3�����򴴽�������*******************/
/**
 *����������ķ�������
 * @param *T
 * @return Status
 */
Status createBiTree(BiTree1 *T){
    elemType data;
    scanf("%c", &data);
    if(data != endMark){
        initBiTree(T);
        (*T)->data = data;
        createBiTree(&((*T)->lchild));
        createBiTree(&((*T)->rchild));
    }//if
    else (*T) = NULL;
    return OK;
}//createBiTree   ��
/*****************1.4����ն�����*******************/
/**
 *�������������ɾ�����Ľ�㣬��ʹ����data = 0
 * @param T
 * @return Status
 */
Status clearBiTree(BiTree1 *T){
    if(*T==NULL) return ERROR;
    (*T)->data = 0;
    clearBiTree(&((*T)->lchild));
    clearBiTree(&((*T)->rchild));
    return OK;
}//clearBiTree   ��
/*****************1.5����ն�����*******************/
/**
 * �˴��Ŀղ���˵��û�нڵ㡣�������нڵ㣬���������нڵ㶼��data==0ʱ��������
 * �����������ֵ!=0����ǿ�
 * @param T
 * @return Status
 */
Status isEmptyBiTree(BiTree1 T){
    if(T == NULL) return 0;
    int i = isEmptyBiTree(T->lchild);
    int j = isEmptyBiTree(T->rchild);
    return T->data!=0 ? (i+j+1) : (i+j);
}//isEmptyBiTree   ��
/*****************1.6������������*******************/
/**
 * ������������
 * @param T
 * @return depth
 */
int depthBiTree(BiTree1 T){
    if(T==NULL) return 0;
    int dl = depthBiTree(T->lchild);    //dl = depthLeft
    int dr = depthBiTree(T->rchild);    //dr = depthRight
    return 1+(dl > dr ? dl : dr);
}//depthBiTree   ��
/*****************1.7��������������*******************/

//TODO rootBiTree

//TODO 1.8~1.16���ѵ㶼���ڡ��ڶ���������ζ�λһ���ڵ㣿��
/*****************1.8������������ĳ���ڵ��ֵ*******************/
void nodeDataBiTree(BiTree1 T, BiTNode1 *node, elemType *data){     //data��ֵ��ʹ��ǰӦ���ȸ�ֵ��0��
    if(!T || *data!='0') return;
    if(T == node) *data = T->data;
    nodeDataBiTree(T->lchild, node, data);
    nodeDataBiTree(T->rchild, node, data);
}//nodeDataBiTree
/*****************1.9���Զ�������ĳ���ڵ㸳ֵ*******************/
void assignDataBiTree(BiTree1 T, BiTNode1 *node, elemType data, _Bool *flag){
    //flag���ڱ�ʶ�Ƿ���ɸ�ֵ��flag==1���Ǹ�ֵ��ɣ���֮��δ���
    if(!T || *flag==1) return;
    if(T == node) {
        T->data = data;
        *flag = 1;
    }//if
    assignDataBiTree(T->lchild, node, data, flag);
    assignDataBiTree(T->rchild, node, data, flag);
}//assignDataBiTree
/*****************1.10����ĳ�����ĸ��ڵ�*******************/
void parentBiTree(BiTree1 T, BiTNode1 *node, BiTNode1 **ptr){ //ptr��ʹ��ǰӦ�ø�ֵNULL
    if(!T || *ptr!=NULL) return;
    if(T->lchild == node) *ptr = T;
    if(T->rchild == node) *ptr = T;
    parentBiTree(T->lchild, node, ptr);
    parentBiTree(T->rchild, node, ptr);
}//parentBiTree
/*****************1.11����ĳ���ڵ������*******************/
void leftChildBiTree(BiTree1 T, BiTNode1 *node, BiTNode1 **ptr){
    if(!T || *ptr!=NULL) return;
    if(T == node) *ptr = node->lchild;
    leftChildBiTree(T->lchild, node, ptr);
    leftChildBiTree(T->rchild, node, ptr);
}//leftChildBiTree
/*****************1.12����ĳ���ڵ���Һ���*******************/
void rightChildBiTree(BiTree1 T, BiTNode1 *node, BiTNode1 **ptr){
    if(!T || *ptr!=NULL) return;
    if(T == node) *ptr = node->rchild;
    rightChildBiTree(T->lchild, node, ptr);
    rightChildBiTree(T->rchild, node, ptr);
}//rightChildBiTree
/*****************1.13����ĳ���ڵ�����ֵ�*******************/

/*****************1.14����ĳ���ڵ�����ֵ�*******************/

/*****************1.15�����������ʽ�������Ľ��*******************/
int experssionBiTree(BiTree1 T){
    //��ǰ�ڵ�������ӽڵ�������Ƕ��գ���ǰ�ڵ��ŵ����������
    //��ô��ȡ��ǰ�ڵ�������ӽڵ�����������͵�ǰ�ڵ���������������õ�������ݹ鷵�ء�
    //�����ǰ�ڵ�������ӽڵ㶼�գ���ǰ�ڵ��ŵı�����ֵ������ֵ���ظ����ڵ㣨���ڵ��������������ɸ��ڵ������������ֽ�������
    if(!T->lchild && !T->rchild) return T->data;
    int i = experssionBiTree(T->lchild);
    int j = experssionBiTree(T->rchild);
    switch (T->data){
        case '+': return i+j; break;
        case '-': return i-j; break;
        case '*': return i*j; break;
        case '/': return i/j; break;
    }//switch
}//experssionBiTree
/*****************1.16��ɾ���ڵ����/������*******************/

/*****************1.17�����������*******************/
void preOrderTraverseBT(BiTree1 T){
    if(T==NULL) return;
    visit(T->data);
    preOrderTraverseBT(T->lchild);
    preOrderTraverseBT(T->rchild);
}//preOrderTraverseBT   ��
/*****************1.18�����������*******************/
void inOrderTraverseBT(BiTree1 T){
    if(T==NULL) return;
    inOrderTraverseBT(T->lchild);
    visit(T->data);
    inOrderTraverseBT(T->rchild);
}//inOrderTraverseBT   ��
/*****************1.19�����������*******************/
void postOrderTraverseBT(BiTree1 T){
    if(T==NULL) return;
    postOrderTraverseBT(T->lchild);
    postOrderTraverseBT(T->rchild);
    visit(T->data);
}//postOrderTraverseBT   ��
/*****************1.20����α�����*******************/
void levelOrderTraverseBT(BiTree1 T) {
    //����α����������㷨
    if(!T) return;           //����
    linkedQueue Q;
    initLinkedQueue(&Q);             //��ʼ���ն���Q
    //printf("\nQ.head==Q.tail ? %d", Q.head==Q.tail);
    enterLinkedQueue(&Q, T);        //�����
    while( !isEmptyLinkedQueue(Q) ) {
        deleteLinkedQueue(&Q, &T);    //��һ��ѭ��ʹ��ͷp����
        //printf("\nQ.head==Q.tail ? %d\n", Q.head==Q.tail);
        visit(T->data);     //����p
        if(T->lchild) enterLinkedQueue(&Q, T->lchild); //p���������
        if(T->rchild) enterLinkedQueue(&Q, T->rchild);  //p���Һ������
        //printf("%p %p ", Q.head->next->data, Q.head->next->next->data);
    }//while
}//levelOrderTraverseBT //ABC\\DE\G\\F\\\  //HDA\\C\B\\GF\E\\\
/*****************1.21����������ڵ���*******************/
int nodeNumBiTree(BiTree1 T){
    if(T==NULL) return 0;
    int i = nodeNumBiTree(T->lchild);
    int j = nodeNumBiTree(T->rchild);
    return i+j+1;
}//nodeNumBiTree   ��
/*****************1.22���������Ҷ����*******************/
int leafBiTree(BiTree1 T){
    if(T==NULL) return 0;
    int i = leafBiTree(T->lchild);
    int j = leafBiTree(T->rchild);
    return (!T->lchild && !T->rchild) ? i+j+1 : i+j;
        //����������ýڵ���Ҷ�ӽڵ�
}//leafBiTree   ��
/*****************1.23����������������������*******************/
Status exchangeChildTreeBT(BiTree1 *T){
    if(*T==NULL) return ERROR;      //�����û�нڵ㣬�򷵻�ERROR
    BiTree1 p;
    p = (*T)->lchild;
    (*T)->lchild = (*T)->rchild;
    (*T)->rchild = p;
    return OK;
}//exchangeChildTreeBT   ��
/*****************1.24���������������ú���ķ�����*******************/
void copyBiTree(BiTree1 *T2, BiTree1 T1){
    if(T1==NULL) *T2 = NULL;
    else {
        BiTNode1 *Lnode, *Rnode;
        copyBiTree(&Lnode, T1->lchild);
        copyBiTree(&Rnode, T1->rchild);
        initBiTree(T2);
        (*T2)->data = T1->data;
        (*T2)->lchild = Lnode;
        (*T2)->rchild = Rnode;
    }//else
}//copyBiTree   ��
/*****************1.25����ӡ�ڵ�����ڲ��*******************/
void levelBiTree(BiTree1 T, int *level){   //level�ĳ�ֵӦ��Ϊ0
    if(T == NULL) return;
    (*level)++;
    int level2 = *level;
    printf("%c\t%d\n", T->data, *level);
    levelBiTree(T->lchild, level);
    levelBiTree(T->rchild, &level2);
}//levelBiTree
/*****************1.25���������ʽ������*******************/
Status createExperssionBT(BiTree1 *T){
    elemType data;
    scanf("%c", &data);
    while(data != endMark){     //�����ǰ����Ĳ���endMark�������ǰ�ڵ����һ���ռ�
        (*T) = (BiTNode1*)malloc(sizeof(BiTNode1));
        if(!(*T)) exit(OVERFLOW);
        if(!isOperate(data)){   //����������������ýڵ�������ӽڵ�Ҫָ��NULL
            (*T)->data = data;
            (*T)->lchild = (*T)->rchild = NULL;
        }//if
        else{       //�������������Ը�������������ӽڵ�������в���
            (*T)->data = data;
            createExperssionBT(&((*T)->lchild));
            createExperssionBT(&((*T)->rchild));
        }//else
        return OK;
    }
}//createExperssionBT
/*****************1.26����ӡ��������������������Ҷ��·��*******************/
void printRouteBT(BiTree1 T, Stcak *S){
    if(!T) return;
    elemType e;
    pushStcak(S, T->data);
    if(!T->lchild && !T->rchild){   //�����ǰ�ڵ�����Ҷ�����ջ�ױ���һ��ջ��������ջ��Ԫ�س�ջ
        traverseStack(*S);
        popStack(&S, &e);
    }//if
    else {
        printRouteBT(T->lchild, S);
        printRouteBT(T->rchild, S);
    }//else
}//printRouteBT

int main(){
    BiTree1 T;
    printf("--1��������������\n");
    printf("�������ݣ�");
    createBiTree(&T);

    printf("�������������");
    preOrderTraverseBT(T);
    printf("\n");
    printf("�������������");
    inOrderTraverseBT(T);
    printf("\n");
    printf("�������������");
    postOrderTraverseBT(T);
    printf("\n");
    printf("��α���������");
    levelOrderTraverseBT(T);
    printf("\n");

    if(isEmptyBiTree(T) > 0){
        printf("�����ǿգ�");
        printf("������ȣ�%d\n", depthBiTree(T));
        printf("�ڵ������%d\n", nodeNumBiTree(T));
        printf("Ҷ�ӽڵ������%d\n\n", leafBiTree(T));

    }
    else printf("�����գ�\n\n");

    printf("��ӡ���������ڵ�Ĳ������\n");
    int level = 0;
    levelBiTree(T, &level);
    printf("\n");

    printf("--2��������������\n");
    exchangeChildTreeBT(&T);
    printf("�������������");
    preOrderTraverseBT(T);
    printf("\n");
    printf("�������������");
    inOrderTraverseBT(T);
    printf("\n");
    printf("�������������");
    postOrderTraverseBT(T);
    printf("\n\n");

    printf("--3���Ը�������clear\n");
    clearBiTree(&T);
    if(isEmptyBiTree(T) > 0){
        printf("�����ǿգ�");
        printf("������ȣ�%d\n", depthBiTree(T));
        printf("�ڵ������%d\n", nodeNumBiTree(T));
        printf("Ҷ�ӽڵ������%d\n\n", leafBiTree(T));

    }
    else {
        printf("�����գ�");
        printf("������ȣ�%d\n", depthBiTree(T));
        printf("�ڵ������%d\n", nodeNumBiTree(T));
        printf("Ҷ�ӽڵ������%d\n\n", leafBiTree(T));
    }

    printf("--4���Ը�������destroy\n");
    destroyBiTree(&T);
    if(isEmptyBiTree(T) > 0){
        printf("�����ǿգ�");
        printf("������ȣ�%d\n", depthBiTree(T));
        printf("�ڵ������%d\n", nodeNumBiTree(T));
        printf("Ҷ�ӽڵ������%d\n", leafBiTree(T));
    }
    else {
        printf("�����գ�");
        printf("������ȣ�%d\n", depthBiTree(T));
        printf("�ڵ������%d\n", nodeNumBiTree(T));
        printf("Ҷ�ӽڵ������%d\n", leafBiTree(T));
    }
}
