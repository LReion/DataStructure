#include <iostream>
#define maxSize 20
#define INF 32767
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

void Visit(AGraph *G, int v) { cout << G->adjlist[v].data; }

// 深度优先搜索算法
// 以邻接表为存储结构的图的优先搜索遍历算法如下：
int visit[maxSize]; // 访问标志数组
void DFS(AGraph *G, int v) {
  ArcNode *p;
  visit[v] = 1;
  Visit(G, v); // 函数Visit()代表了一类访问顶点v的操作
  p = G->adjlist[v].firstarc; // p指向顶点v的第一条边
  while (p != nullptr) {
    if (!visit[p->adjvex]) // 如果顶点未被访问
      DFS(G, p->adjvex);
    p = p->nextarc; // p指向顶点v的下一条边的结点
  }
}

// 广度优先搜索便利（BFS）类似树的层次遍历
// 广度优先搜索遍历图时，需要用到一个队列
// 以邻接表为存储结构的图的广度优先搜索遍历算法如下：
void BFS(AGraph *G, int v, int visit[maxSize]) {
  // visit[]数组被初始化为0
  ArcNode *p;
  int que[maxSize], front = 0, rear = 0; // 定义一个队列
  int j;
  Visit(G, v); // 任意访问顶点v的函数
  visit[v] = 1;
  rear = (rear + 1) % maxSize; // v入队
  que[rear] = v;
  while (front != rear) { // 队列为空则说明遍历完成
    front = (front + 1) % maxSize;
    j = que[front];                  // 顶点出队
    p = G->adjlist[j].firstarc;      // p为指向顶点的第一条边
    while (p != nullptr) {           // 如果边存在
      if (!visit[p->adjvex]) {       // 如果这条边没被访问过
        Visit(G, p->adjvex);         // 访问这条边
        visit[p->adjvex] = 1;        // 将标记访问过
        rear = (rear + 1) % maxSize; // 将当前邻接顶点入队
        que[rear] = p->adjvex;
      }
      p = p->nextarc; // p指向j的下一条边
    }
  }
}

// 针对非连通图的的遍历，只需将上述遍历函数放在一个循环中，循环用来检测图中的每一个顶点
void DFSTraverse(AGraph *G) {
  int i;
  for (i = 0; i < G->n; i++)
    visit[i] = 0; // 访问标志数组初始化
  for (i = 0; i < G->n; i++)
    if (!visit[i])
      DFS(G, i); // 对尚未访问的顶点调用DFS
}
void BFSTraverse(AGraph *G) {
  int i;
  for (i = 0; i < G->n; i++)
    visit[i] = 0; // 访问标志数组初始化
  for (i = 0; i < G->n; i++)
    if (!visit[i])
      BFS(G, i, visit); // 对尚未访问的顶点调用BFS
}

// 设计一个散发，求不带权无向连通图中距离顶点v最远的一个顶点（所谓最远就是到达v的路径长度最长）
int MaxDist(AGraph *G, int v) {
  ArcNode *p;
  int que[maxSize], front = 0, rear = 0;
  int visit[maxSize];
  int i, j;
  for (i = 0; i < G->n; i++)
    visit[i] = 0;
  rear = (rear + 1) % maxSize;
  que[rear] = v;
  while (front != rear) {
    front = (front + 1) % maxSize;
    j = que[front];
    p = G->adjlist[j].firstarc;
    while (p != nullptr) {
      if (!visit[p->adjvex]) {
        Visit(G, p->adjvex);
        visit[p->adjvex] = 1;
        rear = (rear + 1) % maxSize;
        que[rear] = p->adjvex;
      }
      p = p->nextarc;
    }
  }
  return j; // 队空时，j保存了遍历过程中的最后一个结点
}

