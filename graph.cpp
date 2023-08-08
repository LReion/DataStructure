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

void printPath(int path[], int a) {
  int stack[maxSize], top = -1;
  /* 这个循环由叶子节点到根节点的顺序将其入栈 */
  while (path[a] != -1) {
    stack[++top] = a;
    a = path[a];
  }
  stack[++top] = a;
  while (top != -1)
    cout << stack[top--] << " "; // 出栈并打印栈元素实现了顶点的逆序打印
}
// 迪杰斯特拉算法，求图中某一顶点到其余个顶点的最短路径。
void Dijkstra(MGraph g, int v, int dist[], int path[]) {
  int set[maxSize];
  int min, i, j, u;
  // 对数组开始初始化
  for (i = 0; i < g.n; i++) {
    dist[i] = g.edges[v][i];
    set[i] = 0;
    if (g.edges[v][i] < INF)
      path[i] = v;
    else
      path[i] = -1;
  }
  set[v] = 1;
  path[v] = -1;
  for (i = 0; i < g.n - 1; i++) {
    min = INF;
    // 每次从剩余顶点中选出一个顶点，通往这个顶点的路径在通往所有剩余顶点的路径中是最短的
    for (j = 0; j < g.n; j++) {
      if (set[j] == 0 && dist[j] < min) {
        u = j;
        min = dist[j];
      }
      set[u] = 1; // 将刚刚选出的顶点并入最短路径中
      // 以刚并入的顶点作为中间点，对所有通往剩余顶点的路径进行检查
      for (j = 0; j < g.n; j++) {
        // 判断顶点u的加入是否会出现通往顶点j的更短路径，如果出现则更新dist[j]和path[j]
        // 否则什么都不做
        if (set[j] == 0 && dist[u] + g.edges[u][j] < dist[j]) {
          dist[j] = dist[u] + g.edges[u][j];
          path[j] = u;
        }
      }
    }
  }
}
// 函数结束时，dist[]数组中存放了v点到其余顶点的最短路径长度，path[]中存放v点到其他个顶点的最短路径
// 由算法代码可知，本算法主要部分为一个双重循环，外层循环内部有两个并列的单层循环，可以任取一个循环内的操作
// 作为基本操作，基本执行的总次数即为双重循环执行的次数，为n^2次，所以时间复杂度为O(n^2)

// 求图中任意一对顶点间的最短路径，则用弗洛伊德算法。
// 弗洛伊德算法打印最短路径
void printPath(int u, int v, int path[][maxSize], int A[][maxSize]) {
  // 输出从u到v的最短路径上的顶点序列
  if (A[u][v] == INF)
    cout << "No Path !" << endl;
  else {
    if (path[u][v] == -1)
      cout << v << " ";
    else {
      int mid = path[u][v];
      printPath(u, mid, path, A); // 处理前半段
      printPath(mid, v, path, A); // 处理后半段
    }
  }
}

void Floyd(MGraph *g, int Path[][maxSize], int A[][maxSize]) {
  // 图g的边矩阵中，用INF来表示两点之间不存在边
  int i, j, k;
  // 初始化A[]和Path[][]
  for (i = 0; i < g->n; ++i) {
    for (j = 0; j < g->n; ++j) {
      A[i][j] = g->edges[i][j];
      Path[i][j] = -1;
    }
  }
  // 三重循环，每次循环都尝试将顶点k作为中间点，如果经过顶点k的路径比原来的路径更短，则更新A[i][j]和Path[i][j]
  for (k = 0; k < g->n; k++) {
    for (i = 0; i < g->n; i++) {
      for (j = 0; j < g->n; j++) {
        if (A[i][j] > A[i][k] + A[k][j]) {
          A[i][j] = A[i][k] + A[k][j];
          Path[i][j] = k;
        }
      }
    }
  }
}

// 由算法代码可知，本算法主要部分为一个三重循环，循环内部有一个单层循环，可以任取一个循环内的操作作为基本操作，
// 基本执行的总次数即为三重循环执行的次数，为n^3次，所以时间复杂度为O(n^3)

