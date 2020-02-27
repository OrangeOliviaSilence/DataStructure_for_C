#include "stdio.h"
#include "malloc.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define endMark -731
//#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 20
typedef int Status;
typedef enum{DG, DN, UDG, UDN} graphKind;
typedef char vertexType;

//1���ڽӾ����ʾ��
typedef struct {
    vertexType vexs[MAX_VERTEX_NUM];
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];       //arcs[i][j]��ֵ�������Ƿ������Ӷ���i��j�Ļ�/��
    int vexnum, arcnum;
    graphKind kind;
}MGraph;

//2���ڽӱ�ʾ��
/*typedef struct arcNode{             //�ö����һ����/�ߣ��������г�Ϊ�߽ڵ�
    int adjvex;                     //��ʾ�û�/��ָ����ڽӶ��������
    struct arcNode *nextarc;        //��ʾ�ö������һ����
} arcNode;
typedef struct {
    vertexType data;                //�������ŵ�����
    arcNode *firstarc;               //������ĵ�һ����/��
}VNode, adjList[MAX_VERTEX_NUM];
typedef struct {
    adjList vertexs;
    int vernum, arcnum;
    graphKind kind;
}ALGraph;*/
//2���ڽӱ��ʾ��
typedef struct arcNode{     //�߽ڵ�
    int adjvexIndex;
    struct arcNode *nextarc;
}arcNode;
typedef struct {
    vertexType data;
    arcNode *firstarc;
}vexNode;
typedef struct {
    vexNode adjList[MAX_VERTEX_NUM];        //�ڽӱ�
    int vexnum, arcnum;
    graphKind kind;
}ALGraph;

//1���ڽӾ����ʾ���Ļ�������
/********************1�����±�Ϊv�Ķ���ĵ�һ���ڽӽڵ�*********************/
Status firstAdjVex1(MGraph G, int v, int *k){        //Ĭ���±���СΪ1
    if(v<1 || v>G.vexnum) return ERROR;
    int i = 0;
    while(i<G.vexnum && G.arcs[v-1][i] == 0) i++;
    if(i == G.vexnum) {
        *k = endMark;       //����±�Ϊv�Ķ���û���ڽӵ㣬�򷵻�endMark
        return ERROR;
    }//if
    else {
        *k = i;
        return OK;
    }//else
}//firstAdjVex1
/********************2�����±�Ϊv�Ķ��㣬���±�ֵ����w�Ķ����У��������ڽӵ㣬�еĻ����ص�һ���ڽӵ���±�*********************/
Status nextAdjVex1(MGraph G, int v, int w, int *k){
    if(v<1 || v>G.vexnum) return ERROR;         //�˴�ERROR����˼�ǣ�v��ֵ���Ϸ�
    if(w<=0 || w>=G.vexnum) return ERROR;       //�˴�ERROR����˼�ǣ�w��ֵ���Ϸ�
                                                //�˺����У�ERROR�������˼�У�v��ֵ���Ϸ�||w��ֵ���Ϸ�
    int i = w;          //i��������±�ֵΪw+1�Ķ��㣬��������ھ����е�����ֵ����w
    while(i<G.vexnum && G.arcs[v-1][i]==0) i++;
    if(i == G.vexnum){
        *k = endMark;
        return OK;              //�˴�OK�������v, w���Ϸ�������vҲ���ڽӵ㡣���������±����w���ڽӵ㲻����
    }//if
    else{
        *k = i;
        return OK;              //�˴�OK�������v, w���Ϸ�������vҲ���ڽӵ㡣�������±����w���ڽӵ����
                                //�˺�����OK�������v, w���Ϸ�������vҲ���ڽӵ㡣���ǲ�����˵�����±����w���ڽӵ����
    }//else
}//nextAdjVex1

//2���ڽӱ��ʾ���Ļ�������
/********************1�����±�Ϊv�Ķ���ĵ�һ���ڽӽڵ�*********************/
Status firstAdjVex2(ALGraph G, int v, int *k){
    if(v<1 || v>G.vexnum) return ERROR;
    arcNode *p = G.adjList[v-1].firstarc;
    if(p == NULL){
        *k = endMark;
        return ERROR;
    }//if
    else{
        *k = p->adjvexIndex;
        return OK;
    }//else
}//firstAdjVex2
/********************2�����±�Ϊv�Ķ��㣬���±�ֵ����w�Ķ����У��������ڽӵ㣬�еĻ����ص�һ���ڽӵ���±�*********************/
Status nextAdjVex2(ALGraph G, int v, int w, int *k){
    if(v<1 || v>G.vexnum) return ERROR;     //�˴�ERROR����˼�ǣ�v��ֵ���Ϸ�
    if(w<=0 || w>=G.vexnum) return ERROR;   //�˴�ERROR����˼�ǣ�w��ֵ���Ϸ�
    int index = endMark;
    arcNode *p = G.adjList[v-1].firstarc;
    if(!p) return ERROR;                    //�˴�ERROR����˼�ǣ�����vһ���ڽӵ�Ҳû��
                                            //�˺����У�ERROR�������˼�У�v��ֵ���Ϸ�||w��ֵ���Ϸ�||����vһ���ڽӵ�Ҳû��
    while(p){               //�������v���ڽӵ㣬��ִ�����²���
        if(p->adjvexIndex > w){
            index = index < p->adjvexIndex ? (index == endMark ? p->adjvexIndex : index) : p->adjvexIndex;
        }//if
        p = p->nextarc;
    }//while
    *k = index;
    return OK;              //�˴�OK�������v, w���Ϸ�������vҲ���ڽӵ㡣���ǲ�����˵�����±����w���ڽӵ����
}//nextAdjVex2

int main(){
    ALGraph G1;

}