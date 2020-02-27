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

//1、邻接矩阵表示法
typedef struct {
    vertexType vexs[MAX_VERTEX_NUM];
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];       //arcs[i][j]的值，代表是否有连接顶点i和j的弧/边
    int vexnum, arcnum;
    graphKind kind;
}MGraph;

//2、邻接表示法
/*typedef struct arcNode{             //该顶点的一条弧/边，在链表中称为边节点
    int adjvex;                     //表示该弧/边指向的邻接顶点的索引
    struct arcNode *nextarc;        //表示该顶点的下一条弧
} arcNode;
typedef struct {
    vertexType data;                //本顶点存放的数据
    arcNode *firstarc;               //本顶点的第一条弧/边
}VNode, adjList[MAX_VERTEX_NUM];
typedef struct {
    adjList vertexs;
    int vernum, arcnum;
    graphKind kind;
}ALGraph;*/
//2、邻接表表示法
typedef struct arcNode{     //边节点
    int adjvexIndex;
    struct arcNode *nextarc;
}arcNode;
typedef struct {
    vertexType data;
    arcNode *firstarc;
}vexNode;
typedef struct {
    vexNode adjList[MAX_VERTEX_NUM];        //邻接表
    int vexnum, arcnum;
    graphKind kind;
}ALGraph;

//1、邻接矩阵表示法的基本操作
/********************1、求下标为v的顶点的第一个邻接节点*********************/
Status firstAdjVex1(MGraph G, int v, int *k){        //默认下标最小为1
    if(v<1 || v>G.vexnum) return ERROR;
    int i = 0;
    while(i<G.vexnum && G.arcs[v-1][i] == 0) i++;
    if(i == G.vexnum) {
        *k = endMark;       //如果下标为v的顶点没有邻接点，则返回endMark
        return ERROR;
    }//if
    else {
        *k = i;
        return OK;
    }//else
}//firstAdjVex1
/********************2、求下标为v的顶点，在下标值大于w的顶点中，否是有邻接点，有的话返回第一个邻接点的下标*********************/
Status nextAdjVex1(MGraph G, int v, int w, int *k){
    if(v<1 || v>G.vexnum) return ERROR;         //此处ERROR的意思是，v的值不合法
    if(w<=0 || w>=G.vexnum) return ERROR;       //此处ERROR的意思是，w的值不合法
                                                //此函数中，ERROR代表的意思有：v的值不合法||w的值不合法
    int i = w;          //i代表的是下标值为w+1的顶点，这个顶点在矩阵中的索引值等于w
    while(i<G.vexnum && G.arcs[v-1][i]==0) i++;
    if(i == G.vexnum){
        *k = endMark;
        return OK;              //此处OK代表的是v, w都合法、顶点v也有邻接点。但是满足下标大于w的邻接点不存在
    }//if
    else{
        *k = i;
        return OK;              //此处OK代表的是v, w都合法、顶点v也有邻接点。且满足下标大于w的邻接点存在
                                //此函数中OK代表的是v, w都合法、顶点v也有邻接点。但是并不是说满足下标大于w的邻接点存在
    }//else
}//nextAdjVex1

//2、邻接表表示法的基本操作
/********************1、求下标为v的顶点的第一个邻接节点*********************/
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
/********************2、求下标为v的顶点，在下标值大于w的顶点中，否是有邻接点，有的话返回第一个邻接点的下标*********************/
Status nextAdjVex2(ALGraph G, int v, int w, int *k){
    if(v<1 || v>G.vexnum) return ERROR;     //此处ERROR的意思是，v的值不合法
    if(w<=0 || w>=G.vexnum) return ERROR;   //此处ERROR的意思是，w的值不合法
    int index = endMark;
    arcNode *p = G.adjList[v-1].firstarc;
    if(!p) return ERROR;                    //此处ERROR的意思是，顶点v一个邻接点也没有
                                            //此函数中，ERROR代表的意思有：v的值不合法||w的值不合法||顶点v一个邻接点也没有
    while(p){               //如果顶点v有邻接点，则执行以下步骤
        if(p->adjvexIndex > w){
            index = index < p->adjvexIndex ? (index == endMark ? p->adjvexIndex : index) : p->adjvexIndex;
        }//if
        p = p->nextarc;
    }//while
    *k = index;
    return OK;              //此处OK代表的是v, w都合法、顶点v也有邻接点。但是并不是说满足下标大于w的邻接点存在
}//nextAdjVex2

int main(){
    ALGraph G1;

}