// 拓扑排序
// AOV网
// 活动在顶点上的网（Activity On Vertex
// Network）简称AOV网，是指用顶点表示活动，用弧表示活动之间的优先关系的有向图。
// 顶点表示活动，弧表示活动之间的优先关系的有向图称为AOV网（Activity On Vertex
// Network）。

// 拓扑排序核心算法
// 对一个有向无环图进行拓扑排序，是将G中所有顶点排成一个线性序列，使得图中任意一对顶点u和v，若存在由u到v的路径，
// 则在拓扑排序中u一定在v前面。这样的一个序列称为拓扑序列。
// 1）在一个有向图中选择一个没有前驱（入度为0）的顶点输出。
// 2）删除1）中的顶点，并且删除从该顶点出发的全部边。
// 3）重复1）和2），直到所有顶点输出，或者当前图中不存在无前驱的顶点为止。
// 以邻接表为存储结构。对邻接表表头结构定义进行修改，可加上一个统计结点入度的域，以便在拓扑排序时不必每次都扫描整个邻接表。

typedef struct {
  char data;
  int count; // count来统计顶点当前入度
  ArcNode *firstarc;
} VNodev2;
typedef struct {
  VNodev2 adjlist[maxSize]; // 邻接表
  int n, e;                 // 顶点数和边数
} AGraphv2;                 // 图的邻接表类型

// 假设图的邻接表已经生成，并且个个顶点的入度已经统计完毕，在本算法中要设置一个栈，
// 用来记录当前图入度为0的顶点，还要设置一个计数器n，用来记录已经输出的顶点个数。
// 算法开始时置n为0，扫描所有i的那个点，将入度为0的顶点入栈，然后n加1，接着从栈中弹出一个顶点，输出该顶点，
// 执行++n，并且将该顶点的所有邻接点的入度减1，如果减1后入度为0，则将该顶点入栈，重复上述过程，直到栈为空为止。
int TopSort(AGraphv2 *G) {
  int i, j, n = 0;
  int stack[maxSize], top = -1;
  ArcNode *p;
  for (i = 0; i < G->n; i++) // 图中顶点从0开始编号
    if (G->adjlist[i].count == 0)
      stack[++top] = i; // 入度为0结点入栈
  while (top != -1) {
    i = stack[top--]; // 顶点出栈
    ++n;              // 计数器加一记录当前节点
    cout << i << " "; // 输出当前顶点
    p = G->adjlist[i].firstarc;
    // 实现了将由此顶点引出的边所指向的顶点的入度减一，并将这个过程中入度变成0的顶点入栈
    while (p != nullptr) {
      j = p->adjvex;
      --(G->adjlist[j].count);
      if (G->adjlist[j].count == 0)
        stack[++top] = j;
      p = p->nextarc;
    }
  }
  if (n == G->n)
    return 1;
  else
    return 0;
}

// AOE网（Activity On Edge Network）对于活动在边上的网
// 和AOV图的相同点：
// 都是有向无环图
// 不同点：AOE网表示活动，边有权值，边代表活动持续时间；顶点代表事件，事件是由图中新活动开始或者旧活动结束的表示。
// AOV网的顶点表示活动，边无权值，边代表活动之间的先后关系。
// 对于一个表示工程的AOE网，只存在一个入度为0的顶点，称为源点，表示整个工程的开始；也只存在一个出度为0的顶点，成为汇点，表示整个工程的结束。
// AOE网中的每个顶点表示一个事件，每条边表示一个活动，边上的权值表示活动持续的时间，顶点的最早发生时间表示事件最早发生的时间，顶点的最晚发生时间表示事件最晚发生的时间。

