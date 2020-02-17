/************二叉树的链式存储结构************/
/************大量的使用递归算法************/
#include "stdio.h"
#include "malloc.h"
#include "stdlib.h"
#include "q4BiTree.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

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
    if(*T == NULL) exit(ERROR);
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

/*****************1.8、读二叉树中某个节点的值*******************/

/*****************1.9、对二叉树中某个节点赋值*******************/

/*****************1.10、查某个结点的父节点*******************/

/*****************1.11、查某个节点的左孩子*******************/

/*****************1.12、查某个节点的右孩子*******************/

/*****************1.13、查某个节点的左兄弟*******************/

/*****************1.14、查某个节点的右兄弟*******************/

/*****************1.15、*******************/

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
/*****************1.24、求某个节点的所在层次*******************/
//需要层次遍历得到节点按层次遍历的序号，然后由序号，用公式计算得到所在层次
int levelBiTree(BiTree1 T){

}
/*****************1.25、复制二叉树*******************/

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
