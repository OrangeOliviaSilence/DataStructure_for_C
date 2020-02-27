/************二叉树的链式存储结构************/
/************大量的使用递归算法************/
#include "stdio.h"
#include "malloc.h"
#include "stdlib.h"
#include "math.h"       //为了进行对数运算
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

//二叉树结点的第1种定义方式————二叉链表
/*typedef struct BiTNode1{
    elemType data;
    struct BiTNode1 *lchild, *rchild;
}BiTNode1, *BiTree1;        //BiTree表示根指针*/

//二叉树结点的第2种定义方式————三叉链表（三叉的意思并非说这是代表三叉树）
typedef struct BiTNode2{        //比二叉链表的结点多了一个父亲指针
    elemType data;
    struct BiTNode2 *lchild, *rchild, *parent;
}BiTNode2, *BiTree2;

/***
 * 打印出数据
 * @param e
 * @return Status
 */
Status visit(elemType e){
    printf("%c ", e);
    return OK;
}//visit

/*****************1.1、初始化空二叉树*******************/
/**
 * 创建二叉树的根
 * @param *T
 * @return Status
 */
Status initBiTree(BiTree1 *T){
    *T = (BiTNode1*)malloc(sizeof(BiTNode1));
    if(*T == NULL) exit(OVERFLOW);
    (*T)->lchild = (*T)->rchild = NULL;     //TODO 有可能有问题
    return OK;
}//initBiTree   √
/*****************1.2、后序销毁二叉树*******************/
/**
 *用后序遍历的方法销毁
 * @param *T
 * @return Status
 */
Status destroyBiTree(BiTree1 *T){//TODO 如果不用指针的指针会如何？
    if(*T == NULL) return ERROR;
    destroyBiTree(&((*T)->lchild));
    destroyBiTree(&((*T)->rchild));
    free(*T);
    *T = NULL;
    return OK;
}//destroyBiTree   √
/*****************1.3、先序创建二叉树*******************/
/**
 *用先序遍历的方法创建
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
}//createBiTree   √
/*****************1.4、清空二叉树*******************/
/**
 *先序清空树，不删除树的结点，仅使结点的data = 0
 * @param T
 * @return Status
 */
Status clearBiTree(BiTree1 *T){
    if(*T==NULL) return ERROR;
    (*T)->data = 0;
    clearBiTree(&((*T)->lchild));
    clearBiTree(&((*T)->rchild));
    return OK;
}//clearBiTree   √
/*****************1.5、查空二叉树*******************/
/**
 * 此处的空不是说树没有节点。允许树有节点，当树的所有节点都有data==0时，此树空
 * 如果函数返回值!=0，则非空
 * @param T
 * @return Status
 */
Status isEmptyBiTree(BiTree1 T){
    if(T == NULL) return 0;
    int i = isEmptyBiTree(T->lchild);
    int j = isEmptyBiTree(T->rchild);
    return T->data!=0 ? (i+j+1) : (i+j);
}//isEmptyBiTree   √
/*****************1.6、查二叉树深度*******************/
/**
 * 后序遍历求深度
 * @param T
 * @return depth
 */
int depthBiTree(BiTree1 T){
    if(T==NULL) return 0;
    int dl = depthBiTree(T->lchild);    //dl = depthLeft
    int dr = depthBiTree(T->rchild);    //dr = depthRight
    return 1+(dl > dr ? dl : dr);
}//depthBiTree   √
/*****************1.7、查二叉树根结点*******************/

//TODO rootBiTree