// 判断图中从vi到vj是否有路径，可以采用遍历的方式。遍历的起点为vi，再一次BFS推出之前遇到vj，则证明有路径，否则没路径。
int BFSv2(AGraph *G, int vi, int vj) {
  ArcNode *p;
  int que[maxSize], front = 0, rear = 0;
  int visit[maxSize];
  int i, j;
  for (i = 0; i < G->n; i++)
    visit[i] = 0;
  rear = (rear + 1) % maxSize;
  que[rear] = vi;
  visit[vi] = 1;
  while (front != rear) {
    front = (front + 1) % maxSize;
    j = que[front];
    if (j == vj) // 对顶点的访问函数换成判断当前顶点是否为vj即可
      return 1;
    p = G->adjlist[j].firstarc;
    while (p != nullptr) {
      if (!visit[p->adjvex]) {
        rear = (rear + 1) % maxSize;
        que[rear] = p->adjvex;
        visit[p->adjvex] = 1;
      }
      p = p->nextarc; // p指向j的下一条边
    }
  }
}
// 本算法主体为一个双重循环，基本操作有两种：一种是顶点进队，另一种是边的访问。
// 最坏情况为遍历图中所有顶点后才找到通路，此时所有顶点都进队一次，所有边都被访问一次，
// 因为基本操作的总次数为O(n+e)，所以时间复杂度为O(n+e)。

// 判断顶点r到G的每个顶点是否有路径可达，可以通过深度优先搜索遍历的方法。以r为起点进行深度有限搜索遍历，
// 若在函数dfs()退出前已经访问过所有顶点，则r为根。要打印出所有的根节点，可以对每个顶点都进行一次深度优先搜索遍历，
// 如果是根则打印
int visitv2[maxSize]; // 假设常量maxSize已经定义
int sum = 0;
void DFSv2(AGraph *G, int v) {
  ArcNode *p;
  visitv2[v] = 1;
  ++sum;
  p = G->adjlist[v].firstarc;
  while (p != nullptr) {
    if (!visitv2[p->adjvex]) {
      DFSv2(G, p->adjvex);
    }
    p = p->nextarc;
  }
}
void print(AGraph *G) {
  int i, j;
  for (i = 0; i < G->n; i++) {
    sum = 0; // 每次选取一个新的结点时计数器清零
    for (j = 0; j < G->n; j++)
      visitv2[j] = 0; // 每次进行DFS访问时标记数组清零
    DFSv2(G, i);
    if (sum == G->n) // 当图中顶点全部被访问时，则判断为根，输出
      cout << i << endl;
  }
}
// 对于一个有向图，不用拓扑排序，实现判断图中是否存在经过给定顶点v0的环的算法
// 有深度优先搜索算法可知，在一个顶点v的所有边都被检查过之后，则要返回顶点v，进而退回上一个顶点，
// 重新开始检查上一个顶点的其他边。假如图中不存在回路，则在v处遍历v的其他邻接顶点的过程结束前，
// 不会出现一条指向v的边，可以通过检查是否有这样一条边来判断是否存在回路。
bool DFSForCircle(AGraph *G, int v, bool visited[]) {
  bool flag;
  ArcNode *p;
  visited[v] = true;
  for (p = G->adjlist[v].firstarc; p != nullptr; p = p->nextarc) {
    if (visited[p->adjvex] == true) // 如果出现一条边指向v，则存在回路
      return true;
    else
      flag = DFSForCircle(G, p->adjvex, visited);
    if (flag == true)
      return true;
    visited[p->adjvex] = false; // 递归返回时抹除遍历
  }
  return false;
}

// 写出从图的邻接表转换成邻接矩阵表示的算法，图为无权图
void AGraphToMGraph(MGraph &g1, AGraph *g2) {
  ArcNode *p;
  int i, j;
  // 双重矩阵讲g1邻接矩阵清0
  for (i = 0; i < g1.n; i++)
    for (j = 0; j < g1.n; j++)
      g1.edges[i][j] = 0;
  // 用p指针扫描邻接表中所有边结点
  for (i = 0; i < g2->n; i++) {
    p = g2->adjlist[i].firstarc; // 指向i的第一个邻接点
    while (p != nullptr) {       // 如果边不为空
      g1.edges[i][p->adjvex] = 1;
      p = p->nextarc;
    }
  }
  g1.n = g2->n;
  g1.e = g2->e;
}

