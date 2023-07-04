#include <malloc.h>
#define maxSize 20
// 顺序队列定义
typedef struct {
  int data[maxSize];
  int front; // 队首指针
  int rear;  // 队尾指针
} SqQueue;   // 顺序队类型定义

// 链队节点定义
typedef struct QNode {
  int data;           // 数据域
  struct QNode *next; // 指针域
} QNode;              // 队结点类型定义

// 链队类型定义
typedef struct {
  QNode *front; // 队头指针
  QNode *rear;  // 队尾指针
} LiQueue;      // 链队类型定义

SqQueue qu;
// 循环队列
// 队空操作
// qu.rear == qu.front; // 队空状态
// 队满状态

// 元素x进队操作（移动队尾指针）
/* qu.rear = (qu.rear + 1) % maxSize;
qu.data[qu.rear] = x; */

// 元素出队操作（移动队首指针）
/* qu.front = (qu.front + 1) % maxSize;
qu.data[qu.front] = x; */

// 初始化队列算法
void initQueue(SqQueue &qu) {
  qu.front = qu.rear = 0; // 队首和队尾指针重合，并且指向0
}

// 判断队空算法
int isQueueEmpty(SqQueue qu) {
  if (qu.front == qu.rear)
    return 1;
  else
    return 0;
}

// 进队算法
int enQueue(SqQueue &qu, int x) {
  if ((qu.rear + 1) % maxSize == qu.front)
    return 0;
  qu.rear = (qu.rear + 1) % maxSize;
  qu.data[qu.rear] = x;
  return 1;
}

// 出队算法
int deQueue(SqQueue &qu, int &x) {
  if (qu.front == qu.rear)
    return 0;
  qu.front = (qu.front + 1) % maxSize;
  x = qu.data[qu.front];
  return 1;
}

// 链队
LiQueue *liq;

// 队空状态
/* lqu->rear==nullptr 或者 lqu->front==nullptr */

// 元素进队操作
/* lqu->rear->next=p;
lqu->rear=p; */

// 元素出队操作
/* p = lqu->front;
lqu->front = p->next;
x = p->data;
free(p); */

// 初始化链表算法
void initQueue(LiQueue *&lqu) {
  lqu = (LiQueue *)malloc(sizeof(LiQueue));
  lqu->front = lqu->rear = nullptr;
}

// 判断队空算法
int isQueueEmpty(LiQueue *lqu) {
  if (lqu->rear == nullptr ||
      lqu->front == nullptr) // 如果front或rear为空，则队列中没有节点
    return 1;
  return 0;
}

// 入队算法
void enQueue(LiQueue *lqu, int x) {
  QNode *p;
  p = (QNode *)malloc(sizeof(QNode)); // 为插入数据申请结点存放
  p->data = x;
  p->next = nullptr;
  if (lqu->rear ==
      nullptr) // 如果队尾指针为空，则说明插入的数据是队列的第一个结点
    lqu->front = lqu->rear = p;
  else { // 否则，将插入节点放在队尾
    lqu->rear->next = p;
    lqu->rear = p;
  }
}

// 出队算法
int deQueue(LiQueue *lqu, int &x) {
  QNode *p;
  if (lqu->rear == nullptr) // 队空不能出队
    return 0;
  else
    p = lqu->front;
  if (lqu->front == lqu->rear) // 队中只有一个节点，删除后队列队空（头尾指针指向空）
    lqu->front = lqu->rear = nullptr;
  else
    lqu->front = lqu->front->next;
  x = p->data;
  free(p);
  return 1;
}