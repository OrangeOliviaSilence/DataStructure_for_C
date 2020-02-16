/************����������ʽ�洢�ṹ************/
/************������ʹ�õݹ��㷨************/
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

//���������ĵ�1�ֶ��巽ʽ����������������
typedef struct BiTNode1{
    elemType data;
    struct BiTNode1 *lchild, *rchild;
}BiTNode1, *BiTree1;        //BiTree��ʾ��ָ��

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

/**1.1����ʼ���ն�����
 * �����������ĸ�
 * @param *T
 * @return Status
 */
Status initBiTree(BiTree1 *T){
    *T = (BiTNode1*)malloc(sizeof(BiTNode1));
    if(*T == NULL) exit(ERROR);
    (*T)->lchild = (*T)->rchild = NULL;     //TODO �п���������
    return OK;
}//initBiTree   ��

/**1.2���������ٶ�����
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

/**1.3�����򴴽�������
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

/**1.4����ն�����
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

/**1.5����ն�����
 * �����нڵ��data��Ϊ0�����
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

/**1.6������������
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

/*****************1.8������������ĳ���ڵ��ֵ*******************/

/*****************1.9���Զ�������ĳ���ڵ㸳ֵ*******************/

/*****************1.10����ĳ�����ĸ��ڵ�*******************/

/*****************1.11����ĳ���ڵ������*******************/

/*****************1.12����ĳ���ڵ���Һ���*******************/

/*****************1.13����ĳ���ڵ�����ֵ�*******************/

/*****************1.14����ĳ���ڵ�����ֵ�*******************/

/*****************1.15��*******************/

/*****************1.16��ɾ���ڵ����/������*******************/

/**1.17�����������
 *
 * @param T
 */
void preOrderTraverseBT(BiTree1 T){
    if(T==NULL) return;
    printf("%c ", T->data);
    preOrderTraverseBT(T->lchild);
    preOrderTraverseBT(T->rchild);
}//preOrderTraverseBT   ��

/**1.18�����������
 *
 * @param T
 */
void inOrderTraverseBT(BiTree1 T){
    if(T==NULL) return;
    inOrderTraverseBT(T->lchild);
    printf("%c ", T->data);
    inOrderTraverseBT(T->rchild);
}//inOrderTraverseBT   ��

/**1.19�����������
 *
 * @param T
 */
void postOrderTraverseBT(BiTree1 T){
    if(T==NULL) return;
    postOrderTraverseBT(T->lchild);
    postOrderTraverseBT(T->rchild);
    printf("%c ", T->data);
}//postOrderTraverseBT   ��

/*****************1.20����α�����*******************/
//TODO levelTraverse

/**1.21����������ڵ���
 *
 * @param T
 * @return nodeNumber
 */
int nodeNumBiTree(BiTree1 T){
    if(T==NULL) return 0;
    int i = nodeNumBiTree(T->lchild);
    int j = nodeNumBiTree(T->rchild);
    return i+j+1;
}//nodeNumBiTree   ��
/*****************1.22���������Ҷ����*******************/

/*****************1.23����������������������*******************/

/*****************1.24����ĳ���ڵ�����ڲ��*******************/

/*****************1.25����ĳ���ڵ�����ڲ��*******************/

/*****************1.26����������������������*******************/

/*****************1.27�����ƶ�����*******************/

int main(){
    BiTree1 T;
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

    if(isEmptyBiTree(T) > 0){
        printf("�����ǿգ�");
        printf("������ȣ�%d\n", depthBiTree(T));
        printf("�ڵ������%d\n\n", nodeNumBiTree(T));
    }
    else printf("�����գ�\n\n");

    printf("--�Ը�������clear\n");
    clearBiTree(&T);
    if(isEmptyBiTree(T) > 0){
        printf("�����ǿգ�");
        printf("������ȣ�%d\n", depthBiTree(T));
        printf("�ڵ������%d\n\n", nodeNumBiTree(T));
    }
    else {
        printf("�����գ�");
        printf("������ȣ�%d\n", depthBiTree(T));
        printf("�ڵ������%d\n\n", nodeNumBiTree(T));
    }

    printf("--�Ը�������destroy\n");
    destroyBiTree(&T);
    if(isEmptyBiTree(T) > 0){
        printf("�����ǿգ�");
        printf("������ȣ�%d\n", depthBiTree(T));
        printf("�ڵ������%d\n", nodeNumBiTree(T));
    }
    else {
        printf("�����գ�");
        printf("������ȣ�%d\n", depthBiTree(T));
        printf("�ڵ������%d\n", nodeNumBiTree(T));
    }
}