// 设有向图用邻接表表示，图有n个顶点，图采用简化的表示方法，顶点信息与其在数组中的下标相同，
// 表示为0-n-1，尝试写一个算法求顶点k的入度。
int indegree(AGraph *g, int k) {
  ArcNode *p;
  int i, sum;
  sum = 0;
  for (i = 0; i < g->n; i++) {
    p = g->adjlist[i].firstarc;
    while (p != nullptr) {
      if (p->adjvex == k) { // 如果顶点i出发的另一端点是k，则计数器加1
        sum++;
        break;
      }
    }
    p = p->nextarc;
  }
  return sum; // 返回k的入度
}

// 写出以邻接表为存储结构的图的深度优先搜索遍历算法的非递归算法
void dfsv2(AGraph *g, int v) {
  ArcNode *p;
  int stack[maxSize], top = -1; // 定义一个栈来记录访问过程中的顶点
  int i, k;
  int visit[maxSize];
  for (i = 0; i < g->n; i++)
    visit[i] = 0;   // 访问标记数组初始化
  Visit(g, v);      // 访问顶点
  stack[++top] = v; // 标记初始顶点入栈
  while (top != -1) {
    k = stack[top];             // 取栈顶元素
    p = g->adjlist[k].firstarc; // p指向该顶点第一条边
    // p沿着边走并将图中经过的顶点入栈
    while (p != nullptr && visit[p->adjvex] == 0)
      p = p->nextarc; // 找到当前顶点第一个没访问过的邻接结点或者当p走到当前链表尾部时，while循环停止
    if (p ==
        nullptr) // 如果p到达当前链表尾部，则说明当前顶点的所有点都访问完毕，当前顶点出栈
      --top;
    else { // 否则访问当前邻接点入栈
      Visit(g, p->adjvex);
      visit[p->adjvex] = 1;
      stack[++top] = p->adjvex;
    }
  }
}

// 省政府“畅通工程”的目的是使全省任何两个村庄件都可以实现公路交通（但不一定有直接的公路相连），
// 只要能间接通过公路到达即可）。现得到城镇道路统计表，表中列出了任意两镇间修建道路的费用，
// 以及该道路是否已经修通的状态，全省一共N个村庄，编号从0-N-1。先写程序，计算出全省畅通需要的最低成本。
// 道路信息保存在road[]数组中，road数组定义如下：
typedef struct {
  int a, b; // a，b为道路两端两个村庄
  int cost; // 如果a、b间需要修路，则cost为修路费用
  int is; // is等于0代表a、b间还未修路，is等于1代表a、b间已经修路
} Roadv2;               // 道路结构体类型
Roadv2 roadv2[maxSize]; // 定义road数组，保存道路信息

// 本题考察的是最小生成树算法的应用，要实现全省各个村庄之间的畅通，就要找到一棵最小生成树，
// 只需要根据道路统计表，建立最小生成树即可。因为有些村庄间道路已经存在，所以只需要再此
// 基础上继续建立。

int getRoot(int a, int set[]) { // 查早并查集中根节点的函数
  while (a != set[a])
    a = set[a];
  return a;
}
#define N 20
#define M 20
int Lowcost(Roadv2 road[]) {
  int i;
  int a, b, min;
  int set[maxSize];
  min = 0;
  for (i = 0; i < N; i++)
    set[i] = i;
  for (i = 0; i < M; i++) {
    if (road[i].is == 1) { // 如果a、b间已经修路，则将a、b所在的集合合并
      a = getRoot(road[i].a, set);
      b = getRoot(road[i].b, set);
      if (a != b)
        set[a] = b;
    }
  }
  // 假设函数sort()已经定义，既对road[]中M条道路按照花费进行递增排序
  sort(road, M);
  // 下面这个循环从road[]数组中逐个跳出应修的道路
  for (i = 0; i < M; i++)
    // 当a、b不属于一个集合时，并且a、b间没有道路时，将a、b并入同一集合，并记录修建a、b间道路的花费
    if (road[i].is == 0 &&
        (a = getRoot(road[i].a, set)) != (b = getRoot(road[i].b, set))) {
      set[a] = b;
      min += road[i].cost;
    }
  return min;
}