#include<stdio.h>
#include<malloc.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define LIST_INIT_SIZE 100
#define LIST_INCREMENT 10
typedef int status;			//用来表示函数执行结果的状况，或者说返回一个值来验证本函数是否执行成功
/******************线性表的动态分配顺序存储结构***********************/
typedef struct
{
    int* elem;			//顺序表的基地址
    int length;			//顺序表的长度
    int listsize;		//顺序表的大小（以sizeof()为基准）
}sqlist;
/***********************1、顺序表初始化函数****************************/
status init_sqlist(sqlist &L)
{
    L.elem = (int*)malloc(LIST_INIT_SIZE * sizeof(int));//返回void *型的指针（void *,表示未确定类型的指针）
    //void *类型可以强转为任何其他类型的的指针，和free配对
    //malloc和free是C的，new和delete（包括[]）是C++的
    //malloc返回的指针是void *类型，而new返回的指针是它分配空间的类型
    if (!L.elem) return ERROR;
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}
/***********************2、销毁顺序表函数****************************/
status destroy_sqlist(sqlist &L)
{
    free(L.elem); L.elem = NULL;
    L.length = L.listsize = 0;
    return OK;
}
/***************************3、清空顺序表*******************************/
status clear_sqlist(sqlist& L)
{
    L.length = 0;
    return OK;
}
/****************************4、查表是否空********************************/
status empty_sqlist(sqlist L)
{
    if (L.length == 0) return TRUE;
    else if (L.length > 0) return FALSE;
    else return INFEASIBLE;
}
/****************************5、求表长********************************/
int length_sqlist(sqlist L)
{
    return L.length;
}
/************************6、取表中第i个元素（下表为0者称为第1个，即i = 1）**************************/
status get_sqlist_elem(sqlist L, int i, int &e)
{
    if (i>L.length || i<1) return ERROR;
    e = *(L.elem + i - 1);
    return OK;
}
/***********************7、顺序表查元素******************************/
int locate_sqlist_elem(sqlist L, int e)
{
    int* p = L.elem, i;
    for (i = 1; *p != e && i <= L.length;) { p++; i++; }
    return (i <= L.length ? i : 0);
}
/*****************************8、求前驱********************************/
status prior_sqlist(sqlist L, int i, int &e)
{
    if (i <= 1 || i > L.length) return ERROR;
    e = *(L.elem + i - 2);
    return OK;
}
/*****************************9、求后继********************************/
status next_sqlist(sqlist L, int i, int &e)
{
    if (i < 1 || i >= L.length) return ERROR;
    e = *(L.elem + i);
    return OK;
}
/*****************************10、前插元素********************************/
status insert_sqlist(sqlist &L, int e, int i)
{
    if (i<1 || i > L.length + 1) return ERROR;
    if (L.length >= L.listsize)
    {
        int* new_base;
        L.listsize += LIST_INCREMENT;
        new_base = (int *)realloc(L.elem, L.listsize * sizeof(int));
        if (!L.elem) return OVERFLOW;
        L.elem = new_base;
    }
    int* p;
    for (p = L.elem + L.length - 1; p >= L.elem + i - 1; p--)
    {
        *(p + 1) = *p;
    }
    *(L.elem + i - 1) = e;
    L.length++;
    return OK;
}
/*****************************11、删除元素********************************/
status delete_sqlist(sqlist& L, int i, int &e)
{
    if (i<1 || i>L.length || i>L.listsize) return ERROR;
    e = *(L.elem + i - 1);
    int* p;
    for (p = L.elem + i - 1; p < L.elem + L.length - 1; p++)
    {
        *(p) = *(p + 1);
    }
    *(L.elem + L.length - 1) = NULL;
    L.length--;
    return OK;
}
/*****************************12、遍历表********************************/
/*****************************13、逆置数组下标s->t的元素********************************/
void invert(int arr[], int s, int t)
{
    int j;
    for (int i = 0; i < (s+t)/2; i++) { j = arr[i+s]; arr[i+s] = arr[t-i]; arr[t-i] = j; }
}
/*****************************14、逆置顺序表中的所有元素********************************/
void invert_sqlist(sqlist &L)
{ invert(L.elem, 0, L.length - 1); }
/*****************************15、sqlist前m个元素与后L.length - m个元素互换********************************/
status exchange_sqlist(sqlist& L, int m)
{
    if (m<1 || m>=L.length) return ERROR;
    invert(L.elem, 0, m-1);
    invert(L.elem, m, L.length-1);
    invert(L.elem, 0, L.length-1);
    return OK;
}
/*****************************16、sqlistA和B实现与操作（结果置于sqlistC中）********************************/
sqlist and_sqlist(sqlist A, sqlist B)
{
    sqlist C; init_sqlist(C);
    bool flag = 0;			//标志位。A中某一个值和B中所有值比较一遍，若其中有相等的情况，则置1；反之，保持为0
    int num = 1;			//用于给顺序表C调用insert_sqlist()作形参
    for (int i = 0; i < A.length; i++)
    {
        for (int j = 0; j < B.length; j++) { if (*(A.elem + i) == *(B.elem + j)) flag = 1; }
        if (!flag) { insert_sqlist(C, *(A.elem + i), num); num++; }
        flag = 0;
    }

    int e;			//没有实际作用，只是用于作调用delete_sqlist()函数的形参
    for (int i = 0; i < C.length; i++)
        for (int j = i+1; j < C.length; j++)
        {
            if (*(C.elem + i) == *(C.elem + j))
            {
                delete_sqlist(C, j, e);
                j--;			//因为顺序表变短了，原本下标j+1的数值移到了第j位。
                //所以为了下次进入循环时，仍然和没有变短前时下标j+1的数据进行比较，需要让j--自减一次
                //否则就会和没有变短前下标j+2的数据进行比较
            }
        }
    return C;
}
/*****************************17、sqlist L实现消除重复元素的操作********************************/
void purge_sqlist(sqlist &L)
{
    int e;
    for (int i = 0; i < L.length; i++)
        for (int j = i+1; j < L.length; j++)
        {
            if (*(L.elem + i) == *(L.elem + j))
            {
                delete_sqlist(L, j, e);
                j--;
            }
        }
}
/********************************************主函数*************************************************/
int main()
{
    sqlist L, M, N;
    init_sqlist(L); init_sqlist(M); init_sqlist(N);
    for (int i = 1; i <= LIST_INIT_SIZE / 4; i++) { insert_sqlist(L, i, i); }
    printf("顺序表长度 = %d\n", length_sqlist(L));
    printf("[SqList L] = ");
    for (int i = 0; i < length_sqlist(L); i++) { printf("%d ", *(L.elem + i)); }
    printf("\n");
    for (int i = 1; i <= LIST_INIT_SIZE / 4 - 12; i++) { insert_sqlist(M, 2, i); }
    printf("[SqList M] = ");
    for (int i = 0; i < length_sqlist(M); i++) { printf("%d ", *(M.elem + i)); }
    printf("\n");
    N = and_sqlist(L, M);
    printf("[SqList N] = ");
    for (int i = 0; i < length_sqlist(N); i++) { printf("%d ", *(N.elem + i)); }
    printf("\n");
    purge_sqlist(M);
    printf("[NEW SqList M] = ");
    for (int i = 0; i < length_sqlist(M); i++) { printf("%d ", *(M.elem + i)); }
    printf("\n");

    return 0;
}