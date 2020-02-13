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
typedef int status;			//������ʾ����ִ�н����״��������˵����һ��ֵ����֤�������Ƿ�ִ�гɹ�
/******************���Ա�Ķ�̬����˳��洢�ṹ***********************/
typedef struct
{
    int* elem;			//˳���Ļ���ַ
    int length;			//˳���ĳ���
    int listsize;		//˳���Ĵ�С����sizeof()Ϊ��׼��
}sqlist;
/***********************1��˳����ʼ������****************************/
status init_sqlist(sqlist &L)
{
    L.elem = (int*)malloc(LIST_INIT_SIZE * sizeof(int));//����void *�͵�ָ�루void *,��ʾδȷ�����͵�ָ�룩
    //void *���Ϳ���ǿתΪ�κ��������͵ĵ�ָ�룬��free���
    //malloc��free��C�ģ�new��delete������[]����C++��
    //malloc���ص�ָ����void *���ͣ���new���ص�ָ����������ռ������
    if (!L.elem) return ERROR;
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}
/***********************2������˳�����****************************/
status destroy_sqlist(sqlist &L)
{
    free(L.elem); L.elem = NULL;
    L.length = L.listsize = 0;
    return OK;
}
/***************************3�����˳���*******************************/
status clear_sqlist(sqlist& L)
{
    L.length = 0;
    return OK;
}
/****************************4������Ƿ��********************************/
status empty_sqlist(sqlist L)
{
    if (L.length == 0) return TRUE;
    else if (L.length > 0) return FALSE;
    else return INFEASIBLE;
}
/****************************5�����********************************/
int length_sqlist(sqlist L)
{
    return L.length;
}
/************************6��ȡ���е�i��Ԫ�أ��±�Ϊ0�߳�Ϊ��1������i = 1��**************************/
status get_sqlist_elem(sqlist L, int i, int &e)
{
    if (i>L.length || i<1) return ERROR;
    e = *(L.elem + i - 1);
    return OK;
}
/***********************7��˳����Ԫ��******************************/
int locate_sqlist_elem(sqlist L, int e)
{
    int* p = L.elem, i;
    for (i = 1; *p != e && i <= L.length;) { p++; i++; }
    return (i <= L.length ? i : 0);
}
/*****************************8����ǰ��********************************/
status prior_sqlist(sqlist L, int i, int &e)
{
    if (i <= 1 || i > L.length) return ERROR;
    e = *(L.elem + i - 2);
    return OK;
}
/*****************************9������********************************/
status next_sqlist(sqlist L, int i, int &e)
{
    if (i < 1 || i >= L.length) return ERROR;
    e = *(L.elem + i);
    return OK;
}
/*****************************10��ǰ��Ԫ��********************************/
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
/*****************************11��ɾ��Ԫ��********************************/
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
/*****************************12��������********************************/
/*****************************13�����������±�s->t��Ԫ��********************************/
void invert(int arr[], int s, int t)
{
    int j;
    for (int i = 0; i < (s+t)/2; i++) { j = arr[i+s]; arr[i+s] = arr[t-i]; arr[t-i] = j; }
}
/*****************************14������˳����е�����Ԫ��********************************/
void invert_sqlist(sqlist &L)
{ invert(L.elem, 0, L.length - 1); }
/*****************************15��sqlistǰm��Ԫ�����L.length - m��Ԫ�ػ���********************************/
status exchange_sqlist(sqlist& L, int m)
{
    if (m<1 || m>=L.length) return ERROR;
    invert(L.elem, 0, m-1);
    invert(L.elem, m, L.length-1);
    invert(L.elem, 0, L.length-1);
    return OK;
}
/*****************************16��sqlistA��Bʵ����������������sqlistC�У�********************************/
sqlist and_sqlist(sqlist A, sqlist B)
{
    sqlist C; init_sqlist(C);
    bool flag = 0;			//��־λ��A��ĳһ��ֵ��B������ֵ�Ƚ�һ�飬����������ȵ����������1����֮������Ϊ0
    int num = 1;			//���ڸ�˳���C����insert_sqlist()���β�
    for (int i = 0; i < A.length; i++)
    {
        for (int j = 0; j < B.length; j++) { if (*(A.elem + i) == *(B.elem + j)) flag = 1; }
        if (!flag) { insert_sqlist(C, *(A.elem + i), num); num++; }
        flag = 0;
    }

    int e;			//û��ʵ�����ã�ֻ������������delete_sqlist()�������β�
    for (int i = 0; i < C.length; i++)
        for (int j = i+1; j < C.length; j++)
        {
            if (*(C.elem + i) == *(C.elem + j))
            {
                delete_sqlist(C, j, e);
                j--;			//��Ϊ˳������ˣ�ԭ���±�j+1����ֵ�Ƶ��˵�jλ��
                //����Ϊ���´ν���ѭ��ʱ����Ȼ��û�б��ǰʱ�±�j+1�����ݽ��бȽϣ���Ҫ��j--�Լ�һ��
                //����ͻ��û�б��ǰ�±�j+2�����ݽ��бȽ�
            }
        }
    return C;
}
/*****************************17��sqlist Lʵ�������ظ�Ԫ�صĲ���********************************/
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
/********************************************������*************************************************/
int main()
{
    sqlist L, M, N;
    init_sqlist(L); init_sqlist(M); init_sqlist(N);
    for (int i = 1; i <= LIST_INIT_SIZE / 4; i++) { insert_sqlist(L, i, i); }
    printf("˳����� = %d\n", length_sqlist(L));
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