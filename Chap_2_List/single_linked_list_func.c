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
typedef struct LNode {           //���嵥������
    elemType data;              //���������
    struct LNode* next;         // ���ָ����ָ���߼��ϵ���һ�����
}LNode, * linkList;              //linkList�ṹ��ָ�����������ר��������ʾ��������ͷָ�����


//һ����ͷ�����������
/****************************1���������ʼ��*********************************/
Status init_llist(linkList *L) {
    *L = (LNode*)malloc(sizeof(LNode));
    if (!(*L)) return OVERFLOW;
    (*L)->next = NULL;
    return OK;
}//init_llist  ��
/****************************2�����ٱ�*********************************/
void destroy_llist(linkList  *L){
    linkList p = *L;
    while(*L){
        (*L)->next = p->next;
        free(p);
        p = p->next;
    }
}//destroy_llist  ��
/****************************3����ձ�*********************************/
void clear_llist(linkList *L){
    linkList p = (*L)->next;
    while(p){
        (*L)->next = p->next;
        free(p);
        p = (*L)->next;
    }
}//clear_llist  ��
/****************************4�����*********************************/
int length_llist(linkList L) {
    int length;
    linkList p = L->next;
    for (length = 0; p; length++)
        p = p->next;
    return length;
}//length_llist  ��
/****************************5������*********************************/
void empty_llist(linkList L){
    if(length_llist(L)==0) {printf("�������!\n");}
    else if(length_llist(L)>0) {printf("�������գ�\n");}
    else printf("�������жϳ���\n");
}//empty_llist  ��
/****************************6��ȡԪ�أ�ȡ����ĳһλ�õ�Ԫ�أ�*********************************/
Status getelem_llist(linkList L, int i, int* e) {            //��C���Բ�֧�����ò�����C++��֧��
    if (i<1 || i>length_llist(L)) {*e= endMark; return ERROR;}                  //��i<1����i>�����ȣ����ǷǷ��ģ�ֱ�ӱ���
    //linkList p = L->next;
    //for(int j=1; p && j<i; j++)             //�������������������i֮ǰ�ͻ���p==NULL������ѭ���������������������i�Ż�����
    // p = p->next;
    // if(!p) return ERROR;                    //������Ϊ�����������򱨴�
    //*e = p->data;                           //�������������±�Ϊi��ֵ���ظ�e
    //return OK;
    linkList p = L->next;
    for (int j = 1; j < i; j++)
        p = p->next;
    *e = p->data;
    return OK;
}//getelem_llist  ��
/****************************7���ڱ��ж�λĳ��Ԫ�أ�ȡ��һ������ģ�*********************************/
int locate_llist(linkList L, int e){
    int i;
    linkList p;
    for(i=1, p = L->next; p && p->data!=e; i++, p=p->next);
    if(!p) return endMark;        //��Ϊλ���±겻����С��1�����Է���-731��ʾ��������û�ж�λ��
    else return i;
}//locate_llist  ��
/****************************8����ǰ��*********************************/
Status prior_llist(linkList L, int i, elemType *e){
    if (i<=1 || i>length_llist(L)) {*e= endMark; return ERROR;}
    int j;
    linkList p;
    for(j=1, p=L->next; j<i-1;j++, p=p->next);
    *e = p->data;
    return OK;
}//prior_llist  ��
/****************************9������*********************************/
Status next_llist(linkList L, int i, elemType *e){
    if (i<1 || i>=length_llist(L)) {*e= endMark; return ERROR;}
    int j;
    linkList p;
    for(j=1, p=L->next; j<i+1;j++, p=p->next);
    *e = p->data;
    return OK;
}//next_llist  ��
/****************************10������Ԫ��*********************************/
Status insert_llist(linkList *L, int e, int i) {
    if (i<1 || i>length_llist(*L) + 1) return ERROR;            //����λ��ֻ����������[1, length_llist(L)+1]��
    linkList E = (LNode *)malloc(sizeof(LNode));
    E->data = e;                    //�������linkList E = (LNode *)malloc(sizeof(LNode));
    // ��ʹ��LNode�������ɵ��Ǿֲ��������ں������������ڴ�ᱻ�ͷ�
    linkList p = *L;
    for (int j = 0; j < i - 1; j++)
        p = p->next;                        //ѭ��������pָ���±�Ϊi-1�Ľ��
    E->next = p->next;                      //ʹE����һ�����Ϊԭ���±�i�Ľ��
    p->next = E;
    return OK;
}//insert_llist             ���ڵ�1�������һ�������Ƿ���ԣ�  ��
/****************************11��ɾ��Ԫ��*********************************/
Status delete_llist(linkList *L, int i, int* e) {
    if (i<1 || i>length_llist(*L)) return ERROR;
    linkList p = *L;
    for (int j = 0; j < i - 1; j++)
        p = p->next;
    linkList q = p->next; *e = q->data;
    p->next = q->next; free(q);             //�ͷŵ���������ڴ�
    return OK;
}//delete_llist  ��
/****************************12���ֶ����봴��������������ͷ�巨*********************************/
Status head_create_llist(linkList *L) {
    init_llist(L);                  //����ͷ���
    linkList s;
    elemType e;
    printf("�������밴���������ݣ�");
    scanf_s("%d", &e);
    while (e != endMark) {
        s = (LNode*)malloc(sizeof(LNode)); if (!s) return ERROR;
        s->data = e; s->next = (*L)->next;
        (*L)->next = s;
        scanf_s("%d", &e);
    }
    return OK;
}//head_create_llist  ��
/****************************13���ֶ����봴��������������β�巨*********************************/
Status tail_create_llist(linkList *L) {
    init_llist(L);
    linkList s, p = *L;              //p��ָ�������β���
    elemType e;
    printf("�������밴���������ݣ�");
    scanf_s("%d", &e);
    while (e != endMark) {
        s = (LNode*)malloc(sizeof(LNode)); if (!s) return ERROR;
        s->data = e; s->next = p->next;
        p->next = s;
        p = s;
        scanf_s("%d", &e);
    }
    return OK;
}//tail_create_llist  ��
/****************************14����������������ͷ�巨*********************************/
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
}//reverse1_llist  ��
/*************15���������������������н���nextָ����ת���������ͷ�ڵ�ָ������ǰ�����һ�����*****************/
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
}//reverse2_llist  ��
/****************************16����������*********************************/
void traverse_llist(linkList L){
    linkList p;
    int j;
    for(j=1, p=L->next; p;j++, p=p->next )
        printf("%d ", p->data);
    printf("\n");
}//traverse_llist  ��
//����ͷ�ڵ��û��QVQ