//TODO 1.8~1.16的难点都在于“在二叉树中如何定位一个节点？”
/*****************1.8、读二叉树中某个节点的值*******************/
void nodeDataBiTree(BiTree1 T, BiTNode1 *node, elemType *data){     //data的值在使用前应该先赋值‘0’
    if(!T || *data!='0') return;
    if(T == node) *data = T->data;
    nodeDataBiTree(T->lchild, node, data);
    nodeDataBiTree(T->rchild, node, data);
}//nodeDataBiTree
/*****************1.9、对二叉树中某个节点赋值*******************/
void assignDataBiTree(BiTree1 T, BiTNode1 *node, elemType data, _Bool *flag){
    //flag用于标识是否完成赋值，flag==1则是赋值完成，反之还未完成
    if(!T || *flag==1) return;
    if(T == node) {
        T->data = data;
        *flag = 1;
    }//if
    assignDataBiTree(T->lchild, node, data, flag);
    assignDataBiTree(T->rchild, node, data, flag);
}//assignDataBiTree
/*****************1.10、查某个结点的父节点*******************/
void parentBiTree(BiTree1 T, BiTNode1 *node, BiTNode1 **ptr){ //ptr在使用前应该赋值NULL
    if(!T || *ptr!=NULL) return;
    if(T->lchild == node) *ptr = T;
    if(T->rchild == node) *ptr = T;
    parentBiTree(T->lchild, node, ptr);
    parentBiTree(T->rchild, node, ptr);
}//parentBiTree
/*****************1.11、查某个节点的左孩子*******************/
void leftChildBiTree(BiTree1 T, BiTNode1 *node, BiTNode1 **ptr){
    if(!T || *ptr!=NULL) return;
    if(T == node) *ptr = node->lchild;
    leftChildBiTree(T->lchild, node, ptr);
    leftChildBiTree(T->rchild, node, ptr);
}//leftChildBiTree
/*****************1.12、查某个节点的右孩子*******************/
void rightChildBiTree(BiTree1 T, BiTNode1 *node, BiTNode1 **ptr){
    if(!T || *ptr!=NULL) return;
    if(T == node) *ptr = node->rchild;
    rightChildBiTree(T->lchild, node, ptr);
    rightChildBiTree(T->rchild, node, ptr);
}//rightChildBiTree
/*****************1.13、查某个节点的左兄弟*******************/

/*****************1.14、查某个节点的右兄弟*******************/

