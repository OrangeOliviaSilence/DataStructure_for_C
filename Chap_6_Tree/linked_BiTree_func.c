/************二叉树的链式存储结构************/
/************大量的使用递归算法************/
#include "stdio.h"
#include "malloc.h"
#include "stdlib.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define endMark ' '
typedef int Status;
typedef char elemType;

//二叉树结点的第1种定义方式————二叉链表
typedef struct BiTNode1{
    elemType data;
    struct BiTNode1 *lchild, *rchild;
}BiTNode1, *BiTree1;        //BiTree表示根指针

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

/**1.1、初始化空二叉树
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

/**1.2、后序销毁二叉树
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

/**1.3、先序创建二叉树
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

/**1.4、清空二叉树
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

/**1.5、查空二叉树
 * 若所有节点的data都为0，则空
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

/**1.6、查二叉树深度
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

/**1.17、先序遍历树
 *
 * @param T
 */
void preOrderTraverseBT(BiTree1 T){
    if(T==NULL) return;
    printf("%c ", T->data);
    preOrderTraverseBT(T->lchild);
    preOrderTraverseBT(T->rchild);
}//preOrderTraverseBT   √

/**1.18、中序遍历树
 *
 * @param T
 */
void inOrderTraverseBT(BiTree1 T){
    if(T==NULL) return;
    inOrderTraverseBT(T->lchild);
    printf("%c ", T->data);
    inOrderTraverseBT(T->rchild);
}//inOrderTraverseBT   √

/**1.19、后序遍历树
 *
 * @param T
 */
void postOrderTraverseBT(BiTree1 T){
    if(T==NULL) return;
    postOrderTraverseBT(T->lchild);
    postOrderTraverseBT(T->rchild);
    printf("%c ", T->data);
}//postOrderTraverseBT   √

/*****************1.20、层次遍历树*******************/
//TODO levelTraverse

/**1.21、求二叉树节点数
 *
 * @param T
 * @return nodeNumber
 */
int nodeNumBiTree(BiTree1 T){
    if(T==NULL) return 0;
    int i = nodeNumBiTree(T->lchild);
    int j = nodeNumBiTree(T->rchild);
    return i+j+1;
}//nodeNumBiTree   √
/*****************1.22、求二叉树叶子数*******************/

/*****************1.23、互换二叉树的左右子树*******************/

/*****************1.24、求某个节点的所在层次*******************/

/*****************1.25、求某个节点的所在层次*******************/

/*****************1.26、互换二叉树的左右子树*******************/

/*****************1.27、复制二叉树*******************/

int main(){
    BiTree1 T;
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

    if(isEmptyBiTree(T) > 0){
        printf("该树非空！");
        printf("该树深度：%d\n", depthBiTree(T));
        printf("节点个数：%d\n\n", nodeNumBiTree(T));
    }
    else printf("该树空！\n\n");

    printf("--对该树进行clear\n");
    clearBiTree(&T);
    if(isEmptyBiTree(T) > 0){
        printf("该树非空！");
        printf("该树深度：%d\n", depthBiTree(T));
        printf("节点个数：%d\n\n", nodeNumBiTree(T));
    }
    else {
        printf("该树空！");
        printf("该树深度：%d\n", depthBiTree(T));
        printf("节点个数：%d\n\n", nodeNumBiTree(T));
    }

    printf("--对该树进行destroy\n");
    destroyBiTree(&T);
    if(isEmptyBiTree(T) > 0){
        printf("该树非空！");
        printf("该树深度：%d\n", depthBiTree(T));
        printf("节点个数：%d\n", nodeNumBiTree(T));
    }
    else {
        printf("该树空！");
        printf("该树深度：%d\n", depthBiTree(T));
        printf("节点个数：%d\n", nodeNumBiTree(T));
    }
}
