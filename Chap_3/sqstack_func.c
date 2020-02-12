/************顺序栈************/
#include <stdio.h>
#include <malloc.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define endMark -731
#define STACK_INIT_SIZE 100         //存储空间初始分配量
#define STACKINCREMENT 10           //存储空间增量
typedef int Status;
typedef int elemType;

//顺序栈的第1种定义方式
typedef struct {
    elemType *bottom;           //栈底指针
    elemType *top;              //栈顶指针，指向栈顶元素的上面一个位置。top-bottom = 栈长
    int stackSize;              //栈容量
} sqStack1;

//顺序栈的第2种定义方式
typedef struct {
    elemType *bottom;
    int top;            //此处top代表栈顶元素的序号，和上面的指针区分
    int stackSize;
}sqStack2;

/**
 * 打印字符
 * @param e
 */
void visit(elemType e){
    printf("%d ", e);
}//visit

//第1种定义方式的函数
/*****************1.1、初始化栈*******************/
Status initStack1(sqStack1 *S){
    S->bottom = (elemType*)malloc(STACK_INIT_SIZE * sizeof(elemType));
    if(S->bottom == NULL) return OVERFLOW;
    S->top = S->bottom;
    S->stackSize = STACK_INIT_SIZE;
    return OK;
}//initStack1  √
/*****************1.2、销毁栈*******************/
Status destroyStack1(sqStack1 *S){
    free(S->bottom);
    S->bottom = S->top = NULL;
    S->stackSize = 0;
    return OK;
}//destroyStack1
/*****************1.3、清空栈*******************/
Status clearStack1(sqStack1 *S){
    free(S->bottom);
    initStack1(S);//TODO 清空表就是重新初始化？
    return OK;
}//clearStack1  √
/*****************1.4、查栈空*******************/
Status isEmptyStack1(sqStack1 S){
    if(S.bottom == S.top) {/*printf("--此栈空！\n");*/ return TRUE;}
    else if(S.top > S.bottom) {/*printf("--此栈非空！\n");*/ return FALSE;}
    else {printf("--此栈出错！\n"); return ERROR;}
}//isEmptyStack1  √
/*****************1.5、求栈长*******************/
int lengthStack1(sqStack1 S){
    return S.top - S.bottom;
}
/*****************1.6、栈顶数据*******************/
Status getTopStack1(sqStack1 S, elemType *e){
    if(S.bottom == S.top) return ERROR;         //栈空则不返回值
    *e = *(S.top - 1);
    return OK;
}//getTopStack1  √
/*****************1.7、数据入栈*******************/
Status pushStack1(sqStack1* S, elemType e){
    if(S->top-S->bottom>=S->stackSize){
        S->bottom = (elemType*)realloc(S->bottom, (S->stackSize+STACKINCREMENT)*sizeof(elemType));
        if(S->bottom == NULL) return OVERFLOW;
        S->top = S->bottom + S->stackSize;
        S->stackSize += STACKINCREMENT;
    }//若栈满，则扩大栈容量
    *(S->top) = e;
    (S->top)++;
    return OK;
}//pushStack1  √
/*****************1.8、数据出栈*******************/
Status popStack1(sqStack1 *S, int *e){          //用e返回栈顶元素
    if(S->top == S->bottom) return ERROR;       //若栈空，不对空栈操作
    *e = *(S->top - 1);
    (S->top)--;
    //上面两行可以合并成一行【*e = *(--(S->top));】， 但是不方便他人理解，故不使用
    return OK;
}//popStack1  √
/*****************1.9、遍历栈*******************/
void traverseStack1(sqStack1 S){
    printf("--遍历本栈元素（从栈底开始）：");
    for(int i=0; i<lengthStack1(S); i++)
        visit(*(S.bottom + i));
    printf("\n");
}//traverseStack1  √

//第2种定义方式的函数
/*****************2.1、初始化栈*******************/
Status initStack2(sqStack2 *S){
    S->bottom = (elemType*)malloc(STACK_INIT_SIZE * sizeof(elemType));
    if(S->bottom == NULL) return OVERFLOW;
    S->top = -1;
    S->stackSize = STACK_INIT_SIZE;
    return OK;
}//initStack2  √
/*****************2.2、销毁栈*******************/
Status destroyStack2(sqStack2 *S){
    free(S->bottom); S->bottom = NULL;
    //下面应该是S->top = -1还是 free(&(S->top))？
    S->top = -1; //TODO destroyStack2
    S->stackSize = 0;
    return OK;
}//destroyStack2
/*****************2.3、清空栈*******************/
Status clearStack2(sqStack2 *S){
    free(S->bottom);
    initStack2(S);//TODO 清空表就是重新初始化？
    return OK;
}//clearStack2  √
/*****************2.4、查栈空*******************/
Status isEmptyStack2(sqStack2 S){
    if(S.top == -1) {/*printf("--此栈空！\n");*/ return TRUE;}
    else if(S.top > -1) {/*printf("--此栈非空！\n");*/ return FALSE;}
    else {printf("--此栈出错！\n"); return ERROR;}
}//isEmptyStack2  √
/*****************2.5、求栈长*******************/
int lengthStack2(sqStack2 S){
    return S.top + 1;
}//lengthStack2  √
/*****************2.6、栈顶数据*******************/
Status getTopStack2(sqStack2 S, elemType *e){
    if(S.top == -1) return ERROR;         //栈空则不返回值
    *e = S.bottom[S.top];                 //或者写 *e = *(S.bottom + S.top);
    return OK;
}//getTopStack2  √
/*****************2.7、数据入栈*******************/
Status pushStack2(sqStack2 *S, int e){
    if(S->top + 1 >= S->stackSize){
        S->bottom = (elemType*)realloc(S->bottom, (S->stackSize+STACKINCREMENT)* sizeof(elemType));
        if(S->bottom == NULL) return ERROR;
        S->stackSize += STACKINCREMENT;
    }
    S->bottom[++(S->top)] = e;
    return OK;
}//pushStack2  √
/*****************2.8、数据出栈*******************/
Status popStack2(sqStack2 *S, int *e){      //用e返回栈顶元素
    if(S->top == -1) return ERROR;          //若栈空，则不对空栈操作
    *e = S->bottom[S->top];
    (S->top)--;
    //上面两行可以合并成一行【*e = S->bottom[(S->top)--];】， 但是不方便他人理解，故不使用
    return OK;
}//popStack2  √
/*****************2.9、遍历栈*******************/
void traverseStack2(sqStack2 S){
    printf("--遍历本栈元素（从栈底开始）：");
    for(int i=0; i<lengthStack2(S); i++)
        visit(S.bottom[i]);
    printf("\n");
}//traverseStack2  √