int main() {
    linkList L;
    int i, e;
    printf("//1��init����\n");
    tail_create_llist(&L);
    printf("//2��length����\n");
    printf("������ĳ��ȣ�%d\n\n", length_llist(L));
    printf("//3��tail/head����\n");
    printf("//4��traverse����\n");
    printf("//�������Ԫ�أ�\n");
    traverse_llist(L);
    printf("\n");
    printf("//5��empty����\n");
    empty_llist(L);
    printf("\n");

    printf("//6��insert����\n");
    printf("��ϣ����������ݣ�");
    scanf_s("%d", &e);
    printf("��ϣ�������λ�ã�");
    scanf_s("%d", &i);
    insert_llist(&L, e, i);
    printf("�������������ĳ��ȣ�%d\n", length_llist(L));
    printf("��������������");
    traverse_llist(L);
    printf("\n\n");

    printf("//7��delete����\n");
    printf("��ϣ��ɾ�����ݵ��±꣺");
    scanf_s("%d", &i);
    delete_llist(&L, i, &e);
    printf("��ɾ�������ݣ�%d\n", e);
    printf("ɾ������������ĳ��ȣ�%d\n", length_llist(L));
    printf("ɾ�������������");
    traverse_llist(L);
    printf("\n");

    printf("//8��getelem����\n");
    printf("\n");
    printf("��ϣ�����ҵ�λ�ã�");
    scanf_s("%d", &i);
    getelem_llist(L, i, &e);
    printf("��%dλ�����ǣ�%d\n", i, e);

    printf("//9��locate����\n");
    printf("��ϣ�����ҵ����ݣ�");
    scanf_s("%d", &e);
    i = locate_llist(L, e);
    printf("����%d�������λ�ã�%d\n\n", e, i);

    printf("//10��reverse1/2����\n");
    reverse2_llist(&L);
    printf("��ת�����������");
    traverse_llist(L);
    printf("\n");

    printf("//11��prior����\n");
    printf("��ϣ��������һλ��ǰ����");
    scanf_s("%d", &i);
    prior_llist(L, i, &e);
    printf("��%dλ���ݵ�ǰ����%d\n\n", i, e);

    printf("//12��next����\n");
    printf("��ϣ��������һλ�ĺ�̣�");
    scanf_s("%d", &i);
    next_llist(L, i, &e);
    printf("��%dλ���ݵĺ�̣�%d\n\n", i, e);

    printf("//13��clear/destroy����\n");
    clear_llist(&L);
    //printf("%p\n", L);
    empty_llist(L);

    return 0;
}