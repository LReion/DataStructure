#include <iostream>
#define maxSize 20
using namespace std;

// 邻接矩阵的结构型定义如下：
typedef struct {
  int no;     // 顶点编号
  char info;  // 顶点其他信息，这里默认是char
} VertexType; // 顶点类型

// 图的定义
typedef struct {
  int edges[maxSize][maxSize];
  // 邻接矩阵定义，如果是有权图，则在此句中将int改成float
  int n, e;                // 分别为定点数和边数
  VertexType vex[maxSize]; // 存放节点信息
} MGraph;

// 邻接表
typedef struct ArcNode {
  int adjvex;              // 该边所指向的结点的位置
  struct ArcNode *nextarc; // 指向下一条边的结点
  int info;                // 该边的相关信息（如权值）
} ArcNode;

typedef struct {
  char data;         // 顶点信息
  ArcNode *firstarc; // 指向第一条边的指针
} VNode;

typedef struct {
  VNode adjlist[maxSize]; // 邻接表
  int n, e;               // 顶点数和边数
} AGraph;                 // 图的邻接表类型
