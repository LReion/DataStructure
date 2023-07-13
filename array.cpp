#include <iostream>
#include <stdlib.h>
// #define m 4
// #define n 5
#define maxSize 20
using namespace std;

// Amn是一个矩阵的逻辑表示
// int A[m][n];

// 矩阵的转置
// 对于一个mxn的矩阵A[m][n]，它的转置矩阵是一个nxm的矩阵B[n][m]，其中B[i][j]=A[j][i],
// 0<=i<n, 0<=j<m
void transpose(int A[][maxSize], int B[][maxSize], int m, int n) {
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      B[j][i] = A[i][j];
}
// 这里强调了转置算法的1核心部分，略去了一些非法输入的判定操作，
// 并且为了方便处理，将二维数组统一设置成maxSizeXmaxSize的大小
// 其中maxSize是事先定义好的宏变量，表示可能出现的尺寸最大值

// 两个矩阵相加
// 两个尺寸均为mxn的矩阵A和B相加，得到一个新的矩阵C，其中C[i][j]=A[i][j]+B[i][j]
void addmat(int C[][maxSize], int A[][maxSize], int B[][maxSize], int m,
            int n) {
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      C[i][j] = A[i][j] + B[i][j];
}

// 矩阵相乘
// 矩阵相乘也是一种常见的矩阵运算。假设两矩阵A与B相乘，结果为C，C中第i行第j列的元素为A中第i行
// 的元素与B中第j列的元素对应相乘并且求和的结果（两向量的点乘）。
// A和B两矩阵可以相乘的条件是，A的列数必须等于B的行数。算法实现如下，其中A的尺寸为mxn，B的尺寸为nxk
void mutmat(int C[][maxSize], int A[][maxSize], int B[][maxSize], int m, int n,
            int k) {
  for (int i = 0; i < m; i++)
    for (int j = 0; j < k; j++) {
      C[i][j] = 0;
      for (int h = 0; h < n; h++)
        C[i][j] += A[i][h] * B[h][j];
    }
}

// 稀疏矩阵
// 三元组数据结构为一个长度为n、表内每个元素都有3个分量的线性表，
// 其3各分量分别为值、行下标和列下标。元素结构体定义如下：
typedef struct {
  int val;
  int i, j;
} Trimat;

// 在程序中如果要定义一个含有maxSize个非零元素的稀疏矩阵，则只需要写成如下代码：
Trimat trimat[maxSize + 1];

// 建立三元组B
void createtrimat(float A[][maxSize], int m, int n, float B[][3]) {
  int k = 1;
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      if (A[i][j] != 0) {
        B[k][0] = A[i][j];
        B[k][1] = i;
        B[k][2] = j;
        ++k;
      }
  B[0][0] = k - 1;
  B[0][1] = m;
  B[0][2] = n;
}

// 通过三元组打印矩阵A
void print(float B[][3]) {
  int k = 1;
  for (int i = 0; i < B[0][1]; i++) {
    for (int j = 0; j < B[0][2]; j++) {
      if (i == (int)B[k][1] && j == (int)B[k][2]) {
        cout << B[k][0] << " ";
        ++k;
      } else {
        cout << "0 ";
      }
      cout << endl;
    }
  }
}

// 使用十字链表来表示稀疏矩阵
// 普通节点定义如下
typedef struct OLNode {
  int row, col;                // 行号和列号
  struct OLNode *right, *down; // 指向右边节点和下方节点的指针
  float val;
} OLNode;
// 头节点定义
typedef struct {
  OLNode *rhead, *chead; // 行和列的头指针
  int m, n, k;           // 矩阵行数、列数以及非零节点总数
} CrossList;

// 给定一个稀疏矩阵A，其尺寸为mxn，非零元素个数为k，建立其对应的十字链表
// 存储结构，算法如下：
int createCrosslistMat(float A[][maxSize], int m, int n, int k, CrossList &M) {
  if (M.rhead) // 如果行头节点不为空，则释放其空间
    free(M.rhead);
  if (M.chead) // 如果列头节点不为空，则释放其空间
    free(M.chead);
  M.m = m; // 初始化稀疏矩阵的长度
  M.n = n;
  M.k = k;
  // 申请头节点数组空间
  if (!(M.rhead = (OLNode *)malloc(sizeof(OLNode) * m)))
    return 0;
  if (!(M.chead = (OLNode *)malloc(sizeof(OLNode) * n)))
    return 0;
  // 头结点数组right和down指针置空
  for (int i = 0; i < m; i++) {
    M.chead[i].right = nullptr;
    M.chead[i].down = nullptr;
  }
  for (int i = 0; i < n; i++) {
    M.rhead[i].right = nullptr;
    M.rhead[i].down = nullptr;
  }
  OLNode *temps[maxSize]; // 建立列链表的辅助指针数组
  for (int j = 0; j < n; j++)
    temps[j] = &(M.chead[j]); // 记录每一列的头节点
  for (int i = 0; i < m; i++) {
    OLNode *r = &(M.chead[i]);
    for (int j = 0; j < n; j++) {
      if (A[i][j] != 0) {
        OLNode *p = (OLNode *)malloc(sizeof(OLNode));
        p->row = i;
        p->col = j;
        r->val = A[i][j];
        r->down = nullptr;
        p->right = nullptr;
        r->right = p;
        r = p;
        temps[j]->down = p; // 透过temps数组记录每一列的最后一个节点
        temps[j] = p;
      }
    }
  }
}