// 一个无向图是一棵树的条件是有n-1条边的连通图，n为图中顶点的个数。边和顶点的数目是否满足这个条件是判断一个图是否为树的充分必要条件
// 连通与否可以用便利能否访问到所有顶点来判断
void DFS2(AGraph *G, int v, int &vn, int &en) {
  ArcNode *p;
  visit[v] = 1;
  ++vn; // 访问到当前顶点加1
  p = G->adjlist[v].firstarc;
  while (p != nullptr) {
    ++en; // 访问到边加一
    if (visit[p->adjvex] == 0)
      DFS2(G, p->adjvex, vn, en);
    p = p->nextarc;
  }
}
int GisTree(AGraph *G) {
  int vn = 0, en = 0, i;
  for (i = 0; i < G->n; i++)
    // 初始化访问数组
    visit[i] = 0;
  // 开始访问
  DFS2(G, 1, vn, en);
  // 判断是否为树
  // en等于两倍的顶点数减一，是因为是无向图，边被记录了两次
  if (vn == G->n && en == 2 * (G->n - 1))
    return 1;
  else
    return 0;
}

// 图采用邻接表存储，设一个算法，判断顶点i和j（i!=j）之间是否有路径
int DFSTrave(AGraph *G, int i, int j) {
  int k;
  for (k = 0; k < G->n; k++)
    visit[k] = 0;
  // 从结点i开始，进行深度优先搜索
  DFS(G, i);
  // 如果j被访问过，则说明i到j之间有路径
  if (visit[j] == 1)
    return 1;
  else
    return 0;
}

// 最小（代价）生成树
// 1）普利姆算法思想
// 从图中任意取出一个顶点，把它当成一棵树，然后从这棵树相接的边中选取一条最短（权值最小）的边，
// 并将这条边及其所连接的顶点也并入这颗树中，此时得到一颗有两个顶点的树。然后从这颗树相接的边中选取一条最短的边，
// 并将这条边及其所连接的顶点并入这颗树中，此时得到一颗有三个顶点的树。如此重复，直到所有顶点都被并入这颗树中为止。
// 以此类推，最后得到的一颗有n个顶点的树就是最小生成树。
// 2) 普利姆算法的实现
void Prim(MGraph g, int v0, int &sum) {
  int lowcost[maxSize], vset[maxSize], v;
  int i, j, k, min;
  v = v0;
  for (i = 0; i < g.n; i++) {
    lowcost[i] = g.edges[v0][i];
    vset[i] = 0;
  }
  vset[v0] = 1; // 将v0并入树中
  sum = 0;      // sum请0用来累计树的权值
  for (i = 0; i < g.n - 1; i++) {
    min = INF; // INF是一个已经定义好的常量，表示无穷大
    // 选出当前的最小权值的边
    for (j = 0; j < g.n; j++) {
      if (!vset[j] && lowcost[j] < min) {
        min = lowcost[j]; // 最短边中最短的一条（两个最短）
        k = j;
      }
      vset[k] = 1;
      v = k;
      sum += min; // 用sum记录最小生成树的权值
      // 以刚并入的顶点v为媒介，更新lowcost数组
      for (j = 0; j < g.n; j++)
        if (!vset[j] && g.edges[v][j] < lowcost[j]) {
          lowcost[j] = g.edges[v][j];
        }
    }
  }
}

// 3）普利姆算法时间复杂度分析
// 由于每次都要从n个顶点中选取一个顶点，并且要从n-1条边中选取一条边，所以时间复杂度为O(n^2)

// 克鲁斯卡尔算法思想
// 每次找出候选边中权值最小的边，就将该边并入生成树中。重复此过程直到所有边都被检测完为止。
// 由于每次都是从候选边中选取权值最小的边，并且每次选取的边都是不同的，所以最后得到的一定是一颗树。
// 假设road[]数组中已经存放了图中各边及其所连接的两个顶点的信息，且排序函数已经存在，那么克鲁斯卡尔算法的实现如下：
typedef struct {
  int a, b; // a和b为一条边所连的两个顶点
  int w;
} Road;

Road road[maxSize];
int v[maxSize]; // 并查集数组
int getRoot(int a) {
  while (a != v[a])
    a = v[a];
  return a;
}
void Kruskal(MGraph g, int &sum, Road road[]) {
  int i;
  int N, E, a, b;
  N = g.n;
  E = g.e;
  sum = 0;
  for (i = 0; i < N; i++)
    v[i] = i;
  sort(road, E); // 队roard数组中E条边按其权值从小到大排序
  for (i = 0; i < E; i++) { // 遍历所有边
    a = getRoot(a);
    b = getRoot(b);
    if (a != b) {       // 如果没有相同的根
      v[a] = b;         // 则放在一个并查集里
      sum += road[i].w; // 累加权值
    }
  }
}
