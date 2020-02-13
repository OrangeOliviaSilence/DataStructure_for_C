/************˳��ջ************/
#include <stdio.h>
#include <malloc.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define endMark -731
#define STACK_INIT_SIZE 100         //�洢�ռ��ʼ������
#define STACKINCREMENT 10           //�洢�ռ�����
typedef int Status;
typedef int elemType;

//˳��ջ�ĵ�1�ֶ��巽ʽ
typedef struct {
    elemType *bottom;           //ջ��ָ��
    elemType *top;              //ջ��ָ�룬ָ��ջ��Ԫ�ص�����һ��λ�á�top-bottom = ջ��
    int stackSize;              //ջ����
} sqStack1;

//˳��ջ�ĵ�2�ֶ��巽ʽ
typedef struct {
    elemType *bottom;
    int top;            //�˴�top����ջ��Ԫ�ص���ţ��������ָ������
    int stackSize;
}sqStack2;

/**
 * ��ӡ�ַ�
 * @param e
 */
void visit(elemType e){
    printf("%d ", e);
}//visit

//��1�ֶ��巽ʽ�ĺ���
/*****************1.1����ʼ��ջ*******************/
Status initStack1(sqStack1 *S){
    S->bottom = (elemType*)malloc(STACK_INIT_SIZE * sizeof(elemType));
    if(S->bottom == NULL) return OVERFLOW;
    S->top = S->bottom;
    S->stackSize = STACK_INIT_SIZE;
    return OK;
}//initStack1  ��
/*****************1.2������ջ*******************/
Status destroyStack1(sqStack1 *S){
    free(S->bottom);
    S->bottom = S->top = NULL;
    S->stackSize = 0;
    return OK;
}//destroyStack1
/*****************1.3�����ջ*******************/
Status clearStack1(sqStack1 *S){
    S->top = S->bottom;
    return OK;
}//clearStack1  ��
/*****************1.4����ջ��*******************/
Status isEmptyStack1(sqStack1 S){
    if(S.bottom == S.top) {/*printf("--��ջ�գ�\n");*/ return TRUE;}
    else if(S.top > S.bottom) {/*printf("--��ջ�ǿգ�\n");*/ return FALSE;}
    else {printf("--��ջ����\n"); return ERROR;}
}//isEmptyStack1  ��
/*****************1.5����ջ��*******************/
int lengthStack1(sqStack1 S){
    return S.top - S.bottom;
}
/*****************1.6��ջ������*******************/
Status getTopStack1(sqStack1 S, elemType *e){
    if(S.bottom == S.top) return ERROR;         //ջ���򲻷���ֵ
    *e = *(S.top - 1);
    return OK;
}//getTopStack1  ��
/*****************1.7��������ջ*******************/
Status pushStack1(sqStack1* S, elemType e){
    if(S->top-S->bottom>=S->stackSize){
        S->bottom = (elemType*)realloc(S->bottom, (S->stackSize+STACKINCREMENT)*sizeof(elemType));
        if(S->bottom == NULL) return OVERFLOW;
        S->top = S->bottom + S->stackSize;
        S->stackSize += STACKINCREMENT;
    }//��ջ����������ջ����
    *(S->top) = e;
    (S->top)++;
    return OK;
}//pushStack1  ��
/*****************1.8�����ݳ�ջ*******************/
Status popStack1(sqStack1 *S, elemType *e){          //��e����ջ��Ԫ��
    if(S->top == S->bottom) return ERROR;       //��ջ�գ����Կ�ջ����
    *e = *(S->top - 1);
    (S->top)--;
    //�������п��Ժϲ���һ�С�*e = *(--(S->top));���� ���ǲ�����������⣬�ʲ�ʹ��
    return OK;
}//popStack1  ��
/*****************1.9������ջ*******************/
void traverseStack1(sqStack1 S){
    printf("--������ջԪ�أ���ջ�׿�ʼ����");
    for(int i=0; i<lengthStack1(S); i++)
        visit(*(S.bottom + i));
    printf("\n");
}//traverseStack1  ��

//��2�ֶ��巽ʽ�ĺ���
/*****************2.1����ʼ��ջ*******************/
Status initStack2(sqStack2 *S){
    S->bottom = (elemType*)malloc(STACK_INIT_SIZE * sizeof(elemType));
    if(S->bottom == NULL) return OVERFLOW;
    S->top = -1;
    S->stackSize = STACK_INIT_SIZE;
    return OK;
}//initStack2  ��
/*****************2.2������ջ*******************/
Status destroyStack2(sqStack2 *S){
    free(S->bottom); S->bottom = NULL;
    //����Ӧ����S->top = -1���� free(&(S->top))�� ��S->top = -1; ��ΪfreeҪ��malloc���ʹ��
    S->top = -1;
    S->stackSize = 0;
    return OK;
}//destroyStack2
/*****************2.3�����ջ*******************/
Status clearStack2(sqStack2 *S){
    S->top = -1;
    return OK;
}//clearStack2  ��
/*****************2.4����ջ��*******************/
Status isEmptyStack2(sqStack2 S){
    if(S.top == -1) {/*printf("--��ջ�գ�\n");*/ return TRUE;}
    else if(S.top > -1) {/*printf("--��ջ�ǿգ�\n");*/ return FALSE;}
    else {printf("--��ջ����\n"); return ERROR;}
}//isEmptyStack2  ��
/*****************2.5����ջ��*******************/
int lengthStack2(sqStack2 S){
    return S.top + 1;
}//lengthStack2  ��
/*****************2.6��ջ������*******************/
Status getTopStack2(sqStack2 S, elemType *e){
    if(S.top == -1) return ERROR;         //ջ���򲻷���ֵ
    *e = S.bottom[S.top];                 //����д *e = *(S.bottom + S.top);
    return OK;
}//getTopStack2  ��
/*****************2.7��������ջ*******************/
Status pushStack2(sqStack2 *S, elemType e){
    if(S->top + 1 >= S->stackSize){
        S->bottom = (elemType*)realloc(S->bottom, (S->stackSize+STACKINCREMENT)* sizeof(elemType));
        if(S->bottom == NULL) return ERROR;
        S->stackSize += STACKINCREMENT;
    }
    S->bottom[++(S->top)] = e;
    return OK;
}//pushStack2  ��
/*****************2.8�����ݳ�ջ*******************/
Status popStack2(sqStack2 *S, int *e){      //��e����ջ��Ԫ��
    if(S->top == -1) return ERROR;          //��ջ�գ��򲻶Կ�ջ����
    *e = S->bottom[S->top];
    (S->top)--;
    //�������п��Ժϲ���һ�С�*e = S->bottom[(S->top)--];���� ���ǲ�����������⣬�ʲ�ʹ��
    return OK;
}//popStack2  ��
/*****************2.9������ջ*******************/
void traverseStack2(sqStack2 S){
    printf("--������ջԪ�أ���ջ�׿�ʼ����");
    for(int i=0; i<lengthStack2(S); i++)
        visit(S.bottom[i]);
    printf("\n");
}//traverseStack2  ��

//ջ��Ӧ��
/*****************3.1�����ƻ���*******************/
void conversion(){
    sqStack1 S;
    int e1, e2, system;
    initStack1(&S);
    printf("--������һ��ʮ��������");
    scanf_s("%d", &e1);
    e2 = e1;
    printf("--������Ҫת����ʲô���ƣ���ʱ��֧��ʮ�����ƣ���");
    scanf_s("%d", &system);
    while(e1){
        pushStack1(&S, e1%system);
        e1 /= system;
    }
    printf("--ʮ������%d��Ӧ��%d������Ϊ��", e2, system);
    while(!isEmptyStack1(S)){
        popStack1(&S, &e1); printf("%d", e1);
    }
    printf("\n");
}//conversion TODO ʮ�����Ƶı�ʾ��û������
/*****************3.2�������ȼ�������ƥ�����*******************/
//1���ж�������
Status isLeft(char left){
    switch(left){
        case '(': return 1; break;
        case '[': return 2; break;
        case '{': return 3; break;
        default: return FALSE;
    }
}//isLeft
//2���ж�������
Status isRight(char right){
    if(right==')' || right==']' || right=='}') return TRUE;
    else return FALSE;
}//isRight
//3���ж����������Ƿ�ƥ��
Status match(char left, char right){
    if(left=='(' && right==')') return TRUE;
    else if(left=='[' && right==']') return TRUE;
    else if(left=='{' && right=='}') return TRUE;
    else return FALSE;
}//match
//4������ƥ�亯��
Status matching(char *str){         //str��ĳ���ַ������׵�ַ
    char *p = str;          //p��һ��ָ���ַ������ݵ�ָ��
    sqStack1 S; initStack1(&S);
    char ch, left;
    char e;             //����ȡ��ջ����������ȷ�����ŵ����ȼ��Ƿ���ȷ
    while((ch=*p) != '\0'){
        if(isLeft(ch)){
            getTopStack1(S, &e);            //���ջ������
            if(isLeft(ch)==2 && e=='(') return 0;               //��ʾ�������ȼ�����
            if(isLeft(ch)==3 && (e=='[' || e=='(')) return 0;   //��ʾ�������ȼ�����
            pushStack1(&S, ch);
        }
        if(isRight(ch)){
            if(!popStack1(&S, &left)) return -1;         //��ʾ�ַ����ӿ�ͷ��ȱ��������
            if(!match(left, ch)) return -2;              //��ʾ��ǰ��ȵ������źͱ������Ų�ƥ��
        }
        p++;
    }
    if(!isEmptyStack1(S)) return -3;            //��ʾջ���ж����������û�еõ�ƥ��
    return TRUE;
}//matching     ��

