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

// 数组A[0, ... , n-1]的n个元素中有多个零元素，设计一个算法，将A
// 中所有的非零元素依次移动到A数组的前端
void moveZero(int A[], int n) {
  int i = -1, j, tmp;
  for (j = 0; j < n; j++) {
    if (A[j] != 0) { // A[j]为第i个不为0的元素
      ++i;
      if (i != j) { // 如果A[j]不在位置i上，则A[i]和A[j]交换位置
        tmp = A[i];
        A[i] = A[j];
        A[j] = tmp;
      }
    }
  }
}

// 关于浮点数组A[0, ..., n-1]，试设计实现下列运算的递归算法
// 1. 求A中最大元素的值
float max(float A[], int n) {
  if (n == 1) // 如果长度为1，则返回自己
    return A[0];
  else {
    float x = max(A, n - 1); // n-1个长度里面的最大值
    return x > A[n - 1] ? x
                        : A[n - 1]; // n-1个长度里面的最大值和最后一个元素比较
  }
}

// 求数组中n个数之和
float sum(float A[], int n) {
  if (n == 1) // 如果数组只有一个，则和为自己
    return A[0];
  else {
    float x = sum(A, n - 1); // 否则和为前n-1个元素的和+最后一个元素
    return x + A[n - 1];
  }
}

float average(float A[], int n) {
  if (n == 1) // 如果只有一个数字，则平均值是自己
    return A[0];
  else {
    float x = average(
        A,
        n - 1); // 否则等于前n-1个元素的平均值乘以元素数量+最后一个元素除以总元素数量来求平均值
    return (x * (n - 1) + A[n - 1]) / n;
  }
}

// 试设计一个算法，将数组A[0, ..., n-1]中所有奇数移到偶数之前
// 要求不另增加存储空间，且时间复杂为O(n)
void moveEven(int A[], int n) {
  for (int i = 0; i < n; i++) { // 遍历数组
    if ((A[i] & 1) == 1) {      // 如果碰到奇数
      for (int j = i + 1; j < n; j++) { // 则在奇数后面寻找一个偶数来交换位置
        if ((A[i] & 1) == 0) {
          int temp = A[i];
          A[i] = A[j];
          A[j] = temp;
          break;
        }
      }
    }
  }
}

// 设有一元素为整数的线性表L，存放在一维数组A[0, ..., n-1]中，
// 设计一个算法，以A[n-1]为参考量，将该数组分为左、右两个部分，
// 其中左半部分的元素值均小于A[n-1]，右半部分的元素值均大于A[n-1]
// A[n-1]则位于这两部分之间。要求结果仍存放在数组A中。
void divide(int A[], int n) {
  int tmp;
  int i = 0, j = n - 1;
  tmp = A[i];
  A[i] = A[j];
  A[j] = tmp;
  tmp = A[i];
  /* 下面这个循环将数组中小于tmp的元素放在左边，大于tmp的元素放在右边 */
  while (i != j) {
    while (j > i && A[j] > tmp) // 从右往左扫描找到一个小于tmp的元素
      --j;
    if (i < j) {   // 放在tmp左边
      A[i] = A[j]; // i指针移动一位
      ++i;
    }
    while (i < j && A[i] < tmp) // 从左往右扫描，找到一个大于tmp的元素
      ++i;
    if (i < j) {
      A[j] = A[i]; // 放在tmp右边
      --j;         // j指针右移一位
    }
  }
  A[i] = tmp; // tmp放在最终位置
}
// 设计一个算法，对给定的一个整形mxn矩阵A，统计这个矩阵中
// 具有下列特征的元素个数并输出它们的坐标及数值：它们既是
// 所在行中最小的值，又是所在列中的最小值；或者他们既是
// 所在行中的最大值，又是所在列中的最大值。假设矩阵中元素
// 各不相同，要求结果在处理过程中用输出语句输出
void printmmin(int A[][maxSize], int m, int n) {
  int i, j, k, min, minj;
  int flag;
  for (i = 0; i < m; i++) {
    min = A[i][0];
    minj = 0;
    for (j = 1; j < n; j++)
      if (A[i][j] < min) {
        min = A[i][j];
        minj = j;
      }
    flag = 1;
    for (k = 0; k < m; k++) {
      if (min > A[k][minj]) {
        flag = 0;
        break;
      }
    }
    if (flag) {
      cout << min << ", [" << i << "][" << minj << "]" << endl;
    }
    cout << endl;
  }
}
void printmax(int A[][maxSize], int m, int n) {
  int i, j, k, max, maxj;
  int flag;
  for (i = 0; i < m; i++) { // 处理第i行
    max = A[i][0];
    maxj = 0;
    for (j = 1; j < n; j++) // 找出i行上的最大值
      if (A[i][j] > max) {
        max = A[i][j];
        maxj = j;
      }
    flag = 1;
    for (k = 0; k < m; k++) {
      if (max < A[k][maxj]) { // 判断max是否为maxj列上的最大值
        flag = 0;
        break;
      }
      if (flag) { // 如果是，则打印最大值，其格式为，max，[i, max]
        cout << max << ", [" << i << "][" << maxj << "]" << endl;
      }
      cout << endl;
    }
  }
}