//栈的应用
/*****************3.1、进制换算*******************/
void conversion(){
    sqStack1 S;
    int e1, e2, system;
    initStack1(&S);
    printf("--请输入一个十进制数：");
    scanf_s("%d", &e1);
    e2 = e1;
    printf("--请输入要转换成什么进制：");
    scanf_s("%d", &system);
    while(e1){
        pushStack1(&S, e1%system);
        e1 /= system;
    }
    printf("--十进制数%d对应的%d进制数为：", e2, system);
    while(!isEmptyStack1(S)){
        popStack1(&S, &e1); printf("%d", e1);
    }
    printf("\n");
}//conversion

/**********************************************主函数*********************************************************/
int main() {
    /*
    //第1种
    printf("//顺序栈的第1种定义方式的测试\n");
    sqStack1 S1;
    int e;
    printf("//1.1、init测试\n");
    initStack1(&S1);
    printf("\n");

    printf("//1.2、isEmpty测试\n");
    isEmptyStack1(S1);
    printf("\n");

    printf("//1.3、push测试\n");
    printf("--键入入栈元素：");
    scanf_s("%d", &e);
    while(lengthStack1(S1)<S1.stackSize && e!=endMark){
        pushStack1(&S1, e);
        scanf_s("%d", &e);
    }
    isEmptyStack1(S1);
    printf("\n");

    printf("//1.4、length测试\n");
    printf("--当前栈长度：%d\n\n", lengthStack1(S1));

    printf("//1.5、traverse测试\n");
    traverseStack1(S1);
    printf("\n");

    printf("//1.6、pop测试\n");
    popStack1(&S1, &e);
    printf("--出栈一次后的栈长：%d\n", lengthStack1(S1));
    printf("--上一个出栈数据：%d\n\n", e);

    printf("//1.7、getTop测试\n");
    getTopStack1(S1, &e);
    printf("--当前栈顶数据：%d\n\n", e);

    printf("//1.8、clear/destroy测试\n");
    clearStack1(&S1);
    printf("--当前栈长度：%d\n\n", lengthStack1(S1));
    //第2种
    printf("//顺序栈的第2种定义方式的测试\n");
    sqStack2 S2;
    printf("//2.1、init测试\n");
    initStack2(&S2);
    printf("\n");

    printf("//2.2、isEmpty测试\n");
    isEmptyStack2(S2);
    printf("\n");

    printf("//2.3、push测试\n");
    printf("--键入入栈元素：");
    scanf_s("%d", &e);
    while(lengthStack2(S2)<S2.stackSize && e!=endMark){
        pushStack2(&S2, e);
        scanf_s("%d", &e);
    }
    isEmptyStack2(S2);
    printf("\n");

    printf("//2.4、length测试\n");
    printf("--当前栈长度：%d\n\n", lengthStack2(S2));

    printf("//2.5、traverse测试\n");
    traverseStack2(S2);
    printf("\n");

    printf("//2.6、pop测试\n");
    popStack2(&S2, &e);
    printf("--出栈一次后的栈长：%d\n", lengthStack2(S2));
    printf("--上一个出栈数据：%d\n\n", e);

    printf("//2.7、getTop测试\n");
    getTopStack2(S2, &e);
    printf("--当前栈顶数据：%d\n\n", e);

    printf("//2.8、clear/destroy测试\n");
    clearStack2(&S2);
    printf("--当前栈长度：%d\n\n", lengthStack2(S2));

    printf("--键入入栈元素：");
    scanf_s("%d", &e);
    while(lengthStack2(S2)<S2.stackSize && e!=endMark) {
        pushStack2(&S2, e);
        scanf_s("%d", &e);
    }
    printf("\n--当前栈长度：%d\n\n", lengthStack2(S2));
    getTopStack2(S2, &e);
    printf("--当前栈顶数据：%d\n\n", e);
    */
    conversion();

    return 0;
}