/**********************************************������*********************************************************/
int main() {
    //��1��
    printf("//˳��ջ�ĵ�1�ֶ��巽ʽ�Ĳ���\n");
    sqStack1 S1;
    int e;
    printf("//1.1��init����\n");
    initStack1(&S1);
    printf("\n");

    printf("//1.2��isEmpty����\n");
    isEmptyStack1(S1);
    printf("\n");

    printf("//1.3��push����\n");
    printf("--������ջԪ�أ�");
    scanf_s("%d", &e);
    while(lengthStack1(S1)<S1.stackSize && e!=endMark){
        pushStack1(&S1, e);
        scanf_s("%d", &e);
    }
    isEmptyStack1(S1);
    printf("\n");

    printf("//1.4��length����\n");
    printf("--��ǰջ���ȣ�%d\n\n", lengthStack1(S1));

    printf("//1.5��traverse����\n");
    traverseStack1(S1);
    printf("\n");

    printf("//1.6��pop����\n");
    popStack1(&S1, &e);
    printf("--��ջһ�κ��ջ����%d\n", lengthStack1(S1));
    printf("--��һ����ջ���ݣ�%d\n\n", e);

    printf("//1.7��getTop����\n");
    getTopStack1(S1, &e);
    printf("--��ǰջ�����ݣ�%d\n\n", e);

    printf("//1.8��clear/destroy����\n");
    clearStack1(&S1);
    printf("--��ǰջ���ȣ�%d\n\n", lengthStack1(S1));
    //��2��
    printf("//˳��ջ�ĵ�2�ֶ��巽ʽ�Ĳ���\n");
    sqStack2 S2;
    printf("//2.1��init����\n");
    initStack2(&S2);
    printf("\n");

    printf("//2.2��isEmpty����\n");
    isEmptyStack2(S2);
    printf("\n");

    printf("//2.3��push����\n");
    printf("--������ջԪ�أ�");
    scanf_s("%d", &e);
    while(lengthStack2(S2)<S2.stackSize && e!=endMark){
        pushStack2(&S2, e);
        scanf_s("%d", &e);
    }
    isEmptyStack2(S2);
    printf("\n");

    printf("//2.4��length����\n");
    printf("--��ǰջ���ȣ�%d\n\n", lengthStack2(S2));

    printf("//2.5��traverse����\n");
    traverseStack2(S2);
    printf("\n");

    printf("//2.6��pop����\n");
    popStack2(&S2, &e);
    printf("--��ջһ�κ��ջ����%d\n", lengthStack2(S2));
    printf("--��һ����ջ���ݣ�%d\n\n", e);

    printf("//2.7��getTop����\n");
    getTopStack2(S2, &e);
    printf("--��ǰջ�����ݣ�%d\n\n", e);

    printf("//2.8��clear/destroy����\n");
    clearStack2(&S2);
    printf("--��ǰջ���ȣ�%d\n\n", lengthStack2(S2));

    printf("--������ջԪ�أ�");
    scanf_s("%d", &e);
    while(lengthStack2(S2)<S2.stackSize && e!=endMark) {
        pushStack2(&S2, e);
        scanf_s("%d", &e);
    }
    printf("\n--��ǰջ���ȣ�%d\n\n", lengthStack2(S2));
    getTopStack2(S2, &e);
    printf("--��ǰջ�����ݣ�%d\n\n", e);

    //3ջ��Ӧ��
    printf("//3.1��conversion����\n");
    conversion();

    printf("//3.2��matching����\n");
    char str[] = "([{";
    printf("%d\n", matching(str));
    return 0;
}