/*****************1.15、后序计算表达式二叉树的结果*******************/
int experssionBiTree(BiTree1 T){
    //当前节点的左右子节点如果不是都空，则当前节点存放的是运算符，
    //那么求取当前节点的左右子节点的运算结果，和当前节点的运算符进行运算得到结果，递归返回。
    //如果当前节点的左右子节点都空，则当前节点存放的必是数值，则将数值返回给父节点（父节点必是运算符），由父节点的运算符对数字进行运算
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
/*****************1.16、删除节点的左/右子树*******************/

/*****************1.17、先序遍历树*******************/
void preOrderTraverseBT(BiTree1 T){
    if(T==NULL) return;
    visit(T->data);
    preOrderTraverseBT(T->lchild);
    preOrderTraverseBT(T->rchild);
}//preOrderTraverseBT   √
/*****************1.18、中序遍历树*******************/
void inOrderTraverseBT(BiTree1 T){
    if(T==NULL) return;
    inOrderTraverseBT(T->lchild);
    visit(T->data);
    inOrderTraverseBT(T->rchild);
}//inOrderTraverseBT   √
/*****************1.19、后序遍历树*******************/
void postOrderTraverseBT(BiTree1 T){
    if(T==NULL) return;
    postOrderTraverseBT(T->lchild);
    postOrderTraverseBT(T->rchild);
    visit(T->data);
}//postOrderTraverseBT   √
/*****************1.20、层次遍历树*******************/
void levelOrderTraverseBT(BiTree1 T) {
    //按层次遍历二叉树算法
    if(!T) return;           //空树
    linkedQueue Q;
    initLinkedQueue(&Q);             //初始化空队列Q
    //printf("\nQ.head==Q.tail ? %d", Q.head==Q.tail);
    enterLinkedQueue(&Q, T);        //根入队
    while( !isEmptyLinkedQueue(Q) ) {
        deleteLinkedQueue(&Q, &T);    //第一次循环使队头p出队
        //printf("\nQ.head==Q.tail ? %d\n", Q.head==Q.tail);
        visit(T->data);     //访问p
        if(T->lchild) enterLinkedQueue(&Q, T->lchild); //p的左孩子入队
        if(T->rchild) enterLinkedQueue(&Q, T->rchild);  //p的右孩子入队
        //printf("%p %p ", Q.head->next->data, Q.head->next->next->data);
    }//while
}//levelOrderTraverseBT //ABC\\DE\G\\F\\\  //HDA\\C\B\\GF\E\\\
/*****************1.21、求二叉树节点数*******************/
int nodeNumBiTree(BiTree1 T){
    if(T==NULL) return 0;
    int i = nodeNumBiTree(T->lchild);
    int j = nodeNumBiTree(T->rchild);
    return i+j+1;
}//nodeNumBiTree   √
/*****************1.22、求二叉树叶子数*******************/
int leafBiTree(BiTree1 T){
    if(T==NULL) return 0;
    int i = leafBiTree(T->lchild);
    int j = leafBiTree(T->rchild);
    return (!T->lchild && !T->rchild) ? i+j+1 : i+j;
        //此条件代表该节点是叶子节点
}//leafBiTree   √
/*****************1.23、互换二叉树的左右子树*******************/
Status exchangeChildTreeBT(BiTree1 *T){
    if(*T==NULL) return ERROR;      //如果树没有节点，则返回ERROR
    BiTree1 p;
    p = (*T)->lchild;
    (*T)->lchild = (*T)->rchild;
    (*T)->rchild = p;
    return OK;
}//exchangeChildTreeBT   √
/*****************1.24、拷贝二叉树（用后序的方法）*******************/
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
}//copyBiTree   √
/*****************1.25、打印节点的所在层次*******************/
void levelBiTree(BiTree1 T, int *level){   //level的初值应该为0
    if(T == NULL) return;
    (*level)++;
    int level2 = *level;
    printf("%c\t%d\n", T->data, *level);
    levelBiTree(T->lchild, level);
    levelBiTree(T->rchild, &level2);
}//levelBiTree
/*****************1.25、创建表达式二叉树*******************/
Status createExperssionBT(BiTree1 *T){
    elemType data;
    scanf("%c", &data);
    while(data != endMark){     //如果当前输入的不是endMark，则给当前节点分配一个空间
        (*T) = (BiTNode1*)malloc(sizeof(BiTNode1));
        if(!(*T)) exit(OVERFLOW);
        if(!isOperate(data)){   //如果不是运算符，则该节点的左右子节点要指向NULL
            (*T)->data = data;
            (*T)->lchild = (*T)->rchild = NULL;
        }//if
        else{       //如果是运算符，对该运算符的左右子节点继续进行操作
            (*T)->data = data;
            createExperssionBT(&((*T)->lchild));
            createExperssionBT(&((*T)->rchild));
        }//else
        return OK;
    }
}//createExperssionBT
/*****************1.26、打印二叉树中树根到所有树叶的路径*******************/
void printRouteBT(BiTree1 T, Stcak *S){
    if(!T) return;
    elemType e;
    pushStcak(S, T->data);
    if(!T->lchild && !T->rchild){   //如果当前节点是树叶，则从栈底遍历一遍栈，并且让栈顶元素出栈
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
    printf("--1、创建二叉树：\n");
    printf("输入数据：");
    createBiTree(&T);

    printf("先序遍历的树：");
    preOrderTraverseBT(T);
    printf("\n");
    printf("中序遍历的树：");
    inOrderTraverseBT(T);
    printf("\n");
    printf("后序遍历的树：");
    postOrderTraverseBT(T);
    printf("\n");
    printf("层次遍历的树：");
    levelOrderTraverseBT(T);
    printf("\n");

    if(isEmptyBiTree(T) > 0){
        printf("该树非空！");
        printf("该树深度：%d\n", depthBiTree(T));
        printf("节点个数：%d\n", nodeNumBiTree(T));
        printf("叶子节点个数：%d\n\n", leafBiTree(T));

    }
    else printf("该树空！\n\n");

    printf("打印该树各个节点的层次数：\n");
    int level = 0;
    levelBiTree(T, &level);
    printf("\n");

    printf("--2、交换左右子树\n");
    exchangeChildTreeBT(&T);
    printf("先序遍历的树：");
    preOrderTraverseBT(T);
    printf("\n");
    printf("中序遍历的树：");
    inOrderTraverseBT(T);
    printf("\n");
    printf("后序遍历的树：");
    postOrderTraverseBT(T);
    printf("\n\n");

    printf("--3、对该树进行clear\n");
    clearBiTree(&T);
    if(isEmptyBiTree(T) > 0){
        printf("该树非空！");
        printf("该树深度：%d\n", depthBiTree(T));
        printf("节点个数：%d\n", nodeNumBiTree(T));
        printf("叶子节点个数：%d\n\n", leafBiTree(T));

    }
    else {
        printf("该树空！");
        printf("该树深度：%d\n", depthBiTree(T));
        printf("节点个数：%d\n", nodeNumBiTree(T));
        printf("叶子节点个数：%d\n\n", leafBiTree(T));
    }

    printf("--4、对该树进行destroy\n");
    destroyBiTree(&T);
    if(isEmptyBiTree(T) > 0){
        printf("该树非空！");
        printf("该树深度：%d\n", depthBiTree(T));
        printf("节点个数：%d\n", nodeNumBiTree(T));
        printf("叶子节点个数：%d\n", leafBiTree(T));
    }
    else {
        printf("该树空！");
        printf("该树深度：%d\n", depthBiTree(T));
        printf("节点个数：%d\n", nodeNumBiTree(T));
        printf("叶子节点个数：%d\n", leafBiTree(T));
    }
}
