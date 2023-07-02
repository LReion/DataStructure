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
qu.rear == qu.front; // 队空状态
// 队满状态

// 元素x进队操作（移动队尾指针）
/* qu.rear = (qu.rear + 1) % maxSize;
qu.data[qu.rear] = x; */

// 元素出队操作（移动队首指针）
/* qu.front = (qu.front + 1) % maxSize;
qu.data[qu.front] = x; */

// 初始化队列算法
void initQueue(SqQueue &qu) { 
    qu.front = qu.rear = 0;  // 队首和队尾指针重合，并且指向0
 }

// 判断队空算法
int isQueueEmpty(SqQueue qu){
    if(qu.front==qu.rear)
    return 1;
    else
    return 0;
}

// 进队算法
int enQueue(SqQueue &qu,int x){
  if((qu.rear+1)%maxSize==qu.front)
  return 0;
  qu.rear=(qu.rear+1)%maxSize;
  qu.data[qu.rear]=x;
  return 1;
}

// 出队算法
int deQueue(SqQueue &qu,int&x){
  if(qu.front==qu.rear)
  return 0;
  qu.front=(qu.front+1)%maxSize;
  x=qu.data[front];
  return 1;
}