// 简要介绍稀疏矩阵三元组存储结构特点，并实现稀疏矩阵的基本操作
// （1）给定稀疏矩阵A（int型），创建其三元素存储结构B
void create(int A[][maxSize], int m, int n, int B[][3]) {
  int i, j, k = 1;
  for (i = 0; i < m; i++)
    for (j = 0; j < n; j++)
      if (A[i][j] != 0) {
        /* 扫描A中的元素，将不为零的元素相关信息存放在B中的对应位置 */
        B[k][0] = A[i][j];
        B[k][1] = i;
        B[k][2] = j;
        ++k;
      }
  B[0][0] = k - 1;
  B[0][1] = m;
  B[0][2] = n; // 存入非零元素个数
}

// （2）查找给定元素x是否在矩阵中
int search(int B[][3], int x) {
  int i, t;
  t = B[0][0]; // 获取元素个数
  i = 1;
  while (i <= t && B[i][0] != x) // 从第一个元素开始遍历元素的值
    i++;
  if (i < t) // 退出循环时，如果i<t，则表示找到了元素
    return 1;
  else // 否则没有找到元素
    return 0;
}
int findTrimat(float A[][3], int m, int n, int x) {
  for (int i = 1; i <= A[0][0]; i++) {
    if (A[i][0] == x) {
      return 1;
    }
  }
  return 0;
}

// 假设稀疏矩阵A采用三元组表示，编写一个函数，计算其转置矩阵B
// 要求B也采用三元组表示。
void transpose(int A[][3], int B[][3]) {
  int p, q, col;
  B[0][0] = A[0][0]; // 读取元素个数
  B[0][1] = A[0][1]; // 行
  B[0][2] = A[0][2]; // 列
  if (B[0][0] > 0) { // 如果元素个数不为0
    q = 1;
    for (col = 0; col < B[0][1]; col++) // 按列转置 , 找出列中所有元素
      for (p = 1; p <= B[0][2]; p++) // 遍历行 , 然后找出列中非0元素
        if (A[p][2] == col) {        // 如果等于指定列
          B[q][0] = A[p][0];
          B[q][1] = A[p][2]; // 将其转置后，按照列优先存放在三元组中
          B[q][2] = A[p][1];
          ++q;
        }
  }
}

// 假设稀疏矩阵A和B（两矩阵行列数对应相等）都采用
// 三元组表示，编写一个函数，计算C=A+B，要求C也用三元组表示，
// 所有矩阵均为int型
void add(int A[][3], int B[][3], int C[][3]) {
  int i = 1, j = 1, k = 1, m;
  while (i <= A[0][0] && j <= B[0][0])
    if (A[i][1] == B[j][1]) {
      // 若A当前元素的行号等于B当前元素的行号，则比较其列好，将较小列的元素存入C中；
      // 若列号也相等，则将相应的元素值相加后存入C中
      if (A[i][2] < B[j][2]) {
        C[k][0] = A[i][0];
        C[k][1] = A[i][1];
        C[k][2] = A[i][2];
        ++k;
        ++i;
      } else if (A[i][2] > B[j][2]) {
        C[k][0] = B[i][0];
        C[k][1] = B[i][1];
        C[k][2] = B[i][2];
        ++k;
        ++j;
      } else { // 如果行列号相等则可以进行加法运算
        m = A[i][0] + B[j][0];
        if (m != 0) { // 如果加法运算后不为0，则存入C中
          C[k][1] = B[j][1];
          C[k][2] = B[j][2];
          C[k][0] = m;
        }
        ++i;
        ++j;
      }
    } else if (A[i][1] < B[j][1]) {
      // 若A当前元素的行号小于B当前元素的行号，则将A当前元素存入C中
      C[k][0] = A[i][0];
      C[k][1] = A[i][1];
      C[k][2] = A[i][2];
      ++k;
      ++i;
    } else {
      // 若A当前元素的行号大于B当前元素的行号，则将B的元素存入C中
      C[k][0] = B[j][0];
      C[k][1] = B[j][1];
      C[k][2] = B[j][2];
      ++k;
      ++j;
    }
  while (i <= A[0][0]) {
    C[k][0] = A[i][0];
    C[k][1] = A[i][1];
    C[k][2] = A[i][2];
    ++k;
    ++i;
  }
  // B中有剩余元素
  while (j <= B[0][0]) {
    C[k][0] = A[i][0];
    C[k][1] = A[i][1];
    C[k][2] = A[i][2];
    ++k;
    ++j;
  }
  C[0][0] = k - 1; // 产生0行的结果
  C[0][1] = A[0][1];
  C[0][2] = A[0][2];
}

int getValue(int D[][maxSize], int i, int j) {
  // 返回D对应的稀疏矩阵A中（i, j）位置上的值
  int k = 1;
  while (k <= D[0][0] && (D[k][1] != i || D[k][2] != j))
    k++;
  if (k <= D[0][0])
    return D[k][0];
  else
    return 0;
}

// 矩阵相乘
void mul(int A[][3], int B[][3], int C[][3], int m, int n, int k) {
  int i, j, l, p = 1, s;
  for (i = 0; i < m; i++)
    for (j = 0; j < k; ++j) {
      s = 0;
      for (l = 0; l < n; l++)
        s += getValue(A, i, j); // 获取对应位置上的值
      if (s != 0) {             // 如果不为0，则存入C中
        C[p][1] = i;
        C[p][2] = j;
        C[p][0] = s;
        ++p;
      }
    }
  C[0][1] = m;
  C[0][2] = n;
  C[0][0] = p - 1;
}